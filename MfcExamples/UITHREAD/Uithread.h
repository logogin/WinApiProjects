/*************************************************************
Файл UIThread.h
Copyright (c) 1999 Мешков А., Тихомиров Ю.
*************************************************************/

// UIThread.h : main header file for the TEMPLATE application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CUIThreadApp:
// See UIThread.cpp for the implementation of this class
//

class CUIThreadApp : public CWinApp
{
public:
	CUIThreadApp();

// Attributes
public:
	CString m_Text;
	CMutex m_TextLock;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUIThreadApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CUIThreadApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
