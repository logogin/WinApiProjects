// DragListDlg.h : header file
//

#include "DragBox.h"

/////////////////////////////////////////////////////////////////////////////
// CDragListDlg dialog

class CDragListDlg : public CDialog
{
// Construction
public:
	CDragListDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDragListDlg)
	enum { IDD = IDD_DRAGLIST_DIALOG };
	CDragBox	m_DragList;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDragListDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDragListDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
