///////////////////////////////////////////////////////////
// Файл MDIChilds.cpp
// Copyright (c) 1999 Мешков А., Тихомиров Ю.
///////////////////////////////////////////////////////////

// MDIChilds.cpp : implementation file
//

#include "stdafx.h"
#include "MDI.h"
#include "MDIChild.h"

CMenu CTextWnd::menu;     // меню для всех дочерних окон

COLORREF colorArray[] =
{
	RGB (0, 0, 0),
 RGB (255, 255, 255),
 RGB (255, 0, 0),
	RGB (0, 0, 255),
	RGB (0, 255, 0)
};

BEGIN_MESSAGE_MAP(CTextWnd, CMDIChildWnd)
	//{{AFX_MSG_MAP(CTextWnd)
  ON_COMMAND(IDM_BLACK, OnColor)
		ON_UPDATE_COMMAND_UI(IDM_BLACK, OnUpdateColor)
 	ON_WM_LBUTTONDOWN()
  ON_COMMAND(IDM_BLUE, OnColor)
  ON_COMMAND(IDM_GREEN, OnColor)
  ON_COMMAND(IDM_RED, OnColor)
  ON_COMMAND(IDM_WHITE, OnColor)
  ON_UPDATE_COMMAND_UI(IDM_BLUE, OnUpdateColor)
	 ON_UPDATE_COMMAND_UI(IDM_GREEN, OnUpdateColor)
	 ON_UPDATE_COMMAND_UI(IDM_RED, OnUpdateColor)
	 ON_UPDATE_COMMAND_UI(IDM_WHITE, OnUpdateColor)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTextWnd

CTextWnd::CTextWnd()
{
	nIDColor = IDM_BLACK;
 clrText = RGB(0, 0, 0);
}

/////////////////////////////////////////////////////////////////////////////
// CTextWnd message handlers

BOOL CTextWnd::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style |= WS_CHILD | WS_VISIBLE |
             WS_OVERLAPPEDWINDOW;

 // Загружаем меню дочернего окна
	if (menu.m_hMenu == NULL)
		menu.LoadMenu(IDR_MDITEXT);
	m_hMenuShared = menu.m_hMenu;
	
	return CMDIChildWnd::PreCreateWindow(cs);
}

// Обработчик сообщения WM_PAINT
void CTextWnd::OnPaint() 
{
	CPaintDC dc(this);
	
 CRect rect;
 GetClientRect(rect);

	// Устанавливаем текущий цвет текста
 dc.SetTextColor(clrText);
	dc.SetBkColor(::GetSysColor(COLOR_WINDOW));
	
 // Отображаем текст в центре окна
	dc.DrawText(_TEXT("Обработка сообщения WM_PAINT"), -1, rect,
		           DT_SINGLELINE | DT_CENTER | DT_VCENTER);
}

// Обработчик команд IDM_BLACK - IDM_WHITE (один на все)
void CTextWnd::OnColor() 
{
	// Получаем идентификатор выбранной команды
 nIDColor = LOWORD(GetCurrentMessage()->wParam);
	
 // По идентификатору команды выбираем из массива
 // соответствующее значение цвета
 clrText = colorArray[nIDColor - IDM_BLACK];

	// Перерисовать окно в ответ на сообщение WM_PAINT
 Invalidate();
}

// Обработчик команд обновления IDM_BLACK - IDM_WHITE (один на все)
void CTextWnd::OnUpdateColor(CCmdUI* pCmdUI) 
{
	// Устанавливаем или убираем галочку у соответствующего
 // элемента меню
 pCmdUI->SetCheck(pCmdUI->m_nID == nIDColor);
}

// Обработчик сообщения WM_LBUTTONDOWN
void CTextWnd::OnLButtonDown(UINT nFlags, CPoint point) 
{
	TCHAR strText[] = "Обработка сообщения WM_LBOTTONDOWN";

 CClientDC dc(this);
	CRect rect;

	// Устанавливаем текущий цвет текста
 dc.SetTextColor(clrText);
	dc.SetBkColor(::GetSysColor(COLOR_WINDOW));
	
 // Отображаем текст в окне, начиная с точки (10, 10)
 dc.TextOut(10, 10, strText, strlen(strText));
	
	// Не забываем передать управление родительскому
 // окну для дальнейшей обработки
 CMDIChildWnd::OnLButtonDown(nFlags, point);
}
