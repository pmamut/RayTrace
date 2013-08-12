#include "stdafx.h"
#include "math.h"
#include "lib3d.h"

CVector3D::CVector3D (void)
{
	x = 0.0;
	y = 0.0;
	z = 0.0;
}

CVector3D::~CVector3D (void)
{
}

CVector3D::CVector3D (const double dx, const double dy, const double dz)
{
	x = dx;
	y = dy;
	z = dz;
}

CVector3D::CVector3D (const CVector3D& source)
{
	x = source.x;
	y = source.y;
	z = source.z;
}

CVector3D::CVector3D (const CPoint3D& source, const CPoint3D& dest)
{
	x = dest.x - source.x;
	y = dest.y - source.y;
	z = dest.z - source.z;
}

double CVector3D::Normalize (void)
{
	double d = sqrt (x * x + y * y + z * z);
	if (d != 0.0)
	{
		x /= d;
		y /= d;
		z /= d;
	}
	return d;
}

void CVector3D::Revert (void)
{
	x *= -1.0;
	y *= -1.0;
	z *= -1.0;
}

//CVector3D CVector3D::Reverted (void)
//{
//	return CVector3D (x * -1.0, y * -1.0, z * -1.0);
//}

CVector3D CVector3D::operator +(const CVector3D& second) const
{
	return CVector3D (x + second.x, y + second.y, z + second.z);
}

CVector3D CVector3D::operator -(const CVector3D& second) const
{
	return CVector3D (x - second.x, y - second.y, z - second.z);
}

CVector3D CVector3D::operator *(const double val) const
{
	return CVector3D (x * val, y * val, z * val);
}

double CVector3D::operator *(const CVector3D& second) const
{
	return (x * second.x + y * second.y + z * second.z);
}

const CVector3D& CVector3D::operator =(const CVector3D& source)
{
	x = source.x;
	y = source.y;
	z = source.z;
	return *this;
}

const CVector3D& CVector3D::operator +=(const CVector3D& source)
{
	x += source.x;
	y += source.y;
	z += source.z;
	return *this;
}

const CVector3D& CVector3D::operator -=(const CVector3D& source)
{
	x -= source.x;
	y -= source.y;
	z -= source.z;
	return *this;
}

const CVector3D& CVector3D::operator *=(const double val)
{
	x *= val;
	y *= val;
	z *= val;
	return *this;
}

BOOL CVector3D::operator ==(const CVector3D& second) const
{
	return ((x == second.x) && (y == second.y) && (z == second.z));
}

BOOL CVector3D::operator !=(const CVector3D& second) const
{
	return ((x != second.x) || (y != second.y) || (z != second.z));
}
