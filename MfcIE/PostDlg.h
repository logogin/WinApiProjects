#if !defined(AFX_POSTDLG_H__AD2B4249_CFA3_4C25_A5AF_CC1593CA89D7__INCLUDED_)
#define AFX_POSTDLG_H__AD2B4249_CFA3_4C25_A5AF_CC1593CA89D7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PostDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPostDlg dialog

class CPostDlg : public CDialog
{
// Construction
public:
	CString GetPostData(void);
	void SetPostData(const CString &strData);
	CPostDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPostDlg)
	enum { IDD = IDD_DIALOG_POST };
	CString	m_strData;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPostDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CString m_strPostData;

	// Generated message map functions
	//{{AFX_MSG(CPostDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POSTDLG_H__AD2B4249_CFA3_4C25_A5AF_CC1593CA89D7__INCLUDED_)
