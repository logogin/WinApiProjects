///////////////////////////////////////////////////////////
// ���� MDIChilds.cpp
// Copyright (c) 1999 ������ �., ��������� �.
///////////////////////////////////////////////////////////

// MDIChilds.cpp : implementation file
//

#include "stdafx.h"
#include "MDI.h"
#include "MDIChild.h"

CMenu CTextWnd::menu;     // ���� ��� ���� �������� ����

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

 // ��������� ���� ��������� ����
	if (menu.m_hMenu == NULL)
		menu.LoadMenu(IDR_MDITEXT);
	m_hMenuShared = menu.m_hMenu;
	
	return CMDIChildWnd::PreCreateWindow(cs);
}

// ���������� ��������� WM_PAINT
void CTextWnd::OnPaint() 
{
	CPaintDC dc(this);
	
 CRect rect;
 GetClientRect(rect);

	// ������������� ������� ���� ������
 dc.SetTextColor(clrText);
	dc.SetBkColor(::GetSysColor(COLOR_WINDOW));
	
 // ���������� ����� � ������ ����
	dc.DrawText(_TEXT("��������� ��������� WM_PAINT"), -1, rect,
		           DT_SINGLELINE | DT_CENTER | DT_VCENTER);
}

// ���������� ������ IDM_BLACK - IDM_WHITE (���� �� ���)
void CTextWnd::OnColor() 
{
	// �������� ������������� ��������� �������
 nIDColor = LOWORD(GetCurrentMessage()->wParam);
	
 // �� �������������� ������� �������� �� �������
 // ��������������� �������� �����
 clrText = colorArray[nIDColor - IDM_BLACK];

	// ������������ ���� � ����� �� ��������� WM_PAINT
 Invalidate();
}

// ���������� ������ ���������� IDM_BLACK - IDM_WHITE (���� �� ���)
void CTextWnd::OnUpdateColor(CCmdUI* pCmdUI) 
{
	// ������������� ��� ������� ������� � ����������������
 // �������� ����
 pCmdUI->SetCheck(pCmdUI->m_nID == nIDColor);
}

// ���������� ��������� WM_LBUTTONDOWN
void CTextWnd::OnLButtonDown(UINT nFlags, CPoint point) 
{
	TCHAR strText[] = "��������� ��������� WM_LBOTTONDOWN";

 CClientDC dc(this);
	CRect rect;

	// ������������� ������� ���� ������
 dc.SetTextColor(clrText);
	dc.SetBkColor(::GetSysColor(COLOR_WINDOW));
	
 // ���������� ����� � ����, ������� � ����� (10, 10)
 dc.TextOut(10, 10, strText, strlen(strText));
	
	// �� �������� �������� ���������� �������������
 // ���� ��� ���������� ���������
 CMDIChildWnd::OnLButtonDown(nFlags, point);
}
