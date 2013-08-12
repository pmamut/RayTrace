#ifndef _SCREEN_H_
#define _SCREEN_H_
class CScreen3D : public CObject
{
	public:
		CScreen3D (void);
		~CScreen3D (void);
		CScreen3D (const double xl, const double xr, const double yt, const double yb, const double z0 = 0.0, const int w = 1, const int h = 1);
		void Resample (void);
		void Reset (void);

		double xleft, xright, ytop, ybottom, z;
		double dx, dy;
		int width, height;
		CDIBitmap image;
};
#endif
