#ifndef _MODEL_H_
#define _MODEL_H_

class CModel3D : public CObject
{
	public:
		CModel3D (void);
		~CModel3D (void);
		BOOL Create (const CString& file);
		void Reset (void);
		void RenderScanLine (const int scanline);
		void TraceRay (const CRay3D& ray, const int depth, CColor& result);

	private:
		int GetInt (void);
		double GetDouble (void);
		CPoint3D GetPoint (void);
		CColor GetColor (void);
		CShader* GetShader (void);

	public:
		CCamera3D camera;
		CColor ambient_light;
		CColor background_color;
		CLightList lights;
		CObjectList objects;
		CScreen3D screen;
};
#endif
