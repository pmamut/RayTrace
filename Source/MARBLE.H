#ifndef _TEXTURE_MAP_H_
#define _TEXTURE_MAP_H_

class CObject3D;

class CTextureMap : public CObject
{
	public:
		CTextureMap ();
		~CTextureMap ();
		virtual CColor3D (const CPoint3D& point, CObject3D* object) const = 0;
};
#endif
