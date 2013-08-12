#include "stdafx.h"
#include "lib3d.h"

CTexture::CTexture (LPCSTR name)
{
	if (!bitmap.Load (name))
	{
		bitmap.Reset ();
		bitmap.Create (1, 1);
		bitmap.SetPixel (0, 0, 255, 255, 255);
	}
}

CTexture::~CTexture ()
{
}

CColor CTexture::GetColor (const CPoint3D& point, CObject3D* object) const
{
	double u,v;
	double r = 1.0, g = 1.0, b = 1.0;
	if (object->GetUV (point, u, v))
	{
		LONG x = (LONG) (u * (bitmap.Width () - 1));
		LONG y = (LONG) (v * (bitmap.Height () - 1));
		BYTE rr, gg, bb;
		bitmap.GetPixel (x, y, rr, gg, bb);
		r = (double) rr / 255.0;
		g = (double) gg / 255.0;
		b = (double) bb / 255.0;
	}
	return CColor (r, g, b);
}
