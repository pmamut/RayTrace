// DIBitmap.h 
// 

#ifndef __DIBITMAP_H
#define __DIBITMAP_H

#include <windows.h>

class FAR DIBitmap
{
    public:
        DIBitmap();
        ~DIBitmap();
        
        void ClearBitmap();

        BOOL            Create(const char* name)    { return ReadFromFile(name); }        
        BOOL            ReadFromFile(const char* name);         // load bitmap from a file
        
        LPBITMAPINFO    BitmapInfo() const;                     
        WORD            BitCount() const;
        DWORD           ColorsUsed() const;
        BYTE __huge*    Bits() const;
        DWORD           Height() const;
        DWORD           Width() const;
        DWORD           InfoSize() const;
        DWORD           Size() const;
        BYTE __huge*    Data() const;
        DWORD           ImageSize() const;
        
        BOOL            Paint(HDC hdc, DWORD ropCode = SRCCOPY, int destXRes = 0, int destYRes = 0);
        
//      BOOL            CreateDIB(DWORD wid, DWORD hgt, int xdpi, int ydpi, DWORD count, BYTE __huge* bits);

        BOOL            Create(HBITMAP hbmp)        { return CreateDIB(hbmp); } 
        BOOL            CreateDIB(HBITMAP hbmp);
        
        BOOL            Create(DWORD dwCount, BYTE __huge* data)    
                                { return CreateDIB(dwCount, data); } 
                                
        BOOL            CreateDIB(DWORD dwCount, BYTE __huge* data);
        void            SetXOffset(int newx);
        void            SetYOffset(int newy);
        void            SetXDest(int x);
        void            SetYDest(int y);
        void            SetXRes(int x);
        void            SetYRes(int y);
                
    protected: 
        HGLOBAL         hDib;
        BYTE __huge*    dibData;
        
        // functions for creating dib from ddb
        void InitInfoHeader(LPBITMAPINFOHEADER, DWORD, DWORD, int);
        WORD PaletteSize(LPBITMAPINFOHEADER);
        WORD NumColors(LPBITMAPINFOHEADER);
        
    private:
        int     status;
        int     xOffset;
        int     yOffset;
        int     xDest;
        int     yDest;
        int     xRes;
        int     yRes;
};


#endif




