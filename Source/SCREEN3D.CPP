#include "stdafx.h"
#include "stdlib.h"
#include "lib3d.h"
#include "dib.h"

CScreen3D::CScreen3D (void)
{
	xleft = 0.0;
	xright = 0.0;
	ytop = 0.0;
	ybottom = 0.0;
	z = 0.0;
	dx = 0.0;
	dy = 0.0;
	width = 1;
	height = 1;
}

CScreen3D::~CScreen3D (void)
{
}

CScreen3D::CScreen3D (const double xl, const double xr, const double yt, const double yb, const double z0, const int w, const int h)
{
	xleft = __min (xl, xr);
	xright = __max (xl, xr);
	ytop = __max (yt, yb);
	ybottom = __min (yt, yb);
	z = z0;
	width = w == 0? 1 : w;
	height = h == 0? 1 : h;
	Resample ();
}

void CScreen3D::Resample (void)
{
	dx = width == 1? 0.0 : (xright - xleft) / (width - 1);
	dy = height == 1? 0.0 : (ytop - ybottom) / (height - 1);
}

void CScreen3D::Reset (void)
{
	xleft = 0.0;
	xright = 0.0;
	ytop = 0.0;
	ybottom = 0.0;
	z = 0.0;
	dx = 0.0;
	dy = 0.0;
	width = 1;
	height = 1;
}
