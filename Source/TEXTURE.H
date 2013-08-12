#ifndef _TEXTURE_MAP_H_
#define _TEXTURE_MAP_H_

class CTexture : public CShader
{
	public:
		CTexture (LPCSTR name);
		~CTexture ();
		CColor GetColor (const CPoint3D& point, CObject3D* object) const;

		CDIBitmap bitmap;
};
#endif
