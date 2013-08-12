#include "stdafx.h"
#include "math.h"
#include "lib3d.h"

CBox3D::CBox3D ()
{
}

CBox3D::~CBox3D ()
{
}

CBox3D::CBox3D (const CPoint3D& p1, const CPoint3D& p2, CShader* sh, const CColor& ks, const double ph, const CColor& kr)
{
	leftmost.x = __min (p1.x, p2.x);
	leftmost.y = __min (p1.y, p2.y);
	leftmost.z = __min (p1.z, p2.z);
	rightmost.x = __max (p1.x, p2.x);
	rightmost.y = __max (p1.y, p2.y);
	rightmost.z = __max (p1.z, p2.z);
	shader = sh;
	Ks = ks;
	phong = ph;
	Kr = kr;
}

CBox3D::CBox3D (const double x1, const double y1, const double z1,
				const double x2, const double y2, const double z2,
				CShader* sh, const CColor& ks, const double ph, const CColor& kr)
{
	leftmost.x = __min (x1, x2);
	leftmost.y = __min (y1, y2);
	leftmost.z = __min (z1, z2);
	rightmost.x = __max (x1, x2);
	rightmost.y = __max (y1, y2);
	rightmost.z = __max (z1, z2);
	shader = sh;
	Ks = ks;
	phong = ph;
	Kr = kr;
}

BOOL CBox3D::IsIntersection (const CRay3D& ray, CPoint3D& point, double& distance) const
{
	BOOL valid_x = FALSE, valid_y = FALSE, valid_z = FALSE, valid_t = FALSE;
	double tnear, tfar;

	if (ray.direction.x != 0.0)
		valid_x = TRUE;
	else  // ray is parallel to YZ planes
		if ((ray.origin.x < leftmost.x) || (ray.origin.x > rightmost.x))
			return FALSE;

	if (ray.direction.y != 0.0)
		valid_y = TRUE;
	else  // ray is parallel to XZ planes
		if ((ray.origin.y < leftmost.y) || (ray.origin.y > rightmost.y))
			return FALSE;

	if (ray.direction.z != 0.0)
		valid_z = TRUE;
	else  // ray is parallel to XY planes
		if ((ray.origin.z < leftmost.z) || (ray.origin.z > rightmost.z))
			return FALSE;

	if (valid_x)
	{
		double tx1 = (leftmost.x - ray.origin.x) / ray.direction.x;
		double tx2 = (rightmost.x - ray.origin.x) / ray.direction.x;
		tnear = __min (tx1, tx2);
		tfar = __max (tx1, tx2);
		valid_t = TRUE;
	}

	if (valid_y)
	{
		double ty1 = (leftmost.y - ray.origin.y) / ray.direction.y;
		double ty2 = (rightmost.y - ray.origin.y) / ray.direction.y;
		double tn = __min (ty1, ty2);
		double tf = __max (ty1, ty2);
		if (valid_t)
		{
			tnear = __max (tnear, tn);
			tfar = __min (tfar, tf);
		}
		else
		{
			valid_t = TRUE;
			tnear = __min (ty1, ty2);
			tfar = __max (ty1, ty2);
		}
	}

	if (valid_z)
	{
		double tz1 = (leftmost.z - ray.origin.z) / ray.direction.z;
		double tz2 = (rightmost.z - ray.origin.z) / ray.direction.z;
		double tn = __min (tz1, tz2);
		double tf = __max (tz1, tz2);
		if (valid_t)
		{
			tnear = __max (tnear, tn);
			tfar = __min (tfar, tf);
		}
		else
		{
			valid_t = TRUE;
			tnear = __min (tz1, tz2);
			tfar = __max (tz1, tz2);
		}
	}

	if (tfar < tnear)
		return FALSE;
	else
	{
		if (tnear > E)
		{
			distance = tnear;
			point = CPoint3D (ray.origin.x + distance * ray.direction.x,
							ray.origin.y + distance * ray.direction.y,
							ray.origin.z + distance * ray.direction.z);
			return TRUE;
		}
		else if (tfar > E)
		{
			distance = tfar;
			point = CPoint3D (ray.origin.x + distance * ray.direction.x,
							ray.origin.y + distance * ray.direction.y,
							ray.origin.z + distance * ray.direction.z);
			return TRUE;
		}
		else
			return FALSE;
	}
}

BOOL CBox3D::IsIn (const CPoint3D& point) const
{
	return FALSE;
}

CVector3D CBox3D::GetN (const CPoint3D& point) const
{
	// point MUST belong to the box
	double dx = 0.0, dy = 0.0, dz = 0.0;
	double tx = rightmost.x - leftmost.x;
	double ty = rightmost.y - leftmost.y;
	double tz = rightmost.z - leftmost.z;

	if (fabs (point.x - leftmost.x) < E)
		dx = -tx;
	if (fabs (point.x - rightmost.x) < E)
		dx = tx;
	if (fabs (point.y - leftmost.y) < E)
		dy = -ty;
	if (fabs (point.y - rightmost.y) < E)
		dy = ty;
	if (fabs (point.z - leftmost.z) < E)
		dz = -tz;
	if (fabs (point.z - rightmost.z) < E)
		dz = tz;

	CVector3D N (dx, dy, dz);
	N.Normalize ();
	return N;
}

BOOL CBox3D::GetUV (const CPoint3D& point, double& u, double& v) const
{
	if (fabs (point.x - leftmost.x) < E) // left
	{
		u = (rightmost.z - point.z) / (rightmost.z - leftmost.z);
		v = (rightmost.y - point.y) / (rightmost.y - leftmost.y);
		return TRUE;
	}
	if (fabs (point.x - rightmost.x) < E) // right
	{
		u = (point.z - leftmost.z) / (rightmost.z - leftmost.z);
		v = (rightmost.y - point.y) / (rightmost.y - leftmost.y);
		return TRUE;
	}
	if (fabs (point.y - leftmost.y) < E) // bottom
	{
		u = (point.x - leftmost.x) / (rightmost.x - leftmost.x);
		v = (point.z - leftmost.z) / (rightmost.z - leftmost.z);
		return TRUE;
	}
	if (fabs (point.y - rightmost.y) < E) // top
	{
		u = (point.x - leftmost.x) / (rightmost.x - leftmost.x);
		v = (rightmost.z - point.z) / (rightmost.z - leftmost.z);
		return TRUE;
	}
	if (fabs (point.z - leftmost.z) < E) // front
	{
		u = (point.x - leftmost.x) / (rightmost.x - leftmost.x);
		v = (rightmost.y - point.y) / (rightmost.y - leftmost.y);
		return TRUE;
	}
	if (fabs (point.z - rightmost.z) < E) // rear
	{
		u = (rightmost.x - point.x) / (rightmost.x - leftmost.x);
		v = (rightmost.y - point.y) / (rightmost.y - leftmost.y);
		return TRUE;
	}
	return FALSE;
}

CPoint3D CBox3D::GetLocalXYZ (const CPoint3D& point) const
{
	return CPoint3D (point.x - leftmost.x, point.y - leftmost.y, point.z - leftmost.z);
}
