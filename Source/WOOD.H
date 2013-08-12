#ifndef _WOOD_H_
#define _WOOD_H_

class CWood : public CShader
{
	public:
//		CWood (const CColor& d = CColor (0.1, 0.02, 0.01), const CColor& l = CColor (0.6, 0.24, 0.06));
		CWood (void);
		~CWood (void);
		CColor GetColor (const CPoint3D& point, CObject3D* object) const;

		CColor dark, light;
};
#endif
