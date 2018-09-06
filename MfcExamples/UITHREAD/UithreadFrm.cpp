/*************************************************************
Файл UIThreadFrm.cpp
Copyright (c) 1999 Мешков А., Тихомиров Ю.
*************************************************************/

// UIThreadFrm.cpp : implementation file
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
// CUIThreadFrame

CUIThreadFrame::CUIThreadFrame()
{
}


BEGIN_MESSAGE_MAP(CUIThreadFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CUIThreadFrame)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_USER_PREPARE_TO_CLOSE, OnPrepareToClose)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////
// CUIThreadFrame message handlers

BOOL CUIThreadFrame::Create(LPCTSTR lpszClassName, 
                            LPCTSTR lpszWindowName, 
                            DWORD dwStyle, 
                            const RECT& rect, 
                            CWnd* pParentWnd, 
                            UINT nID, 
                            CCreateContext* pContext) 
{
  if (!CFrameWnd::Create(lpszClassName, lpszWindowName, 
    dwStyle, rect, pParentWnd, MAKEINTRESOURCE(nID), 0, pContext))
    return FALSE;

  CRect clientRect;
  GetClientRect(&clientRect);
  clientRect.top += 20;

  // создание окна-редактора
  m_wndEdit.Create(ES_MULTILINE | ES_AUTOHSCROLL | WS_BORDER |
    ES_AUTOVSCROLL | WS_CHILD | WS_VISIBLE, 
    clientRect, this, IDC_LINE_WND+1);

  // создание нового потока, при создании которого
  // будет создано и окно "бегущая строка"
  m_pLineThread = new CLineThread(m_hWnd);
  m_pLineThread->CreateThread();

  // устанавливаем фокус на окно-редактор
  m_wndEdit.SetFocus();

  return TRUE;
}

//
// функция перенаправления командных сообщений
//
BOOL CUIThreadFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra,
    AFX_CMDHANDLERINFO* pHandlerInfo)
{
  // По умолчанию эта функция диспетчирует команды меню
  // и команды инициализации перенапрявляя их в 
  // ON_COMMAND и ON_UPDATE_COMMAND_UI обработчики.
  // Причем все это происходит в основном потоке приложения.
  // Однако объект класса CLineWnd находится в другом потоке.
  // Вызов напрямую функции CLineWnd::OnCmdMsg возможно, 
  // но в этом случае обработка сообщений будет происходить
  // в этом основном потоке. Самый лучший способ это
  // передать сообщение окну, собрав в специальной структуре
  // необходимые данные. Причем это самый надежный и
  // правильный способ исключающий вызов напрямую
  // функций другого потока.

  CWnd* pLineWnd = (CLineWnd*)GetDlgItem(IDC_LINE_WND);
  if (pLineWnd == NULL)
    return FALSE; // окно CLineWnd еще не создано

  // создаем объект CCmdMsg в стеке, т.к. функция 
  // SendMessage осуществляет синхронную пердачу сообщений, 
  // т.о. она завершиться только по завершении обработки
  // сообщения

  CCmdMsg cmdmsg;
  cmdmsg.m_nID =    nID;
  cmdmsg.m_nCode = nCode;
  cmdmsg.m_pExtra = pExtra;
  cmdmsg.m_pHandlerInfo = pHandlerInfo;

  return pLineWnd->SendMessage(WM_USER_ONCMDMSG,
    GetCurrentMessage()->wParam, (LPARAM)&cmdmsg);
}

BOOL CUIThreadFrame::DestroyWindow()
{
  OnPrepareToClose();

  return CFrameWnd::DestroyWindow();
}

LRESULT CUIThreadFrame::OnPrepareToClose(WPARAM, LPARAM)
{
  // отправляем сообщение окну CLineWnd на 
  // завершение и ждем до тех пор пока это 
  // сообщение не будет обработано и ожидаем 
  // сигнала о завершении соответствующего потока

  CWnd* pLineWnd = (CLineWnd*)GetDlgItem(IDC_LINE_WND);
  pLineWnd->SendMessage(WM_USER_PREPARE_TO_CLOSE);

  WaitForSingleObject(
    CLineThread::m_hEventLineThreadKilled, INFINITE);

  return 0;
}

void CUIThreadFrame::OnSize(UINT nType, int cx, int cy)
{
  CFrameWnd::OnSize(nType, cx, cy);

  CWnd* pLineWnd = GetDlgItem(IDC_LINE_WND);
  if (pLineWnd == NULL)
    return; // окно CLineWnd еще не создано

  CRect rect;
  GetClientRect(&rect);
  pLineWnd->SetWindowPos(NULL, rect.top, rect.left, 
    rect.Width(), 20,
    SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOZORDER);

  m_wndEdit.SetWindowPos(NULL, rect.top+20, rect.left, 
    rect.Width(), rect.Height()-20,
    SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOZORDER);
}
