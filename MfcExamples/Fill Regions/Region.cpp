// Region.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Region.h"
#include "RegionFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRegionApp

BEGIN_MESSAGE_MAP(CRegionApp, CWinApp)
	//{{AFX_MSG_MAP(CRegionApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRegionApp construction

CRegionApp::CRegionApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CRegionApp object

CRegionApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CRegionApp initialization

BOOL CRegionApp::InitInstance()
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

	CRegionFrame *pWnd = new CRegionFrame;
	m_pMainWnd = pWnd;

	pWnd->Create(NULL, _T("Region -- CRgn::CombineRgn"));

	pWnd->CenterWindow();
	pWnd->ShowWindow(m_nCmdShow);
	pWnd->UpdateWindow();

	return TRUE;
}
