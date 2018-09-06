// ChildDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChildDlg dialog

class CChildDlg : public CDialog
{
// Construction
public:
	CChildDlg(HANDLE hThread, CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CChildDlg)
	enum { IDD = IDD_CHILD_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	HANDLE m_hThread; 

	// Generated message map functions
	//{{AFX_MSG(CChildDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
