#ifndef _OBJECT_H_
#define _OBJECT_H_
class CObject3D : public CObject
{
	public:
		CObject3D ();
		virtual ~CObject3D ();
		virtual BOOL IsIntersection (const CRay3D& ray, CPoint3D& point, double& distance) const = FALSE;
		virtual BOOL IsIn (const CPoint3D& point) const = FALSE;
		virtual CVector3D GetN (const CPoint3D& point) const = 0;
		virtual BOOL GetUV (const CPoint3D& point, double& u, double& v) const = 0;
		virtual CPoint3D GetLocalXYZ (const CPoint3D& point) const;
		virtual CPoint3D GetCorrectedXYZ (const CPoint3D& point) const;

		CShader* shader;
		CColor Ks;
		double phong;
		CColor Kr;
};
#endif
