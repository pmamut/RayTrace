// mainfrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////
#include "lib3d.h"

class CMainFrame : public CFrameWnd
{
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
	CModel3D NEAR model;
	BOOL bModelReady;
	BOOL bImageReady;
	BOOL bRendering;
	int nCurrentScanLine;
	CString FileName;

// Operations
public:
	void SetStatus (LPCSTR status);
	void SetPercent (long percent);
	BOOL ProcessIdle (LONG lCoubt);
	void Save (void);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
	afx_msg void OnRender();
	afx_msg void OnStopRender();
	afx_msg void OnUpdateOpen(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRender(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSave(CCmdUI* pCmdUI);
	afx_msg void OnUpdateStopRender(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
