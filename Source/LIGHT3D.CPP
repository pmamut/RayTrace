#include "stdafx.h"
#include "lib3d.h"

CLight3D::CLight3D (void)
{
}

CLight3D::CLight3D (const CPoint3D& loc, const CColor& ip)
{
	location = loc;
	Ip = ip;
}

CLight3D::~CLight3D (void)
{
}
