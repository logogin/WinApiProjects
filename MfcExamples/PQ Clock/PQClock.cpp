/*************************************************************
���� PQClock.cpp
Copyright (c) 1999 ������ �., ��������� �.
*************************************************************/

// PQClock.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "PQClock.h"
#include "ClockFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPQClockApp

BEGIN_MESSAGE_MAP(CPQClockApp, CWinApp)
  //{{AFX_MSG_MAP(CPQClockApp)
    // NOTE - the ClassWizard will add and remove mapping macros here.
    //    DO NOT EDIT what you see in these blocks of generated code!
  //}}AFX_MSG
  ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPQClockApp construction

CPQClockApp::CPQClockApp()
{
  // TODO: add construction code here,
  // Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CPQClockApp object

CPQClockApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CPQClockApp initialization

BOOL CPQClockApp::InitInstance()
{
  // Standard initialization
  // If you are not using these features and
  // wish to reduce the size
  // of your final executable, 
  // you should remove from the following
  // the specific initialization routines you do not need.

#ifdef _AFXDLL
  Enable3dControls();      // Call this when using MFC in a shared DLL
#else
  Enable3dControlsStatic();  // Call this when linking to MFC statically
#endif

  CClockFrame *pWnd = new CClockFrame;
  m_pMainWnd = pWnd;

  int nSize = min(GetSystemMetrics(SM_CXMAXIMIZED), 
    GetSystemMetrics(SM_CYMAXIMIZED)) * 3 / 5;

  pWnd->Create(NULL, "���� 'PRAGMA Quartz'", 
    WS_OVERLAPPEDWINDOW, CRect(0, 0, nSize, nSize));

  pWnd->CenterWindow();
  pWnd->ShowWindow(m_nCmdShow);
  pWnd->UpdateWindow();

  return TRUE;
}

BOOL CPQClockApp::OnIdle(LONG lCount) 
{
  CWinApp::OnIdle(lCount);

  // �������������� ����
  ((CClockFrame *)m_pMainWnd)->Redraw();

  // ����� �� ��������� ���� ������
  // ������� OnIdle ���������� TRUE
  return TRUE;
}
