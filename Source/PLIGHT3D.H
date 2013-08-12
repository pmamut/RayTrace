class CPointLight3D : public CObject
{
	public:
		CPointLight3D (const CPoint3D& source) {origin = source;};
		~CPointLight3D ();
		CPoint3D origin;
};
