/*************************************************************
Файл CheckBoxDlg.h
Copyright (c) 1999 Мешков А., Тихомиров Ю.
*************************************************************/

// CheckBoxDlg.h : header file
//

#include "ColorBox.h"

/////////////////////////////////////////////////////////////////////////////
// CCheckBoxDlg dialog

class CCheckBoxDlg : public CDialog
{
// Construction
public:
	CCheckBoxDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCheckBoxDlg)
	enum { IDD = IDD_CHECKBOX_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCheckBoxDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CColorBox m_CheckBox;

	// Generated message map functions
	//{{AFX_MSG(CCheckBoxDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
