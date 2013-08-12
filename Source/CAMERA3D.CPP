#include "stdafx.h"
#include "lib3d.h"

CCamera3D::CCamera3D (void)
{
}

CCamera3D::CCamera3D (const CPoint3D& source)
{
	location = source;
}

CCamera3D::CCamera3D (const double x, const double y, const double z)
{
	location = CPoint3D (x, y, z);
}

CCamera3D::~CCamera3D (void)
{
}

const CCamera3D& CCamera3D::operator =(const CCamera3D& source)
{
	location = source.location;
	return *this;
}
