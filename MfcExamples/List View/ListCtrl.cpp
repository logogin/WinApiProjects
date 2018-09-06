// ListCtrl.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ListCtrl.h"
#include "ListCtrlFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListCtrlApp

BEGIN_MESSAGE_MAP(CListCtrlApp, CWinApp)
	//{{AFX_MSG_MAP(CListCtrlApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
    //    DO NOT EDIT what you see in these blocks of generated code!
  //}}AFX_MSG
  ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListCtrlApp construction

CListCtrlApp::CListCtrlApp()
{
	// TODO: add construction code here,
  // Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CListCtrlApp object

CListCtrlApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CListCtrlApp initialization

BOOL CListCtrlApp::InitInstance()
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

	CListCtrlFrame *pWnd = new CListCtrlFrame;
	m_pMainWnd = pWnd;

	int nSizeX = (int)(GetSystemMetrics(SM_CXMAXIMIZED) * 0.5);
	int nSizeY = (int)(GetSystemMetrics(SM_CYMAXIMIZED) * 0.4);

	pWnd->Create(NULL, _T("ListCtrl -- CListCtrl"),
		WS_OVERLAPPEDWINDOW, 
		CRect(0, 0, nSizeX, nSizeY), NULL, MAKEINTRESOURCE(IDR_LISTCTRL));

	pWnd->CenterWindow();
  pWnd->ShowWindow(m_nCmdShow);
  pWnd->UpdateWindow();

  return TRUE;
}
