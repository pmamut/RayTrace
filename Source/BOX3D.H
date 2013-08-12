#ifndef _BOX_H_
#define _BOX_H_

class CBox3D : public CObject3D
{
	public:
		CBox3D ();
		~CBox3D ();
		CBox3D (const CPoint3D& p1, const CPoint3D& p2, CShader* sh, const CColor& ks, const double ph, const CColor& kr);
		CBox3D (const double x1, const double y1, const double z1,
				const double x2, const double y2, const double z2,CShader* sh, const CColor& ks, const double ph, const CColor& kr);
		BOOL IsIntersection (const CRay3D& ray, CPoint3D& point, double& distance) const;
		BOOL IsIn (const CPoint3D& point) const;
		CVector3D GetN (const CPoint3D& point) const;
		BOOL GetUV (const CPoint3D& point, double& u, double& v) const;
		CPoint3D GetLocalXYZ (const CPoint3D& point) const;

		CPoint3D leftmost;
		CPoint3D rightmost;
};
#endif
