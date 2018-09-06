/////////////////////////////////////////////////////////
// Файл Template.cpp
// Copyright (c) 1999 Мешков А., Тихомиров Ю.
/////////////////////////////////////////////////////////

// Template.cpp : Реализация основного класса приложения
//

#include "stdafx.h"
#include "Template.h"
#include "TempDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////
// CTemplateApp

BEGIN_MESSAGE_MAP(CTemplateApp, CWinApp)
	//{{AFX_MSG_MAP(CTemplateApp)
	//}}AFX_MSG
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////
// Конструктор CTemplateApp

CTemplateApp::CTemplateApp(){
}

///////////////////////////////////////////////////////////
// The one and only CTemplateApp object

CTemplateApp theApp;

///////////////////////////////////////////////////////////
// CTemplateApp initialization

BOOL CTemplateApp::InitInstance(){
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CTemplateDlg dlg;
	m_pMainWnd = &dlg;

	int nResponse = dlg.DoModal();
	
	return FALSE;
}
