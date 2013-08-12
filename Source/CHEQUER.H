#ifndef _CHEQUER_H_
#define _CHEQUER_H_

class CChequer : public CShader
{
	public:
		CChequer (double step = 1.0, const CColor& d = CColor (0.0, 0.0, 0.0), const CColor& l = CColor (1.0, 1.0, 1.0));
		~CChequer ();
		CColor GetColor (const CPoint3D& point, CObject3D* object) const;

		CColor dark, light;
		double step_size;
};
#endif
