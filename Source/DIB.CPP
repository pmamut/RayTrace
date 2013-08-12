#include "stdafx.h"
#include "dib.h"

CDIBitmap::CDIBitmap (void)
{
	width = 0;
	height = 0;
	nScanBytes = 0;
	lpBits = NULL;
	hBits = NULL;
}

CDIBitmap::~CDIBitmap (void)
{
	if (hBits)
	{
		GlobalUnlock (hBits);
		GlobalFree (hBits);
	}
}

void CDIBitmap::Reset (void)
{
	width = 0;
	height = 0;
	if (hBits)
	{
		GlobalUnlock (hBits);
		GlobalFree (hBits);
	}
	hBits = NULL;
	lpBits = NULL;
}

BOOL CDIBitmap::Create (const LONG w, const LONG h)
{
	BOOL ret = FALSE;
	if (!lpBits)
	{
		nScanBytes = (((w * 3 - 1) >> 2) << 2) + 4;
		hBits = GlobalAlloc (GHND, nScanBytes * h);
		if (hBits)
		{
			lpBits = (BYTE FAR*) GlobalLock (hBits);
			if (lpBits)
			{
				width = w;
				height = h;
				bih.biSize = sizeof (BITMAPINFOHEADER);
				bih.biWidth = w;
				bih.biHeight = h;
				bih.biPlanes = 1;
				bih.biBitCount = 24;
				bih.biCompression = BI_RGB;
				bih.biSizeImage = 0;
				bih.biXPelsPerMeter = 0;
				bih.biYPelsPerMeter = 0;
				bih.biClrUsed = 0;
				bih.biClrImportant = 0;
				ret = TRUE;
			}
			else
			{
				GlobalFree (hBits);
				hBits = NULL;
			}
		}
	}
	return ret;
}

BOOL CDIBitmap::Save (LPCSTR file)
{
	BOOL ret = FALSE;
	if (lpBits)
	{
		HFILE f = _lcreat (file, 0);
		if (f != HFILE_ERROR)
		{
			bfh.bfType = 'MB';
			bfh.bfSize = sizeof (BITMAPFILEHEADER) + sizeof (BITMAPINFOHEADER) + height * nScanBytes;
			bfh.bfReserved1 = 0;
			bfh.bfReserved2 = 0;
			bfh.bfOffBits = sizeof (BITMAPFILEHEADER) + sizeof (BITMAPINFOHEADER);
			if (_lwrite (f, &bfh, sizeof (BITMAPFILEHEADER)) == sizeof (BITMAPFILEHEADER))
			{
				if (_lwrite (f, &bih, sizeof (BITMAPINFOHEADER)) == sizeof (BITMAPINFOHEADER))
				{
					if (_hwrite (f, lpBits, height * nScanBytes) == height * nScanBytes)
						ret = TRUE;
				}
			}
			_lclose (f);
		}
	}
	return ret;
}

BOOL CDIBitmap::Load (LPCSTR file)
{
	BOOL ret = FALSE;
	Reset ();

	HFILE f = _lopen (file, READ);
	if (f != HFILE_ERROR)
	{
		if (_lread (f, &bfh, sizeof (BITMAPFILEHEADER)) == sizeof (BITMAPFILEHEADER))
		{
			if (bfh.bfType == 'MB')
			{
				if (_lread (f, &bih, sizeof (BITMAPINFOHEADER)) == sizeof (BITMAPINFOHEADER))
				{
					if ((bih.biSize == sizeof (BITMAPINFOHEADER)) &&
						(bih.biPlanes == 1) &&
						(bih.biBitCount == 24) &&
						(bih.biCompression == BI_RGB))
					{
						nScanBytes = (((bih.biWidth * 3 - 1) >> 2) << 2) + 4;
						hBits = GlobalAlloc (GHND, nScanBytes * bih.biHeight);
						if (hBits)
						{
							lpBits = (BYTE FAR*) GlobalLock (hBits);
							if (lpBits)
							{
								if (_hread (f, lpBits, nScanBytes * bih.biHeight) == nScanBytes * bih.biHeight)
								{
									width = bih.biWidth;
									height = bih.biHeight;
									ret = TRUE;
								}
								else
								{
									GlobalUnlock (hBits);
									GlobalFree (hBits);
									hBits = NULL;
									lpBits = NULL;
								}
							}
							else
							{
								GlobalFree (hBits);
								hBits = NULL;
							}
						}
					}
				}
			}
		}
		_lclose (f);
	}
	return ret;
}

void CDIBitmap::SetPixel (const LONG x, const LONG y, const BYTE r, const BYTE g, const BYTE b)
{
	BYTE _huge* lpTmp = (BYTE _huge*) lpBits + (height - y - 1) * nScanBytes + x * 3;
	*(lpTmp) = b;
	*(lpTmp + 1) = g;
	*(lpTmp + 2) = r;
}

void CDIBitmap::GetPixel (const LONG x, const LONG y, BYTE &r, BYTE &g, BYTE &b) const
{
	BYTE _huge* lpTmp = (BYTE _huge*) lpBits + (height - y - 1) * nScanBytes + x * 3;
	b = *(lpTmp);
	g = *(lpTmp + 1);
	r = *(lpTmp + 2);
}
 
void CDIBitmap::Paint (const HDC hdc, const int x_dest, const int y_dest, const int w_dest, const int h_dest,
						const int x_src, const int y_src, const int w_src, const int h_src) const
{
	StretchDIBits (hdc,
					x_dest, y_dest, w_dest ? w_dest : (int) width, h_dest ? h_dest : (int) height,
					x_src, y_src, w_src ? w_src : (int) width, h_src ? h_src : (int) height,
					lpBits,
					(BITMAPINFO FAR*) &bih,
					DIB_RGB_COLORS,
					SRCCOPY);
}
