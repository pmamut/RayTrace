// raytrvw.cpp : implementation of the CRaytraceView class
//

#include "stdafx.h"
#include "raytrace.h"
#include "mainfrm.h"

#include "raytrdoc.h"
#include "raytrvw.h"
#include "stdio.h"
#include "string.h"
#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRaytraceView

IMPLEMENT_DYNCREATE(CRaytraceView, CScrollView)

BEGIN_MESSAGE_MAP(CRaytraceView, CScrollView)
	//{{AFX_MSG_MAP(CRaytraceView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRaytraceView construction/destruction

CRaytraceView::CRaytraceView()
{
}

CRaytraceView::~CRaytraceView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CRaytraceView drawing

void CRaytraceView::OnDraw(CDC* pDC)
{
	CRaytraceDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CMainFrame* main = (CMainFrame*) AfxGetMainWnd ();
	if (main->bImageReady)
		main->model.screen.image.Paint (pDC->GetSafeHdc ());
}

void CRaytraceView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 0;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

/////////////////////////////////////////////////////////////////////////////
// CRaytraceView diagnostics

#ifdef _DEBUG
void CRaytraceView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CRaytraceView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CRaytraceDoc* CRaytraceView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRaytraceDoc)));
	return (CRaytraceDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRaytraceView message handlers
