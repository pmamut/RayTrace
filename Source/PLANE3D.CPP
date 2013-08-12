#include "stdafx.h"
#include "lib3d.h"

CPlane3D::CPlane3D ()
{
	D = 0.0;
}

CPlane3D::~CPlane3D ()
{
}

CPlane3D::CPlane3D (const CVector3D& n, const double d, CShader* sh, const CColor& ks, const double ph, const CColor& kr)
{
	normal = n;
	normal.Normalize ();
	D = d;
	shader = sh;
	Ks = ks;
	phong = ph;
	Kr = kr;
}

CPlane3D::CPlane3D (const double x, const double y, const double z, const double d, CShader* sh, const CColor& ks, const double ph, const CColor& kr)
{
	normal = CVector3D (x, y, z);
	normal.Normalize ();
	D = d;
	shader = sh;
	Ks = ks;
	phong = ph;
	Kr = kr;
}

BOOL CPlane3D::IsIntersection (const CRay3D& ray, CPoint3D& point, double& distance) const
{
	double d = normal * ray.direction;
	if (d == 0.0)
		return FALSE;
	else
	{
		double t = -(normal.x * ray.origin.x + normal.y * ray.origin.y + normal.z * ray.origin.z + D) / d;
		if (t > E)
		{
			distance = t;
			point = CPoint3D (ray.origin.x + distance * ray.direction.x,
							ray.origin.y + distance * ray.direction.y,
							ray.origin.z + distance * ray.direction.z);
			return TRUE;
		}
		else
			return FALSE;
	}
}

BOOL CPlane3D::IsIn (const CPoint3D& point) const
{
	return FALSE;
}

CVector3D CPlane3D::GetN (const CPoint3D& point) const
{
	return normal;
}

BOOL CPlane3D::GetUV (const CPoint3D& point, double& u, double& v) const
{
	return FALSE;
}
