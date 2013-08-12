// raytrvw.h : interface of the CRaytraceView class
//
/////////////////////////////////////////////////////////////////////////////

class CRaytraceView : public CScrollView
{
protected: // create from serialization only
	CRaytraceView();
	DECLARE_DYNCREATE(CRaytraceView)

// Attributes
public:
	CRaytraceDoc* GetDocument();

// Operations
public:

// Members
public:

// Implementation
public:
	virtual ~CRaytraceView();
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void OnInitialUpdate(); // called first time after construct

// Generated message map functions
protected:
	//{{AFX_MSG(CRaytraceView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in raytrvw.cpp
inline CRaytraceDoc* CRaytraceView::GetDocument()
   { return (CRaytraceDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
