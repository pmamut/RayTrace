#include "stdafx.h"
#include "lib3d.h"

CColor::CColor (void)
{
	r = 0.0;
	g = 0.0;
	b = 0.0;
	black = TRUE;
}

CColor::~CColor (void)
{
}

CColor::CColor (const double srcr, const double srcg, const double srcb)
{
	r = srcr;
	g = srcg;
	b = srcb;
	black = (r == 0.0) && (g == 0.0) && (b == 0.0);
}

CColor::CColor (const CColor& source)
{
	r = source.r;
	g = source.g;
	b = source.b;
	black = source.black;
}

const CColor& CColor::operator =(const CColor& source)
{
	r = source.r;
	g = source.g;
	b = source.b;
	black = source.black;
	return *this;
}

const CColor& CColor::operator +=(const CColor& source)
{
	r += source.r;
	g += source.g;
	b += source.b;
	black = (r == 0.0) && (g == 0.0) && (b == 0.0);
	return *this;
}

CColor CColor::operator +(const CColor& color) const
{
	return CColor (r + color.r, g + color.g, b + color.b);
}

CColor CColor::operator *(const CColor& color) const
{
	return CColor (r * color.r, g * color.g, b * color.b);
}

CColor CColor::operator *(const double val) const
{
	return CColor (r * val, g * val, b * val);
}

CColor CColor::operator /(const double val) const
{
	return CColor (r / val, g / val, b / val);
}

void CColor::Clip (void)
{
	r = __min (__max (r, 0.0), 1.0);
	g = __min (__max (g, 0.0), 1.0);
	b = __min (__max (b, 0.0), 1.0);
	black = (r == 0.0) && (g == 0.0) && (b == 0.0);
}

BOOL CColor::IsBlack (void) const
{
	return black;
}
