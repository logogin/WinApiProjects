// InProg.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "InProg.h"
#include "InProgFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInProgApp

BEGIN_MESSAGE_MAP(CInProgApp, CWinApp)
	//{{AFX_MSG_MAP(CInProgApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
    //    DO NOT EDIT what you see in these blocks of generated code!
  //}}AFX_MSG
  ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInProgApp construction

CInProgApp::CInProgApp()
{
	// TODO: add construction code here,
  // Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CInProgApp object

CInProgApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CInProgApp initialization

BOOL CInProgApp::InitInstance()
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

	CInProgFrame *pWnd = new CInProgFrame;
	m_pMainWnd = pWnd;

	int nSizeX = (int)(GetSystemMetrics(SM_CXMAXIMIZED) * 0.4);
	int nSizeY = (int)(GetSystemMetrics(SM_CYMAXIMIZED) * 0.4);

	pWnd->Create(NULL, _T("InProg -- CProgressCtrl"),
		WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME, 
		CRect(0, 0, nSizeX, nSizeY));

	pWnd->CenterWindow();
  pWnd->ShowWindow(m_nCmdShow);
  pWnd->UpdateWindow();

  return TRUE;
}
