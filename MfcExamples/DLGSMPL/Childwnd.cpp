//////////////////////////////////////////////////////////////
// ���� ChildWnd.cpp
// Copyright (c) 1999 ������ �., ��������� �.
//////////////////////////////////////////////////////////////

// ChildWnd.cpp : implementation file
//

#include "stdafx.h"
#include "DlgSmpl.h"
#include "ChildWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildWnd

IMPLEMENT_DYNCREATE(CChildWnd, CMDIChildWnd)

CMenu CChildWnd::menu;
COLORREF CChildWnd::aCustom[16];
COLORREF colorArray[] =
{
	RGB (0, 0, 0),
 RGB (255, 0, 0),
 RGB (0, 0, 255),
 RGB (0, 255, 0),
 RGB (255, 255, 255),
 RGB (128, 128, 128)
};

CChildWnd::CChildWnd()
{
 nIDColor = IDM_BLUE;
 clrText = RGB(0, 0, 255);
 for(int i = 0; i < 16; i++)
  aCustom[i] = RGB (255, 255, 255);
}

CChildWnd::~CChildWnd()
{
}

// � �������� ��������������� ������� ����� ������������
// ������� ��� ��������� ���� ��������������� ������
// ON_COMMAND_RANGE � ON_UPDATE_COMMAND_UI_RANGE

BEGIN_MESSAGE_MAP(CChildWnd, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildWnd)
	ON_WM_PAINT()
	ON_COMMAND(IDM_CUSTOM, OnCustom)
	ON_COMMAND(IDM_FONT, OnFont)
	//}}AFX_MSG_MAP
 ON_COMMAND_RANGE(IDM_BLACK, IDM_WHITE, OnColor)
 ON_UPDATE_COMMAND_UI_RANGE(IDM_BLACK, IDM_WHITE, OnUpdateColor)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildWnd message handlers

BOOL CChildWnd::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style |= WS_CHILD | WS_VISIBLE | WS_OVERLAPPEDWINDOW;

 if(menu.m_hMenu == NULL)
  menu.LoadMenu(IDR_CHILD);
 m_hMenuShared = menu.m_hMenu;
	
	return CMDIChildWnd::PreCreateWindow(cs);
}

void CChildWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	CRect rect;

	dc.SetTextColor(clrText);
	dc.SetBkColor(::GetSysColor(COLOR_WINDOW));
	GetClientRect(rect);
	dc.DrawText(_TEXT("��������� ��������� WM_PAINT"), -1, rect,
		           DT_SINGLELINE | DT_CENTER | DT_VCENTER);
}

// ��������������� �����������
void CChildWnd::OnColor(UINT nID) 
{
  nIDColor = nID;
  clrText = colorArray[nIDColor - IDM_BLACK];

  Invalidate();
}

void CChildWnd::OnUpdateColor(CCmdUI* pCmdUI) 
{
  pCmdUI->SetCheck(pCmdUI->m_nID == nIDColor);
}

// ���������� ��� ��������� ������
void CChildWnd::OnCustom() 
{
  // ������� ������ ����� �������
  CColorDialog clrDlg;

  clrDlg.m_cc.lStructSize = sizeof(clrDlg.m_cc);
  clrDlg.m_cc.rgbResult = colorArray[nIDColor - IDM_BLACK];
  clrDlg.m_cc.lpCustColors = aCustom;

  // ���� �� ������������ ��������� �� ���������, �� ���������
  // ������������� ���� CC_ENABLEHOOK ��� ����������� �����������
  // ��� ��������� ������� ��������� ������
  clrDlg.m_cc.Flags = CC_ENABLEHOOK; // CC_FULLOPEN | CC_RGBINIT

  // ������� ���� ������� �� �����
  if(clrDlg.DoModal() == IDOK)
  {
    // ��������� ����� ���������� ������ ��� ��������
    // ����� ������� ������� OK
    nIDColor = IDM_CUSTOM;
    colorArray[nIDColor - IDM_BLACK] = clrDlg.GetColor();
    OnColor(nIDColor);
  }
}

// ���������� ��� ��������� ����� ������� ������ ������
void CChildWnd::OnFont() 
{
  CFontDialog fontDlg;

  fontDlg.m_cf.Flags = CF_BOTH | CF_APPLY | CF_ENABLEHOOK;

  // ������������� ���������� �����
  fontDlg.m_cf.rgbColors = RGB(255, 255, 255);

  // ��� ��������� ���������� �������� ������ ���
  // ������������� ����� CF_EFFECTS
  fontDlg.m_cf.Flags |= CF_EFFECTS;

  // ������� ���� ������� �� �����
  if (fontDlg.DoModal() == IDOK)
  {
    // ����� ����� ���������� ������ � �������
    // �������� �������� ����
    CClientDC dc(this);

    // ������������� ���� ��� ���������� ������
    // � ������������ �� ��������� �������
    dc.SetTextColor(fontDlg.GetColor());
    dc.SetBkColor(::GetSysColor(COLOR_WINDOW));

    // ������� �����
    TCHAR strText[256];
    strcpy(strText, "������ ����� ");
    strcat(strText, fontDlg.GetFaceName());
    TCHAR str[32];
    sprintf(str, " �������� %d �������", fontDlg.GetSize()/10);
    strcat(strText, str);
    dc.TextOut(10, 10, strText, strlen(strText));
  }
}
