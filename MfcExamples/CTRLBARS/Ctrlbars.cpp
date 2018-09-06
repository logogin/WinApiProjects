//////////////////////////////////////////////////////////////
// Модуль ControlBars.cpp
// Copyright (c) 1999 Мешков А., Тихомиров Ю.
//////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <afxpriv.h>    // for idle-update windows message

#include "ctrlbars.h"
#include "mainfrm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCtrlbarsApp

BEGIN_MESSAGE_MAP(CCtrlbarsApp, CWinApp)
        //{{AFX_MSG_MAP(CCtrlbarsApp)
        ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCtrlbarsApp construction

CCtrlbarsApp::CCtrlbarsApp()
{
        // Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CCtrlbarsApp object

CCtrlbarsApp NEAR theApp;

/////////////////////////////////////////////////////////////////////////////
// Инициализация CControlBarsApp

BOOL CCtrlbarsApp::InitInstance()
{
  // Standard initialization

  Enable3dControls(); // use 3d controls in dialogs

  // создание нового SDI-окна
  CFrameWnd* pMainFrame = new CMainFrame;
  if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
    return FALSE;

  pMainFrame->ShowWindow(m_nCmdShow);
  pMainFrame->UpdateWindow();

  m_pMainWnd = pMainFrame;

  return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CCtrlbarsApp commands

void CCtrlbarsApp::OnAppAbout()
{
        CDialog(IDD_ABOUTBOX).DoModal();
}

/////////////////////////////////////////////////////////////////////////////
