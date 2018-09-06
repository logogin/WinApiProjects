/////////////////////////////////////////////////////////
// ���� First.cpp
// Copyright (c) 1999 ������ �., ��������� �.
/////////////////////////////////////////////////////////

#include "stdafx.h"

#include "First.h"
#include "MainFrm.h"

// CFirstApp

CFirstApp::CFirstApp()
{
}

// ����� ���� ������ ���� � ������ ���� ������ CFirstApp
CFirstApp theApp;

// ������������� ������� CFirstApp

BOOL CFirstApp::InitInstance()
{
  const char *szWndClass = AfxRegisterWndClass(
    CS_HREDRAW | CS_HREDRAW,
    LoadStandardCursor(IDC_ARROW),
    (HBRUSH)COLOR_BACKGROUND + 1,
    LoadIcon(IDR_MAINFRAME));

  CMainFrame *pWnd = new CMainFrame;

  pWnd->CreateEx(
    0,                            // �������������� �����
    szWndClass,                   // ����� ����
    "������ ���������",           // ���������
    WS_OVERLAPPEDWINDOW,          // �����
    CW_USEDEFAULT, CW_USEDEFAULT, // ����� ������� ���� (x, y)
    CW_USEDEFAULT, CW_USEDEFAULT, // ������� (cx, cy)
    NULL,                         // ������������ ����
    NULL);                        // ������������� ����

  pWnd->ShowWindow(m_nCmdShow);
  m_pMainWnd = pWnd;

  return TRUE;
}

