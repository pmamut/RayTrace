// dibitmap.cpp
#include "stdafx.h"

#include "dibitmap.h"
#include <windows.h>

DIBitmap::DIBitmap()
{
    hDib = NULL;
    dibData = NULL;
    status = 0;
    xOffset = 0;
    yOffset = 0;
    xDest = 0;
    yDest = 0;
    xRes = 0;
    yRes = 0;
    //MessageBox(NULL, "Constructor called", "DIBitmap", MB_OK);
}


DIBitmap::~DIBitmap()
{
    //MessageBox(NULL, "Destructor called", "DIBitmap", MB_OK);
    ClearBitmap();
}


void DIBitmap::ClearBitmap()
{
    if (hDib)
    {
        GlobalUnlock(hDib);
        GlobalFree(hDib);
        hDib = NULL;
        dibData = NULL;
        //MessageBox(NULL, "Freed Global Memory", "DIBitmap", MB_OK);

    }
}


BOOL DIBitmap::ReadFromFile(const char* name)
{
    BITMAPFILEHEADER bmfh;
    DWORD            dwDibSize, dwOffset, dwHeaderSize;
    int              hFile;
    WORD             wDibRead;

    ClearBitmap();
    
    if (-1 == (hFile = _lopen (name, OF_READ | OF_SHARE_DENY_WRITE)))
    {
        return FALSE;
    }


    if (_lread (hFile, (LPSTR) &bmfh, sizeof (BITMAPFILEHEADER)) !=
                                       sizeof (BITMAPFILEHEADER))
    {
        _lclose (hFile);
        return FALSE;
    }

    if (bmfh.bfType != * (WORD *) "BM")
    {
        _lclose (hFile);
        return FALSE;
    }

    dwDibSize = bmfh.bfSize - sizeof (BITMAPFILEHEADER);
    hDib = GlobalAlloc(GMEM_MOVEABLE, dwDibSize);
    dibData = (BYTE __huge*) GlobalLock(hDib);

    if (dibData == NULL)
    {
        _lclose (hFile);
        return FALSE;
    }
    //else 
        //MessageBox(NULL, "Allocated Global Memory", "DIBitmap", MB_OK);

    dwOffset = 0;

    while (dwDibSize > 0)
    {
        wDibRead = (WORD) (32768ul < dwDibSize ? 32768ul : dwDibSize);

        if (wDibRead != _lread (hFile, (LPSTR) (dibData + dwOffset), wDibRead))
        {
            _lclose (hFile);
            GlobalUnlock(hDib);
            GlobalFree(hDib);
            dibData = NULL;
            return FALSE;
        }

        dwDibSize -= wDibRead;
        dwOffset  += wDibRead;
    }

    _lclose (hFile);

    dwHeaderSize = InfoSize();

    if (dwHeaderSize < 12 || (dwHeaderSize > 12 && dwHeaderSize < 16))
    {
        GlobalUnlock(hDib);
        GlobalFree(hDib);
        dibData = NULL;
        return FALSE;
    }
    return TRUE;
}


BOOL DIBitmap::CreateDIB(HBITMAP hbmp)
{
    // if not a valid handle, no dice
    if (!hbmp)
        return FALSE;
        
    // get bitmap information
    BITMAP bmp;
    GetObject(hbmp, sizeof(bmp), &bmp);
         
    ClearBitmap();

        
    BITMAPINFOHEADER bmi;
    InitInfoHeader(&bmi, bmp.bmWidth, bmp.bmHeight, 
            bmp.bmPlanes * bmp.bmBitsPixel);

    // get memory sizeable enough to hold entire bitmap 
    hDib    = GlobalAlloc(GHND, sizeof(BITMAPINFOHEADER) + 
                PaletteSize(&bmi) + 
                bmi.biSizeImage);
                
    dibData = (BYTE __huge*) GlobalLock(hDib);
                
    if (!dibData)
    {
        return FALSE;
    }
    //else
        //MessageBox(NULL, "Allocated Global Memory", "DIBitmap", MB_OK);

    // put header information into place
    *((LPBITMAPINFOHEADER) dibData) = bmi;
                  
    // select bitmap into a memory device context compatible with the display
    CDC memDC;
    memDC.CreateCompatibleDC(NULL);
    HDC hdc = memDC.GetSafeHdc();
    
    ASSERT(hdc != NULL);
    
    // get bitmap
    int lines = GetDIBits(hdc, hbmp, 0, bmp.bmHeight, Bits(), BitmapInfo(), DIB_RGB_COLORS) ? TRUE : FALSE;
    
    if (lines == 0)
    {
        //char buf[80];
        //sprintf(buf, "%d", lines);
        //MessageBox(NULL, buf, "lines copied", MB_OK);
        
        GlobalUnlock(hDib);
        GlobalFree(hDib);
        hDib = NULL;
    }

    BOOL ret = (lines != 0);    
    return ret;
}


