// raytrace.h : main header file for the RAYTRACE application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CRaytraceApp:
// See raytrace.cpp for the implementation of this class
//

class CRaytraceApp : public CWinApp
{
public:
	CRaytraceApp();

// Overrides
	virtual BOOL InitInstance();
	virtual BOOL OnIdle (LONG lCount);

// Implementation

	//{{AFX_MSG(CRaytraceApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
