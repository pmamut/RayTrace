#include "stdafx.h"
#include "math.h"
#include "lib3d.h"

CModel3D::CModel3D (void)
{
}

CModel3D::~CModel3D (void)
{
}

int CModel3D::GetInt (void)
{
	int temp = 0;
	char* buf = strtok (NULL, " ,\t");
	if (buf)
		temp = atoi (buf);
	return temp;
}

double CModel3D::GetDouble (void)
{
	double temp = 0.0;
	char* buf = strtok (NULL, " ,\t");
	if (buf)
		temp = atof (buf);
	return temp;
}

CPoint3D CModel3D::GetPoint (void)
{
	double x = GetDouble ();
	double y = GetDouble ();
	double z = GetDouble ();
	return CPoint3D (x, y, z);
}

CColor CModel3D::GetColor (void)
{
	double r = GetDouble ();
	double g = GetDouble ();
	double b = GetDouble ();
	return CColor (r, g, b);
}

CShader* CModel3D::GetShader (void)
{
	CShader* shader = NULL;
	char* buf = strtok (NULL, " ,\t");
	if (!strcmp(buf, "constant"))
	{
		CColor kd = GetColor ();
		shader = (CShader*) new CConstant (kd);
	}
	else if (!strcmp(buf, "texture"))
	{
		shader = (CShader*) new CTexture (strtok (NULL, " ,\t"));
	}
	else if (!strcmp(buf, "chequer"))
	{
		double step = GetDouble ();
		CColor dark = GetColor ();
		CColor light = GetColor ();
		shader = (CShader*) new CChequer (step, dark, light);
	}
	else if (!strcmp(buf, "wood"))
	{
		shader = (CShader*) new CWood;
	}

	if (!shader)
		shader = (CShader*) new CConstant ();
	return shader;
}

BOOL CModel3D::Create (const CString& file)
{

	FILE* src = fopen (file, "rt");
	if (src)
	{
		char buf [256];
		char* tmp;
		while (fgets (buf, sizeof (buf), src))
		{
			buf [strlen (buf) - 1] = '\0';
			tmp = strtok (buf, " ,\t");
			if (!strcmp(tmp, "Window"))
			{
				screen.width = GetInt ();
				screen.height = GetInt ();
				screen.xleft = GetDouble ();
				screen.xright = GetDouble ();
				screen.ybottom = GetDouble ();
				screen.ytop = GetDouble ();
				screen.z = GetDouble ();
				screen.Resample ();
			}
			else if (!strcmp(tmp, "Camera"))
			{
				camera.location = GetPoint ();
			}
			else if (!strcmp(tmp, "Ambient_Light"))
			{
				ambient_light = GetColor ();
			}
			else if (!strcmp(tmp, "Background_Color"))
			{
				background_color = GetColor ();
			}
			else if (!strcmp(tmp, "Light"))
			{
				CPoint3D loc = GetPoint ();
				CColor clr = GetColor ();
				lights.AddTail (new CLight3D (loc, clr));
			}
			else if (!strcmp(tmp, "Sphere"))
			{
				CPoint3D cntr = GetPoint ();
				double r = GetDouble ();
				CShader* shader = GetShader ();
				CColor ks = GetColor ();
				double ph = GetDouble ();
				CColor kr = GetColor ();
				objects.AddTail (new CSphere3D (cntr, r, shader, ks, ph, kr));
			}
			else if (!strcmp(tmp, "Plane"))
			{
				double x = GetDouble ();
				double y = GetDouble ();
				double z = GetDouble ();
				double d = GetDouble ();
				CShader* shader = GetShader ();
				CColor ks = GetColor ();
				double ph = GetDouble ();
				CColor kr = GetColor ();
				objects.AddTail (new CPlane3D (x, y, z, d, shader, ks, ph, kr));
			}
			else if (!strcmp(tmp, "Box"))
			{
				CPoint3D p1 = GetPoint ();
				CPoint3D p2 = GetPoint ();
				CShader* shader = GetShader ();
				CColor ks = GetColor ();
				double ph = GetDouble ();
				CColor kr = GetColor ();
				objects.AddTail (new CBox3D (p1, p2, shader, ks, ph, kr));
			}
		}
		fclose (src);
		screen.image.Reset ();
		if (screen.image.Create (screen.width, screen.height))
			return TRUE;
	}
	return FALSE;
}