// create from a buffer and a size...
// todo: add some validation that this is a good bitmap
BOOL DIBitmap::CreateDIB(DWORD dwCount, BYTE __huge* data)
{
    hDib = GlobalAlloc(GHND, dwCount);
    dibData = (BYTE __huge*) GlobalLock(hDib);
    
    if (dibData == NULL)
    {
        ASSERT(FALSE);
        return FALSE;
    }
        
    BYTE __huge* p = data; 
    BYTE __huge* q = dibData;
    
    DWORD bytesLeft = dwCount;
    
    WORD dibRead;
    while (bytesLeft > 0)
    {
        dibRead = (WORD) (32768ul < bytesLeft ? 32768ul : bytesLeft);
        _fmemcpy(q, p, dibRead);
        p += dibRead;
        q += dibRead;
        bytesLeft -= dibRead;
    }
    return TRUE;    
}   


// returns a pointer to the information header
LPBITMAPINFO DIBitmap::BitmapInfo() const
{
    return (LPBITMAPINFO) dibData;
}


// returns the number of bits necessary to represent one pixel
WORD DIBitmap::BitCount() const
{
    return ((BITMAPINFOHEADER __huge*) dibData)->biBitCount;
}


// returns the number of entries in color table 
DWORD DIBitmap::ColorsUsed() const
{
    DWORD ret;
    
    if (InfoSize() >= 36)
        ret = ((BITMAPINFOHEADER __huge*) dibData)->biClrUsed; 
    else
        ret = 0;
    
    if (!ret) 
    {
        if (BitCount() != 24)
            ret = 1L << BitCount();
        else 
            ret = 0;
    }
    
    return ret;
}


// returns a pointer to the "bits"
BYTE __huge* DIBitmap::Bits() const
{
    DWORD   dwColorTableSize = ColorsUsed() * sizeof(RGBQUAD);
    
    return dibData + InfoSize() + dwColorTableSize;     
}


// returns the height of the bitmap in pixels
DWORD DIBitmap::Height() const
{
    return ((BITMAPINFOHEADER __huge*) dibData)->biHeight;  
}


// returns the width of the bitmap in pixels
DWORD DIBitmap::Width() const
{
    return ((BITMAPINFOHEADER __huge*) dibData)->biWidth;
}



// returns the size of the bitmap information header
DWORD DIBitmap::InfoSize() const
{
    return ((BITMAPINFOHEADER __huge*) dibData)->biSize;    
}


