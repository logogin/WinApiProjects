/*************************************************************
Файл LineWnd.cpp
Copyright (c) 1999 Мешков А., Тихомиров Ю.
*************************************************************/

// LineWnd.cpp : implementation file
//

#include "stdafx.h"
#include "uithread.h"
#include "LineWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CLineWnd, CWnd)

/////////////////////////////////////////////////////////////////////////////
// CLineWnd

CLineWnd::CLineWnd() : m_Speed(NormalSpeed)
{
}

CLineWnd::~CLineWnd()
{
}


BEGIN_MESSAGE_MAP(CLineWnd, CWnd)
	//{{AFX_MSG_MAP(CLineWnd)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_COMMAND(ID_SPEED_SLOW, OnSpeedSlow)
	ON_COMMAND(ID_SPEED_NORMAL, OnSpeedNormal)
	ON_COMMAND(ID_SPEED_FAST, OnSpeedFast)
	ON_UPDATE_COMMAND_UI(ID_SPEED_SLOW, OnUpdateSpeedSlow)
	ON_UPDATE_COMMAND_UI(ID_SPEED_NORMAL, OnUpdateSpeedNormal)
	ON_UPDATE_COMMAND_UI(ID_SPEED_FAST, OnUpdateSpeedFast)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_USER_ONCMDMSG, OnDelegatedCmdMsg)
	ON_MESSAGE(WM_USER_PREPARE_TO_CLOSE, OnPrepareToClose)
END_MESSAGE_MAP()

void CLineWnd::Redraw()
{
  static int nOffset_1 = 0;

  // организация взаимоисключающего доступа к элементу
  // CUIThreadApp::m_Text, который содержит строку текста 
  ((CUIThreadApp *)AfxGetApp())->m_TextLock.Lock();

  CString csText = ((CUIThreadApp *)AfxGetApp())->m_Text;
  
  ((CUIThreadApp *)AfxGetApp())->m_TextLock.Unlock();

  CClientDC dc(this);
  dc.SetBkColor(RGB(192,192,192));

  CRect rect(0, 0, m_cxClient, m_cyClient);
  dc.DrawText(csText, &rect, 
    DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX | DT_CALCRECT);

  int nWidth = rect.Width();
  rect.OffsetRect(nOffset_1, 0);
  dc.DrawText(csText, &rect, 
    DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX);

  int nOffset_2 = nWidth + nOffset_1 + 50;
  if (nOffset_2 - nOffset_1 < m_cxClient)
    nOffset_2 = m_cxClient + nOffset_1;

  rect.OffsetRect(nOffset_2 - nOffset_1, 0);
  dc.DrawText(csText, &rect, 
    DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX);

  dc.FillRect(CRect(nOffset_1+nWidth, 0, nOffset_2, 
    m_cyClient), &m_Brush);

  if (nOffset_2+nWidth < m_cxClient)
    dc.FillRect(CRect(nOffset_2+nWidth, 0, m_cxClient, 
    m_cyClient), &m_Brush);

  nOffset_1--;

  if (nOffset_2 == 0)
    nOffset_1 = nOffset_2;
}

//////////////////////////////////////////////////////////////
// CLineWnd message handlers

BOOL CLineWnd::Create(LPCTSTR szTitle, LONG style, 
  const RECT& rect, CWnd* parent)
{
  m_Brush.CreateSolidBrush(RGB(192,192,192));

  // регистрируем класс окна, т.к. оно имеет отличную от 
  // принятой кисти и не имеет пиктограммы
  LPCTSTR lpszLineClass =
    AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_SAVEBITS,
      LoadCursor(NULL, IDC_ARROW), m_Brush, NULL);

  return CWnd::Create(lpszLineClass, szTitle, style, 
    rect, parent,  IDC_LINE_WND);
}

LRESULT CLineWnd::OnDelegatedCmdMsg(WPARAM, LPARAM lParam)
{
  CCmdMsg* pcmdMsg = (CCmdMsg*)lParam;
  return CWnd::OnCmdMsg(pcmdMsg->m_nID, pcmdMsg->m_nCode, 
    pcmdMsg->m_pExtra,  pcmdMsg->m_pHandlerInfo);
}

LRESULT CLineWnd::OnPrepareToClose(WPARAM, LPARAM)
{
  DestroyWindow();
  return 0;
}

void CLineWnd::OnSize(UINT nType, int cx, int cy) 
{
  CWnd::OnSize(nType, cx, cy);
  
  // запоминаем размер клиентской области
  // окна, чтобы каждый раз при перерисовке
  // не запрашивать размер заново
  m_cxClient = cx;
  m_cyClient = cy;
}

void CLineWnd::OnPaint() 
{
  CPaintDC dc(this); // device context for painting
  
  CRect rect(0, 0, m_cxClient, m_cyClient);
  dc.FillRect(&rect, &m_Brush);

  Redraw();
}

void CLineWnd::OnSpeedSlow() 
{
  m_Speed = SlowSpeed;
}

void CLineWnd::OnSpeedNormal() 
{
  m_Speed = NormalSpeed;
}

void CLineWnd::OnSpeedFast() 
{
  m_Speed = FastSpeed;
}

void CLineWnd::OnUpdateSpeedSlow(CCmdUI* pCmdUI) 
{
  pCmdUI->SetCheck(m_Speed == SlowSpeed);
}

void CLineWnd::OnUpdateSpeedNormal(CCmdUI* pCmdUI) 
{
  pCmdUI->SetCheck(m_Speed == NormalSpeed);
}

void CLineWnd::OnUpdateSpeedFast(CCmdUI* pCmdUI) 
{
  pCmdUI->SetCheck(m_Speed == FastSpeed);
}
