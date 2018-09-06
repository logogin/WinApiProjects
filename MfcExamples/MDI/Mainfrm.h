///////////////////////////////////////////////////////////
// Файл MainFrm.h
// Copyright (c) 1999 Мешков А., Тихомиров Ю.
///////////////////////////////////////////////////////////

// MainFrm.h : interface of the CMainFrame class
//

class CMainFrame : public CMDIFrameWnd
{
// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	 afx_msg void OnText();
	 afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