BOOL DIBitmap::Paint(HDC hDC, DWORD ropCode, int destXRes, int destYRes)
{
    // if there is no bitmap, don't paint one
    if (hDib == NULL)
        return FALSE;
        
    SetStretchBltMode(hDC, COLORONCOLOR);
    
    // determine if bitmap needs to be scaled
    // SetDIBitsToDevice is much faster, so if we can use it we should
    BOOL actualSize = (destXRes == xRes && destYRes == yRes) 
                        || (destXRes == 0 && destYRes == 0);
                        
    // if using a raster operation other than SRCCOPY, 
    // we have to use StretchDIBits
    BOOL stretchit = (ropCode != SRCCOPY) || !actualSize;
    
    /***************************************************
    char buf[40];
    sprintf(buf, "X: %d; Y: %d", xDest, yDest);
    MessageBox(NULL, buf, "Bitmap Destination", MB_OK);
    *****************************************************/
                                             
    if (!stretchit)
    {
        // render bitmap on hdc exactly as is
        SetDIBitsToDevice(hDC,
                        xDest - xOffset,
                        yDest - yOffset,
                        (int) Width(),
                        (int) Height(),
                        0,
                        0,
                        0,
                        (UINT) Height(), 
                        (LPSTR) Bits(),
                        BitmapInfo(),
                        DIB_RGB_COLORS);
    }
    else 
    {
        // scale image to appear actual size on whatever device
        DWORD destWidth = Width(); 
        DWORD destHeight = Height();
        
        if (!actualSize)
        {
            destWidth  = destWidth * (DWORD) destXRes / (DWORD) xRes;
            destHeight = destHeight * (DWORD) destYRes / (DWORD) yRes;
        }
        
        // stretch bitmap to fit 
        long l = StretchDIBits(hDC,
                        xDest - xOffset,
                        yDest - yOffset,
                        (int) destWidth,
                        (int) destHeight,
                        0, //xOffset,
                        0, //yOffset,
                        (int) Width(), // - xOffset,
                        (int) Height(), // + yOffset,
                        (LPSTR) Bits(),
                        BitmapInfo(),
                        DIB_RGB_COLORS,
                        ropCode);
        
        /*********************************************              
        char buf[40];
        sprintf(buf, "%ld", l);
        MessageBox(NULL, buf, "lines copied", MB_OK);
        *********************************************/
    }
    
    return TRUE;
}


void DIBitmap::SetXOffset(int x)
{
    xOffset = x;
}


void DIBitmap::SetXDest(int x)
{
    xDest = x;
}


void DIBitmap::SetYOffset(int y)
{
    yOffset = y;
}


void DIBitmap::SetYDest(int y)
{
    yDest = y;
}


void DIBitmap::SetXRes(int x)
{
    xRes = x;
}


void DIBitmap::SetYRes(int y)
{
    yRes = y;
}

#define WIDTHBYTES(bits)      (((bits) + 31) / 32 * 4)

void DIBitmap::InitInfoHeader(LPBITMAPINFOHEADER lpInfoHdr, 
        DWORD dwWidth, 
        DWORD dwHeight, 
        int nBitCount)
{
    _fmemset(lpInfoHdr, 0, sizeof(BITMAPINFOHEADER));
    lpInfoHdr->biSize = sizeof(BITMAPINFOHEADER);
    lpInfoHdr->biWidth = dwWidth;
    lpInfoHdr->biHeight = dwHeight;
    lpInfoHdr->biPlanes = 1;
    
    if (nBitCount <= 1)
        nBitCount = 1;
    else if (nBitCount <= 4)
        nBitCount = 4;
    else if (nBitCount <= 8)
        nBitCount = 8;
    else 
        nBitCount = 24;
        
    lpInfoHdr->biBitCount = nBitCount;
    lpInfoHdr->biSizeImage = WIDTHBYTES(dwWidth * nBitCount) * dwHeight;
}


WORD DIBitmap::PaletteSize(LPBITMAPINFOHEADER lpBmi)
{
    return NumColors(lpBmi) * sizeof(RGBQUAD);
}
 
 
WORD DIBitmap::NumColors(LPBITMAPINFOHEADER lpBmi)
{
    if (lpBmi->biClrUsed)
        return (WORD) lpBmi->biClrUsed;
        
    switch(lpBmi->biBitCount)
    {
        case 1:     return 2;
        case 4:     return 16;
        case 8:     return 256; 
        default:    return 0;
    }
}


DWORD DIBitmap::Size() const
{
    if (dibData)
        return InfoSize() + ColorsUsed() * sizeof(RGBQUAD) + ImageSize();
    else 
        return 0ul;
}


BYTE __huge* DIBitmap::Data() const
{
    return dibData;
}


DWORD DIBitmap::ImageSize() const
{
    return ((BITMAPINFOHEADER __huge*) dibData)->biSizeImage;
}