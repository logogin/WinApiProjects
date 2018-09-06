/*************************************************************
���� UIThreadFrm.cpp
Copyright (c) 1999 ������ �., ��������� �.
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

  // �������� ����-���������
  m_wndEdit.Create(ES_MULTILINE | ES_AUTOHSCROLL | WS_BORDER |
    ES_AUTOVSCROLL | WS_CHILD | WS_VISIBLE, 
    clientRect, this, IDC_LINE_WND+1);

  // �������� ������ ������, ��� �������� ��������
  // ����� ������� � ���� "������� ������"
  m_pLineThread = new CLineThread(m_hWnd);
  m_pLineThread->CreateThread();

  // ������������� ����� �� ����-��������
  m_wndEdit.SetFocus();

  return TRUE;
}

//
// ������� ��������������� ��������� ���������
//
BOOL CUIThreadFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra,
    AFX_CMDHANDLERINFO* pHandlerInfo)
{
  // �� ��������� ��� ������� ������������ ������� ����
  // � ������� ������������� ������������� �� � 
  // ON_COMMAND � ON_UPDATE_COMMAND_UI �����������.
  // ������ ��� ��� ���������� � �������� ������ ����������.
  // ������ ������ ������ CLineWnd ��������� � ������ ������.
  // ����� �������� ������� CLineWnd::OnCmdMsg ��������, 
  // �� � ���� ������ ��������� ��������� ����� �����������
  // � ���� �������� ������. ����� ������ ������ ���
  // �������� ��������� ����, ������ � ����������� ���������
  // ����������� ������. ������ ��� ����� �������� �
  // ���������� ������ ����������� ����� ��������
  // ������� ������� ������.

  CWnd* pLineWnd = (CLineWnd*)GetDlgItem(IDC_LINE_WND);
  if (pLineWnd == NULL)
    return FALSE; // ���� CLineWnd ��� �� �������

  // ������� ������ CCmdMsg � �����, �.�. ������� 
  // SendMessage ������������ ���������� ������� ���������, 
  // �.�. ��� ����������� ������ �� ���������� ���������
  // ���������

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
  // ���������� ��������� ���� CLineWnd �� 
  // ���������� � ���� �� ��� ��� ���� ��� 
  // ��������� �� ����� ���������� � ������� 
  // ������� � ���������� ���������������� ������

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
    return; // ���� CLineWnd ��� �� �������

  CRect rect;
  GetClientRect(&rect);
  pLineWnd->SetWindowPos(NULL, rect.top, rect.left, 
    rect.Width(), 20,
    SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOZORDER);

  m_wndEdit.SetWindowPos(NULL, rect.top+20, rect.left, 
    rect.Width(), rect.Height()-20,
    SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOZORDER);
}
