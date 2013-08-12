#include "stdafx.h"
#include "math.h"
#include "lib3d.h"

CChequer::CChequer (double step, const CColor& d, const CColor& l)
{
	step_size = step;
	dark = d;
	light = l;
}

CChequer::~CChequer ()
{
}

CColor CChequer::GetColor (const CPoint3D& point, CObject3D* object) const
{
	// get # of cell
//	CPoint3D pt (object->GetCorrectedXYZ (object->GetLocalXYZ (point)));
	CPoint3D pt (object->GetCorrectedXYZ (point));
	int x = abs ((int) floor (pt.x / step_size));
	int y = abs ((int) floor (pt.y / step_size));
	int z = abs ((int) floor (pt.z / step_size));
	if ((long) (x + y + z) % 2)
		return light;
	else
		return dark;
}
