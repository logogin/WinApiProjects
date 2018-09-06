// HotKeyFrm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHotKeyFrame frame

class CHotKeyFrame : public CFrameWnd
{
public:
	CHotKeyFrame(); 

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHotKeyFrame)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CHotKeyFrame();

	// Generated message map functions
	//{{AFX_MSG(CHotKeyFrame)
	afx_msg void OnPaint();
  afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
  afx_msg LONG OnHotKey(UINT nID, LPARAM lParam);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
