#ifndef _CONSTANT_H_
#define _CONSTANT_H_

class CConstant : public CShader
{
	public:
		CConstant (const CColor& kd = CColor (0.0, 0.0, 0.0));
		~CConstant ();
		CColor GetColor (const CPoint3D& point, CObject3D* object) const;

		CColor Kd;
};
#endif
