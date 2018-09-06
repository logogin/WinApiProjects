///////////////////////////////////////////////////////////
// Файл MDIChilds.h
// Copyright (c) 1999 Мешков А., Тихомиров Ю.
///////////////////////////////////////////////////////////

// MDIChilds.h : header file
//

////////////////////////////////////////////////////////////
// CTextWnd frame

class CTextWnd : public CMDIChildWnd
{
public:
	CTextWnd();

// Implementation
protected:
 static CMenu    menu;     // меню для всех дочерних окон
 UINT     nIDColor;
 COLORREF clrText;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTextWnd)
	protected:
 	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CTextWnd)
	 afx_msg void OnColor();
	 afx_msg void OnPaint();
 	afx_msg void OnUpdateColor(CCmdUI* pCmdUI);
	 afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

////////////////////////////////////////////////////////////
