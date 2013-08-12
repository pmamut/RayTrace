// raytrdoc.h : interface of the CRaytraceDoc class
//
/////////////////////////////////////////////////////////////////////////////

class CRaytraceDoc : public CDocument
{
protected: // create from serialization only
	CRaytraceDoc();
	DECLARE_DYNCREATE(CRaytraceDoc)

// Attributes
public:
// Operations
public:

// Implementation
public:
	virtual ~CRaytraceDoc();
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual BOOL OnNewDocument();

// Generated message map functions
protected:
	//{{AFX_MSG(CRaytraceDoc)
	afx_msg void OnFSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
