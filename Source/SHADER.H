#ifndef _SHADER_H_
#define _SHADER_H_

class CObject3D;

class CShader : public CObject
{
	public:
		CShader ();
		virtual ~CShader ();
		virtual CColor GetColor (const CPoint3D& point, CObject3D* object) const = 0;
};
#endif
