/*************************************************************
���� LineThread.cpp
Copyright (c) 1999 ������ �., ��������� �.
*************************************************************/

// LineThread.cpp : implementation file
//

#include "stdafx.h"
#include "uithread.h"
#include "LineThread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

HANDLE CLineThread::m_hEventLineThreadKilled;

/////////////////////////////////////////////////////////////////////////////
// CLineThread

IMPLEMENT_DYNCREATE(CLineThread, CWinThread)

CLineThread::CLineThread()
{
}

CLineThread::CLineThread(HWND hwndParent) : 
	m_hwndParent(hwndParent)
{
}

CLineThread::~CLineThread()
{
}

void CLineThread::operator delete(void* p)
{
	CWinThread::operator delete(p);
	
	SetEvent(m_hEventLineThreadKilled);
}

BOOL CLineThread::InitInstance()
{
  CWnd* pParent = CWnd::FromHandle(m_hwndParent);
  CRect rect;
  pParent->GetClientRect(&rect);
  rect.bottom = rect.top + 20;

  BOOL bReturn = m_wndLine.Create(_T("LineMTChildWnd"),
    WS_CHILD | WS_VISIBLE, rect, pParent);

  // ��� ����, ����� ������������ ����� ���������� �� 
  // ������������� ����� ����� ����������� ����, ������� 
  // ������� ����� � ���� �����

  if (bReturn)
    m_pMainWnd = &m_wndLine;

  return bReturn;
}

int CLineThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CLineThread, CWinThread)
	//{{AFX_MSG_MAP(CLineThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLineThread message handlers

BOOL CLineThread::OnIdle(LONG lCount) 
{
  if (::IsWindow(m_wndLine.m_hWnd))
  {
    // ��� ���������� ��������� "������� ������"
    // ���������� �������� ��������� lCount,
    // ������, ���������� ��� ������� ��������,
    // �.�. � ��������� ������ ������ ����� 
    // ������������ ��� ������� ���������� ������� 
    // ���������, ��������, �� ���� - ����� �������
    // ������ ��������� ������� OnIdle ����� ����������,
    // ������ �������� lCount ��� ���� ����� ����� 0
    if (!((lCount+1) % m_wndLine.m_Speed))
      m_wndLine.Redraw();

    return TRUE;
  }
    
  return CWinThread::OnIdle(lCount);
}
