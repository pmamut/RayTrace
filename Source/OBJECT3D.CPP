#include "stdafx.h"
#include "lib3d.h"

CObject3D::CObject3D ()
{
	phong = 0.0;
	shader = NULL;
}

CObject3D::~CObject3D ()
{
	if (shader)
		delete shader;
}

CPoint3D CObject3D::GetCorrectedXYZ (const CPoint3D& point) const
{
	return point;
}

CPoint3D CObject3D::GetLocalXYZ (const CPoint3D& point) const
{
	return point;
}
