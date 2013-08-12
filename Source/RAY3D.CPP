#include "stdafx.h"
#include "lib3d.h"

CRay3D::CRay3D (void)
{
	length = 0.0;
}

CRay3D::~CRay3D (void)
{
}

CRay3D::CRay3D (const CPoint3D& org, const CVector3D& dir)
{
	origin = org;
	direction = dir;
	length = direction.Normalize ();
}

CRay3D::CRay3D (const CPoint3D& org, const CPoint3D& dest)
{
	origin = org;
	direction = CVector3D (org, dest);
	length = direction.Normalize ();
}

CRay3D::CRay3D (const double orgx, const double orgy, const double orgz, const double destx, const double desty, const double destz)
{
	CPoint3D org (orgx, orgy, orgz), dest (destx, desty, destz);
	origin = org;
	direction = CVector3D (org, dest);
	length = direction.Normalize ();
}
