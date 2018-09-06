///////////////////////////////////////////////////////////
// Файл Template.h
// Copyright (c) 1997 Мешков А., Тихомиров Ю.
///////////////////////////////////////////////////////////

// Template.h : Основной включаемый файл приложения Template
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

///////////////////////////////////////////////////////////
// CTemplateApp:

class CTemplateApp : public CWinApp{
public:
	CTemplateApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTemplateApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTemplateApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
