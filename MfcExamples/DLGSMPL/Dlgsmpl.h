//////////////////////////////////////////////////////////////
// Файл DlgSmpl.h
// Copyright (c) 1999 Мешков А., Тихомиров Ю.
//////////////////////////////////////////////////////////////

// DlgSmpl.h : main header file for the DLGSMPL application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDlgSmplApp:
// See DlgSmpl.cpp for the implementation of this class
//

class CDlgSmplApp : public CWinApp
{
public:
	CDlgSmplApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSmplApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDlgSmplApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
