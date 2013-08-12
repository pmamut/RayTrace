#ifndef _COLOR_H_
#define _COLOR_H_
class CColor : public CObject
{
	public:
		CColor (void);
		~CColor (void);
		CColor (const double srcr, const double srcg, const double srcb);
		CColor (const CColor& source);
		void Clip (void);
		BOOL IsBlack (void) const;
		CColor operator +(const CColor& color) const;
		CColor operator *(const CColor& color) const;
		CColor operator *(const double val) const;
		CColor operator /(const double val) const;
		const CColor& operator +=(const CColor& source);
		const CColor& operator =(const CColor& source);

		double r,g,b;
		BOOL black;
};
#endif
