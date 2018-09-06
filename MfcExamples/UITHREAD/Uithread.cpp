/*************************************************************
Файл UIThread.cpp
Copyright (c) 1999 Мешков А., Тихомиров Ю.
*************************************************************/

// UIThread.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "UIThread.h"
#include "UIThreadFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUIThreadApp

BEGIN_MESSAGE_MAP(CUIThreadApp, CWinApp)
	//{{AFX_MSG_MAP(CUIThreadApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
    //    DO NOT EDIT what you see in these blocks of generated code!
  //}}AFX_MSG
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUIThreadApp construction

CUIThreadApp::CUIThreadApp()
{
	// TODO: add construction code here,
  // Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CUIThreadApp object

CUIThreadApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CUIThreadApp initialization

BOOL CUIThreadApp::InitInstance()
{
	// Standard initialization
  // If you are not using these features and wish to reduce the size
  //  of your final executable, you should remove from the following
  //  the specific initialization routines you do not need.

#ifdef _AFXDLL
  Enable3dControls();                     // Call this when using MFC in a shared DLL
#else
  Enable3dControlsStatic();       // Call this when linking to MFC statically
#endif

	CUIThreadFrame *pWnd = new CUIThreadFrame;
	m_pMainWnd = pWnd;

  pWnd->Create(NULL, _T("UIThread -- Бегущая строка"),
		WS_OVERLAPPEDWINDOW, CFrameWnd::rectDefault,
		NULL, IDR_UITHREAD);

	pWnd->CenterWindow();
  pWnd->ShowWindow(m_nCmdShow);
  pWnd->UpdateWindow();

  return TRUE;
}
