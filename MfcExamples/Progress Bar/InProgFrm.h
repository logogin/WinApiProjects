// InProgFrm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInProgFrame frame

class CInProgFrame : public CFrameWnd
{
public:
	CInProgFrame(); 

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInProgFrame)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CInProgFrame();

	// Generated message map functions
	//{{AFX_MSG(CInProgFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:  // control bar embedded members
	CStatusBar m_wndStatusBar;
  CDialogBar m_wndDlgBar;
};

/////////////////////////////////////////////////////////////////////////////
