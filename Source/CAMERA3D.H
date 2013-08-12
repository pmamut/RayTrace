#ifndef _CAMERA_H_
#define _CAMERA_H_
class CCamera3D : public CObject
{
	public:
		CCamera3D (void);
		CCamera3D (const CPoint3D& source);
		CCamera3D (const double x, const double y, const double z);
		~CCamera3D (void);
		const CCamera3D& operator =(const CCamera3D& source);

		CPoint3D location;
};
#endif
