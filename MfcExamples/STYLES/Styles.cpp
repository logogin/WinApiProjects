/////////////////////////////////////////////////////////////
// Файл Styles.cpp
// Copyright (c) 1999 Мешков А., Тихомиров Ю.
/////////////////////////////////////////////////////////////

// Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Styles.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStylesApp

BEGIN_MESSAGE_MAP(CStylesApp, CWinApp)
	//{{AFX_MSG_MAP(CStylesApp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStylesApp construction

CStylesApp::CStylesApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CStylesApp object

CStylesApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CStylesApp initialization

BOOL CStylesApp::InitInstance()
{
 CMainFrame *pMainWnd = new CMainFrame;
 m_pMainWnd = pMainWnd;

 pMainWnd->LoadFrame(IDR_MAINFRAME);

 int cx = ::GetSystemMetrics(SM_CXSCREEN)/8;
 int cy = ::GetSystemMetrics(SM_CYSCREEN)/4;

 pMainWnd->SetWindowPos(NULL, cx, cy, 6*cx, 2*cy,
                        SWP_NOZORDER | SWP_SHOWWINDOW);
 	
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CStylesApp commands
