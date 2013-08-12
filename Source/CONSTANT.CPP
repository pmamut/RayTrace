#include "stdafx.h"
#include "lib3d.h"

CConstant::CConstant (const CColor& kd)
{
	Kd = kd;
}

CConstant::~CConstant ()
{
}

CColor CConstant::GetColor (const CPoint3D& point, CObject3D* object) const
{
	return Kd;
}
