#include "stdafx.h"
#include "math.h"
#include "lib3d.h"

/*
CWood::CWood (const CColor& d, const CColor& l)
{
	dark = d;
	light = l;
}
*/
CWood::CWood (void)
{
	 dark = CColor (0.3, 0.06, 0.03);
	 light = CColor (0.6, 0.24, 0.06);
}

CWood::~CWood (void)
{
}

CColor CWood::GetColor (const CPoint3D& point, CObject3D* object) const
{
	double radius, angle;
	int grain;
//	CPoint3D pt (object->GetLocalXYZ (point));
	CPoint3D pt (point);

	radius = sqrt (pt.y * pt.y + pt.z * pt.z);
	if (pt.z == 0.0)
		angle = PI / 2.0;
	else
		angle = atan2 (pt.y, pt.z);
	radius += 2.0 * sin (3.0 * angle + pt.x / 35.0);
	grain = (int) radius % 3;
	if (grain < 2)
		return light;
	else
		return dark;
}
