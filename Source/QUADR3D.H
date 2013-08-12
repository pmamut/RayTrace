#ifndef _QUADRIC_H_
#define _QUADRIC_H_
class CQuadric3D : public CObject3D
{
	public:
		CQuadric3D ();
		~CQuadric3D ();
		CQuadric3D (const CPoint3D& c, const double r, const CColor& kd, const CColor& ks, const double ph);
		CQuadric3D (const double x, const double y, const double z, const double r,
				const double dr, const double dg, const double db,
				const double sr, const double sg, const double sb, const double ph);
		BOOL IsIntersection (const CRay3D& ray, CPoint3D& point, double& distance) const;
		BOOL IsIn (const CPoint3D& point) const;
		CVector3D GetN (const CPoint3D& point) const;

		CPoint3D center;
		double radius;
};
#endif