void CModel3D::Reset (void)
{
	CCamera3D cam;
	CColor col;

	camera = cam;
	ambient_light = col;
	background_color = col;
	screen.Reset ();
	lights.Empty ();
	objects.Empty ();
}

void CModel3D::TraceRay (const CRay3D& ray, const int depth, CColor& result)
{
	CPoint3D intersection, temp;
	CVector3D reflected_direction, transmitted_direction, normal, inv (ray.direction * -1.0);
	CColor shade, local, reflected, transmitted;
	double distance = 0.0;
	CObject3D* object = NULL;

// get intersection
	POSITION pos = objects.GetHeadPosition ();
	while (pos != NULL)
	{
		double d = 0.0;
		CObject3D* ptr = (CObject3D*) objects.GetNext (pos);
		if (ptr->IsIntersection (ray, temp, d))
		{
			if ((distance > d) || (object == NULL)) // closest intersection
			{
				if ((depth != 0) || (d > ray.length)) // near clipping plane
				{
					distance = d;
					intersection = temp;
					object = ptr;
				}
			}
		}
	}

	if (object == NULL)
		result = background_color;
	else
	{
		normal = object->GetN (intersection); // object's N at the point of intersection
		shade = object->shader->GetColor (intersection,object); // invoke shader

// ambient term
//		local = ambient_light * object->Kd;
		local = ambient_light * shade;

		if (!(shade.IsBlack () && object->Ks.IsBlack ())) // at least one of koeff. is not 0
		{
// for each light calculate LIM
			POSITION lpos = lights.GetHeadPosition ();
			while (lpos != NULL)
			{
				CLight3D* l = (CLight3D*) lights.GetNext (lpos);
				CRay3D shadow_ray (intersection, l->location); // shadow ray (L)
				double d = 0.0;
				BOOL in_shadow = FALSE;
// check against each object
				POSITION opos = objects.GetHeadPosition ();
				while (opos != NULL)
				{
					CObject3D* o = (CObject3D*) objects.GetNext (opos);
					if (o->IsIntersection (shadow_ray, temp, d))
						if (d < shadow_ray.length) // object is closer than light source
						{
							in_shadow = TRUE;
							break;
						}
				}
				if (!in_shadow) // no intersections
				{
// L - shadow_ray.direction, N - normal, H=(L+V).Normalize, V=ray.direction * -1

// diffuse only / distant light
//					local += (l->Ip * (object->Kd * (shadow_ray.direction * normal)));

// difuse and specular / distant light
//					local += l->Ip * (object->Kd * (shadow_ray.direction * normal) +
//									object->Ks * pow((normal * H), object->phong));
//					local += l->Ip * (shade * (shadow_ray.direction * normal) +
//									object->Ks * pow((normal * H), object->phong));

					if (!shade.IsBlack ()) // diffuse term
						local += l->Ip * (shade * (shadow_ray.direction * normal));

					if (!object->Ks.IsBlack ()) // specular term
					{
						CVector3D H = shadow_ray.direction + inv;
						H.Normalize ();
						local += object->Ks * pow ((normal * H), object -> phong);
					}

// difuse and specular / point light
//					local += l->Ip * (object->Kd * (shadow_ray.direction * normal) +
//									object->Ks * pow((normal * H), object->phong)) / (shadow_ray.length + E);
				}

			}
		}

		if (depth < 3) // max depth for reflections
		{
			if (!object->Kr.IsBlack ()) // reflected term
			{
				reflected_direction = (normal * 2.0) * (normal * inv) - inv;
				TraceRay (CRay3D (intersection, reflected_direction), depth + 1, reflected);
				local += reflected * object->Kr;
			}
			// transmission
			// TraceRay
		}
		local.Clip ();
		result = local;
	}
}

void CModel3D::RenderScanLine (const int scanline)
{
	double ys = screen.ytop - screen.dy * scanline;
	double xs;
	int x;
	for (x = 0, xs = screen.xleft; x < screen.width; x++, xs += screen.dx)
	{
		CPoint3D scr (xs, ys, screen.z);
//		CPoint3D tmp (xs, ys, camera.location.z);
		CRay3D primary_ray (camera.location, scr);
//		CRay3D primary_ray (tmp, scr);
		CColor result;
		TraceRay (primary_ray, 0, result);
		screen.image.SetPixel (x, scanline,
								(BYTE) (result.r * 255),
								(BYTE) (result.g * 255),
								(BYTE) (result.b * 255));
	}
}
