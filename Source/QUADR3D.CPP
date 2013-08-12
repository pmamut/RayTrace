#include "stdafx.h"
#include "math.h"
#include "lib3d.h"

CQuadric3D::CQuadric3D ()
{
	radius = 0.0;
	phong = 0.0;
}

CQuadric3D::~CQuadric3D ()
{
}

CQuadric3D::CQuadric3D (const CPoint3D& c, const double r, const CColor& kd, const CColor& ks, const double ph)
{
	center = c;
	radius = r;
	phong = ph;
	Kd = kd;
	Ks = ks;
}

CQuadric3D::CQuadric3D (const double x, const double y, const double z, const double r,
						const double dr, const double dg, const double db,
						const double sr, const double sg, const double sb, const double ph)
{
	center = CPoint3D (x, y, z);
	Kd = CColor (dr, dg, db);
	Ks = CColor (sr, sg, sb);
	radius = r;
	phong = ph;
}

BOOL CQuadric3D::IsIntersection (const CRay3D& ray, CPoint3D& point, double& distance) const
{
	double a, b, c, D, x1, x2;

// ****** a == 1.0 always! ****** ray.direction is normalized!
//	a = ray.direction.x * ray.direction.x +
//		ray.direction.y * ray.direction.y +
//		ray.direction.z * ray.direction.z;
	b = 2.0 * ray.direction.x * (ray.origin.x - center.x) +
		2.0 * ray.direction.y * (ray.origin.y - center.y) +
		2.0 * ray.direction.z * (ray.origin.z - center.z);
	c = center.x * center.x + center.y * center.y + center.z * center.z +
		ray.origin.x * ray.origin.x + ray.origin.y * ray.origin.y + ray.origin.z * ray.origin.z -
		2.0 * (center.x * ray.origin.x + center.y * ray.origin.y + center.z * ray.origin.z) -
		radius * radius;
//	D = b * b - 4 * a * c;
	D = b * b - 4 * c;
	if (D < 0.0)
		return FALSE;
	else if (D == 0.0)
	{
//		x1 = (-b) / (2.0 * a);
		x1 = (-b) / 2.0;
		if (x1 > E)
		{
			distance = x1;
			point = CPoint3D (ray.origin.x + distance * ray.direction.x,
							ray.origin.y + distance * ray.direction.y,
							ray.origin.z + distance * ray.direction.z);
			return TRUE;
		}
		else
			return FALSE;
	}
	else
	{
//		x1 = (-b + sqrt (D)) / (2.0 * a);
//		x2 = (-b - sqrt (D)) / (2.0 * a);
		x1 = (-b + sqrt (D)) / 2.0;
		x2 = (-b - sqrt (D)) / 2.0;
		if ((x1 > E) && (x2 > E))
		{
			distance = __min (x1, x2);
			point = CPoint3D (ray.origin.x + distance * ray.direction.x,
							ray.origin.y + distance * ray.direction.y,
							ray.origin.z + distance * ray.direction.z);
			return TRUE;
		}
		else
		{
			x1 = __max (x1, x2);
			if (x1 > E)
			{
				distance = x1;
				point = CPoint3D (ray.origin.x + distance * ray.direction.x,
								ray.origin.y + distance * ray.direction.y,
								ray.origin.z + distance * ray.direction.z);
				return TRUE;
			}
			else
				return FALSE;
		}

	}
}

BOOL CQuadric3D::IsIn (const CPoint3D& point) const
{
	return FALSE;
}

CVector3D CQuadric3D::GetN (const CPoint3D& point) const
{
	return CVector3D ((point.x - center.x) / radius, (point.y - center.y) / radius, (point.z - center.z) / radius);
//	CVector3D N (point.x - center.x, point.y - center.y, point.z - center.z);
//	N.Normalize ();
//	return N;
}
