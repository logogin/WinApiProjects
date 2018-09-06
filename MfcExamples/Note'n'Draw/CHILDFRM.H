// ChildFrm.h : interface of the CNoteFrame class
//
/////////////////////////////////////////////////////////////////////////////

class CNoteFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CNoteFrame)
protected:
	CNoteFrame();

// Attributes
public:

protected:
  CSplitterWnd m_spltWnd;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNoteFrame)
	public:
	virtual void ActivateFrame(int nCmdShow = -1);
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CNoteFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CNoteFrame)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CDrawFrame frame

class CDrawFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CDrawFrame)
protected:
	CDrawFrame();           // protected constructor used by dynamic creation

// Attributes
protected:
  CSplitterWnd m_splitWnd;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrawFrame)
	public:
	virtual void ActivateFrame(int nCmdShow = -1);
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CDrawFrame();

	// Generated message map functions
	//{{AFX_MSG(CDrawFrame)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
