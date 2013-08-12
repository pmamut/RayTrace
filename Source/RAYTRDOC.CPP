// raytrdoc.cpp : implementation of the CRaytraceDoc class
//

#include "stdafx.h"
#include "raytrace.h"

#include "mainfrm.h"
#include "raytrdoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRaytraceDoc

IMPLEMENT_DYNCREATE(CRaytraceDoc, CDocument)

BEGIN_MESSAGE_MAP(CRaytraceDoc, CDocument)
	//{{AFX_MSG_MAP(CRaytraceDoc)
	ON_COMMAND(ID_FILE_SAVE, OnFSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRaytraceDoc construction/destruction

CRaytraceDoc::CRaytraceDoc()
{
	// TODO: add one-time construction code here
}

CRaytraceDoc::~CRaytraceDoc()
{
}

BOOL CRaytraceDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CRaytraceDoc serialization

void CRaytraceDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CRaytraceDoc diagnostics

#ifdef _DEBUG
void CRaytraceDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CRaytraceDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

void CRaytraceDoc::OnFSave()
{
	CMainFrame* main = (CMainFrame*) AfxGetMainWnd ();
	main->Save ();
}
