#ifndef _SPHERE_H_
#define _SPHERE_H_
class CSphere3D : public CObject3D
{
	public:
		CSphere3D ();
		~CSphere3D ();
		CSphere3D (const CPoint3D& c, const double r, CShader* sh, const CColor& ks, const double ph, const CColor& kr);
		CSphere3D (const double x, const double y, const double z, const double r, CShader* sh, const CColor& ks, const double ph, const CColor& kr);
		BOOL IsIntersection (const CRay3D& ray, CPoint3D& point, double& distance) const;
		BOOL IsIn (const CPoint3D& point) const;
		CVector3D GetN (const CPoint3D& point) const;
		BOOL GetUV (const CPoint3D& point, double& u, double& v) const;
		CPoint3D GetCorrectedXYZ (const CPoint3D& point) const;
		CPoint3D GetLocalXYZ (const CPoint3D& point) const;

		CPoint3D center;
		double radius;
};
#endif
