#ifndef _RAY_H_
#define _RAY_H_
class CRay3D : public CObject
{
	public:
		CRay3D (void);
		~CRay3D (void);
		CRay3D (const CPoint3D& org, const CVector3D& dir);
		CRay3D (const double orgx, const double orgy, const double orgz, const double destx, const double desty, const double destz);
		CRay3D (const CPoint3D& org, const CPoint3D& dest);

		CPoint3D origin;
		CVector3D direction;
		double length;
};
#endif
