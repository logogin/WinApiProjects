///////////////////////////////////////////////////////////
// ���� AppAbout.h
// Copyright (c) 1999 ������ �., ��������� �.
///////////////////////////////////////////////////////////

// AppAbout.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAppAbout dialog

class CAppAbout : public CDialog
{
// Construction
public:
	CAppAbout(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAppAbout)
	enum { IDD = IDD_ABOUTBOX };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAppAbout)
	//}}AFX_VIRTUAL

// Implementation

	// Generated message map functions
	//{{AFX_MSG(CAppAbout)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
