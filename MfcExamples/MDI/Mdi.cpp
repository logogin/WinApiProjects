///////////////////////////////////////////////////////////
// Файл MDI.cpp
// Copyright (c) 1999 Мешков А., Тихомиров Ю.
///////////////////////////////////////////////////////////

// MDI.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "MDI.h"
#include "AppAbout.h"

#include "MainFrm.h"

/////////////////////////////////////////////////////////////////////////////
// CMDIApp

BEGIN_MESSAGE_MAP(CMDIApp, CWinApp)
	//{{AFX_MSG_MAP(CMDIApp)
 	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMDIApp construction

CMDIApp::CMDIApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMDIApp object

CMDIApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMDIApp initialization

BOOL CMDIApp::InitInstance()
{
	// Standard initialization

 CString csCaption;
 csCaption.LoadString(IDR_MAINFRAME);

 CWnd *pWnd = CWnd::FindWindow(NULL, csCaption);
 if(pWnd != NULL){
  if(pWnd->IsIconic())
   pWnd->ShowWindow(SW_RESTORE);
  pWnd->SetForegroundWindow();
  return FALSE;
 }
	
 Enable3dControls();			// Call this when using MFC in a shared DLL

 // create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

// App command to run the dialog
void CMDIApp::OnAppAbout()
{
	CAppAbout *aboutDlg = new CAppAbout();
//	aboutDlg->Create(IDD_ABOUTBOX);
}

/////////////////////////////////////////////////////////////////////////////
// CMDIApp commands
