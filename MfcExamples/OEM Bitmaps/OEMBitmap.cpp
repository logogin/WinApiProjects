// OEMBitmap.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "OEMBitmap.h"
#include "OEMBitmapFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COEMBitmapApp

BEGIN_MESSAGE_MAP(COEMBitmapApp, CWinApp)
	//{{AFX_MSG_MAP(COEMBitmapApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COEMBitmapApp construction

COEMBitmapApp::COEMBitmapApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only COEMBitmapApp object

COEMBitmapApp theApp;

/////////////////////////////////////////////////////////////////////////////
// COEMBitmapApp initialization

BOOL COEMBitmapApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	COEMBitmapFrame *pWnd = new COEMBitmapFrame;
	m_pMainWnd = pWnd;

	pWnd->Create(NULL, _T("OEMBitmap -- CBitmap::LoadOEMBitmap"));

	pWnd->CenterWindow();
	pWnd->ShowWindow(m_nCmdShow);
	pWnd->UpdateWindow();

	return TRUE;
}
