/*************************************************************
Файл TermWnd.h
Copyright (c) 1999 Мешков А., Тихомиров Ю.
*************************************************************/

// TermWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTermWnd window

class CTermWnd : public CEdit
{
// Construction
public:
	CTermWnd();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTermWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTermWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTermWnd)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
