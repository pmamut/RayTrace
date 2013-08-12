#ifndef _VECTOR_H_
#define _VECTOR_H_
class CVector3D : public CObject
{
	public:
		CVector3D (void);
		CVector3D (const double dx, const double dy, const double dz);
		CVector3D (const CVector3D& source);
		CVector3D (const CPoint3D& source, const CPoint3D& dest);
		~CVector3D (void);
		double Normalize (void);
		void Revert (void);
		CVector3D operator +(const CVector3D& second) const;
		CVector3D operator -(const CVector3D& second) const;
		CVector3D operator *(const double val) const;
		double operator *(const CVector3D& second) const;
		const CVector3D& operator =(const CVector3D& source);
		const CVector3D& operator +=(const CVector3D& second);
		const CVector3D& operator -=(const CVector3D& second);
		const CVector3D& operator *=(const double val);
		BOOL operator ==(const CVector3D& second) const;
		BOOL operator !=(const CVector3D& second) const;

		double x,y,z;
};
#endif
