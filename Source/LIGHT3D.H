#ifndef _LIGHT_H_
#define _LIGHT_H_
class CLight3D : public CObject
{
	public:
		CLight3D (void);
		~CLight3D (void);
		CLight3D (const CPoint3D& loc, const CColor& ip);

		CPoint3D location;
		CColor Ip;
};
#endif
