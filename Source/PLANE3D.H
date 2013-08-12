#ifndef _PLANE_H_
#define _PLANE_H_

class CPlane3D : public CObject3D
{
	public:
		CPlane3D ();
		~CPlane3D ();
		CPlane3D (const CVector3D& n, const double d, CShader* sh, const CColor& ks, const double ph, const CColor& kr);
		CPlane3D (const double x, const double y, const double z, const double d, CShader* sh, const CColor& ks, const double ph, const CColor& kr);
		BOOL IsIntersection (const CRay3D& ray, CPoint3D& point, double& distance) const;
		BOOL IsIn (const CPoint3D& point) const;
		CVector3D GetN (const CPoint3D& point) const;
		BOOL GetUV (const CPoint3D& point, double& u, double& v) const;

		CVector3D normal;
		double D;
};
#endif
