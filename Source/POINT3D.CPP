/////////////////////////////////////////////////////////////////////////////////////////////////
// CPoint3D implementation

#include "stdafx.h"
#include "lib3d.h"

CPoint3D::CPoint3D (void)
{
	x = 0.0;
	y = 0.0;
	z = 0.0;
}

CPoint3D::CPoint3D (const CPoint3D& source)
{
	x = source.x;
	y = source.y;
	z = source.z;
}

CPoint3D::CPoint3D (double source_x, double source_y, double source_z)
{
	x = source_x;
	y = source_y;
	z = source_z;
}

CPoint3D::~CPoint3D (void)
{
}

CPoint3D CPoint3D::operator +(const CPoint3D& second) const
{
	return CPoint3D (second.x + x, second.y + y, second.z + z);
}

CPoint3D CPoint3D::operator -(const CPoint3D& second) const
{
	return CPoint3D (x - second.x, y - second.y, z - second.z);
}

const CPoint3D& CPoint3D::operator =(const CPoint3D& source)
{
	x = source.x;
	y = source.y;
	z = source.z;
	return *this;
}

const CPoint3D& CPoint3D::operator +=(const CPoint3D& source)
{
	x += source.x;
	y += source.y;
	z += source.z;
	return *this;
}

const CPoint3D& CPoint3D::operator -=(const CPoint3D& source)
{
	x -= source.x;
	y -= source.y;
	z -= source.z;
	return *this;
}

BOOL CPoint3D::operator ==(const CPoint3D& second) const
{
	return ((x == second.x) && (y == second.y) && (z == second.z));
}

BOOL CPoint3D::operator !=(const CPoint3D& second) const
{
	return ((x != second.x) || (y != second.y) || (z != second.z));
}
