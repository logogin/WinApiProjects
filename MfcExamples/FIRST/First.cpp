/////////////////////////////////////////////////////////
// Файл First.cpp
// Copyright (c) 1999 Мешков А., Тихомиров Ю.
/////////////////////////////////////////////////////////

#include "stdafx.h"

#include "First.h"
#include "MainFrm.h"

// CFirstApp

CFirstApp::CFirstApp()
{
}

// Может быть создан один и только один объект CFirstApp
CFirstApp theApp;

// Инициализация объекта CFirstApp

BOOL CFirstApp::InitInstance()
{
  const char *szWndClass = AfxRegisterWndClass(
    CS_HREDRAW | CS_HREDRAW,
    LoadStandardCursor(IDC_ARROW),
    (HBRUSH)COLOR_BACKGROUND + 1,
    LoadIcon(IDR_MAINFRAME));

  CMainFrame *pWnd = new CMainFrame;

  pWnd->CreateEx(
    0,                            // дополнительные стили
    szWndClass,                   // класс окна
    "Первая программа",           // заголовок
    WS_OVERLAPPEDWINDOW,          // стиль
    CW_USEDEFAULT, CW_USEDEFAULT, // левый верхний угол (x, y)
    CW_USEDEFAULT, CW_USEDEFAULT, // размеры (cx, cy)
    NULL,                         // родительское окно
    NULL);                        // идентификатор меню

  pWnd->ShowWindow(m_nCmdShow);
  m_pMainWnd = pWnd;

  return TRUE;
}

