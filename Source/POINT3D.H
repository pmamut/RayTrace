#ifndef _POINT_H_
#define _POINT_H_
class CPoint3D : public CObject
{
	public:
		CPoint3D (void);
		CPoint3D (const CPoint3D& source);
		CPoint3D (double source_x, double source_y, double source_z);
		~CPoint3D (void);
		CPoint3D operator +(const CPoint3D& second) const;
		CPoint3D operator -(const CPoint3D& second) const;
		const CPoint3D& operator =(const CPoint3D& source);
		const CPoint3D& operator +=(const CPoint3D& source);
		const CPoint3D& operator -=(const CPoint3D& source);
		BOOL operator ==(const CPoint3D& second) const;
		BOOL operator !=(const CPoint3D& second) const;

		double x,y,z;
};
#endif
