#ifndef _DIB_H_
#define _DIB_H_

class CDIBitmap : public CObject
{
	public:
		CDIBitmap (void);
		~CDIBitmap (void);
		BOOL Create (const LONG w, const LONG h);
		BOOL Load (LPCSTR file);
		BOOL Save (LPCSTR file);
		void Paint (const HDC hdc, const int x_dest = 0, const int y_dest = 0, const int w_dest = 0, const int h_dest = 0,
					const int x_src = 0, const int y_src = 0, const int w_src = 0, const int h_src = 0) const;
		void SetPixel (const LONG x, const LONG y, const BYTE r, const BYTE g, const BYTE b);
		void GetPixel (const LONG x, const LONG y, BYTE &r, BYTE &g, BYTE &b) const;
		void Reset (void);
		LONG Width (void) const { return width; };
		LONG Height (void) const { return height; };

	private:
		HGLOBAL hBits;
		BYTE FAR* lpBits;
		BITMAPINFOHEADER bih;
		BITMAPFILEHEADER bfh;
		LONG width, height, nScanBytes;
};
#endif
