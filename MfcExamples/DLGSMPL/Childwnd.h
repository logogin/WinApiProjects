//////////////////////////////////////////////////////////////
// Файл ChildWnd.h
// Copyright (c) 1999 Мешков А., Тихомиров Ю.
//////////////////////////////////////////////////////////////

// ChildWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChildWnd frame

class CChildWnd : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CChildWnd)
public:
	CChildWnd();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildWnd)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	static CMenu    menu;
 static COLORREF aCustom[16];
        UINT     nIDColor;
        COLORREF clrText;

 virtual ~CChildWnd();

	// Generated message map functions
	//{{AFX_MSG(CChildWnd)
	afx_msg void OnPaint();
	afx_msg void OnCustom();
 afx_msg void OnColor(UINT nID);
 afx_msg void OnUpdateColor(CCmdUI *pCmdUI);//, UINT nID);
	afx_msg void OnFont();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
