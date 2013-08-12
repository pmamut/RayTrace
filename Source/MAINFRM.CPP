// mainfrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "raytrace.h"

#include "mainfrm.h"
#include "message.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_FILE_RENDER, OnRender)
	ON_COMMAND(ID_FILE_STOP_RENDER, OnStopRender)
	ON_UPDATE_COMMAND_UI(ID_FILE_OPEN, OnUpdateOpen)
	ON_UPDATE_COMMAND_UI(ID_FILE_RENDER, OnUpdateRender)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateSave)
	ON_UPDATE_COMMAND_UI(ID_FILE_STOP_RENDER, OnUpdateStopRender)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// arrays of IDs used to initialize control bars

// toolbar buttons - IDs are command buttons
static UINT BASED_CODE buttons[] =
{
	// same order as in the bitmap 'toolbar.bmp'
	ID_FILE_OPEN,
	ID_FILE_SAVE,
		ID_SEPARATOR,
	ID_FILE_RENDER,
	ID_FILE_STOP_RENDER,
		ID_SEPARATOR,
	ID_APP_ABOUT,
};

static UINT BASED_CODE indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_SEPARATOR,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadBitmap(IDR_MAINFRAME) ||
		!m_wndToolBar.SetButtons(buttons,
		  sizeof(buttons)/sizeof(UINT)))
	{
		TRACE("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE("Failed to create status bar\n");
		return -1;      // fail to create
	}

	m_wndToolBar.SetButtonInfo (3, ID_FILE_RENDER, TBBS_BUTTON, 4);
	m_wndToolBar.SetButtonInfo (4, ID_FILE_STOP_RENDER, TBBS_BUTTON, 5);
	m_wndToolBar.SetButtonInfo (6, ID_APP_ABOUT, TBBS_BUTTON, 2);

	m_wndStatusBar.SetPaneInfo (0, ID_SEPARATOR, SBPS_STRETCH, 160);
	m_wndStatusBar.SetPaneInfo (1, ID_SEPARATOR, 0, 50);

	bModelReady = FALSE;
	bImageReady = FALSE;
	bRendering = FALSE;
	nCurrentScanLine = 0;

	return 0;
}

void CMainFrame::SetStatus (LPCSTR status)
{
	m_wndStatusBar.SetPaneText (0, status, TRUE);
}

void CMainFrame::SetPercent (long percent)
{
	if (percent < 0)
		m_wndStatusBar.SetPaneText (1, "", TRUE);
	else
	{
		char buf [64];
		wsprintf (buf, "   %li%%", percent);
		m_wndStatusBar.SetPaneText (1, buf, TRUE);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

BOOL CMainFrame::ProcessIdle (LONG lCount)
{
	if (bRendering)
	{
		SetPercent ((long) nCurrentScanLine * 100 / model.screen.height);
		model.RenderScanLine (nCurrentScanLine++);
		if (nCurrentScanLine == model.screen.height)
		{
			nCurrentScanLine = 0;
			bRendering = FALSE;
			bImageReady = TRUE;
			SetStatus ("Done ...");
			SetPercent (100);
			CSize sizeTotal;
			sizeTotal.cx = model.screen.width;
			sizeTotal.cy = model.screen.height;
			((CScrollView *) GetActiveView ())->SetScrollSizes(MM_TEXT, sizeTotal);
			InvalidateRect (NULL);
			return FALSE;
		}
		return TRUE;
	}
	else
		return FALSE;
}

void CMainFrame::OnFileOpen()
{
	CFileDialog of (TRUE,
					NULL,
					NULL,
					OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_PATHMUSTEXIST,
					"Model Files (*.dat)|*.dat|All Files (*.*)|*.*||",
					this);
	if (IDOK == of.DoModal ())
	{
		CString name = of.GetPathName ();
		bModelReady = FALSE;
		bImageReady = FALSE;
		model.Reset ();
		CSize sizeTotal;
		sizeTotal.cx = sizeTotal.cy = 0;
		((CScrollView *) GetActiveView ())->SetScrollSizes(MM_TEXT, sizeTotal);
		InvalidateRect (NULL);
		if (model.Create (name))
		{
			bModelReady = TRUE;
			FileName = of.GetFileName ();
			GetActiveDocument ()->SetTitle (FileName);
			SetPercent (-1);
			SetStatus ("Model was successfully loaded form " + name);
		}
		else
		{
			MessageBox ("Can't create a model.\n" + name + " may not be a valid model description file.", "RayTrace", MB_ICONSTOP);
			GetActiveDocument ()->SetTitle ("Empty Model");
		}
	}
}

void CMainFrame::OnFileSave()
{
	CFileDialog sf (FALSE,
					NULL,
					FileName + ".bmp",
					OFN_HIDEREADONLY | OFN_PATHMUSTEXIST | OFN_NOREADONLYRETURN | OFN_OVERWRITEPROMPT,
					"Bitmap Files (*.dib, *.bmp)|*.dib;*.bmp||",
					this);
	if (IDOK == sf.DoModal ())
	{
		CString name = sf.GetPathName ();
		if (!model.screen.image.Save (name))
			MessageBox ("Can't save an image into " + name + "\nThe drive may be full.", "RayTrace", MB_ICONSTOP);
		else
			SetStatus ("Image was successfully saved to " + name);
	}
}

void CMainFrame::OnRender()
{
		nCurrentScanLine = 0;
		bImageReady = FALSE;
		bRendering = TRUE;
		CSize sizeTotal;
		sizeTotal.cx = sizeTotal.cy = 0;
		((CScrollView *) GetActiveView ())->SetScrollSizes(MM_TEXT, sizeTotal);
		InvalidateRect (NULL);
		SetPercent (-1);
		SetStatus ("Rendering ...");
}

void CMainFrame::Save (void)
{
	OnFileSave ();
}

void CMainFrame::OnStopRender()
{
	bRendering = FALSE;
	bImageReady = FALSE;
	nCurrentScanLine = 0;
	SetPercent (-1);
	SetStatus ("Rendering terminated");
}

void CMainFrame::OnUpdateOpen(CCmdUI* pCmdUI)
{
	pCmdUI->Enable (!bRendering);
}

void CMainFrame::OnUpdateRender(CCmdUI* pCmdUI)
{
	pCmdUI->Enable (bModelReady && (!bRendering));
}

void CMainFrame::OnUpdateSave(CCmdUI* pCmdUI)
{
	pCmdUI->Enable (bImageReady && (!bRendering));
}

void CMainFrame::OnUpdateStopRender(CCmdUI* pCmdUI)
{
	pCmdUI->Enable (bRendering);
}
