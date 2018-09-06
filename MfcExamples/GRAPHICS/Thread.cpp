/*************************************************************
���� Thread.cpp
Copyright (c) 1999 ������ �., ��������� �.
*************************************************************/

// Thread.cpp : implementation file
//

#include "stdafx.h"
#include "Graphics.h"
#include "Thread.h"

#include "stdlib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// ����������� ������ ��� ���������������� ������� 
// � ��������� ����������
CCriticalSection CThread::m_csGDILock;

///////////////////////////////////////////////////////////
// CThread

IMPLEMENT_DYNAMIC(CThread, CWinThread)

CThread::CThread(CWnd* pWnd, HDC hDC, COLORREF &cr)
{
  m_pMainWnd = pWnd;
  m_pMainWnd->GetClientRect(&m_Rect);
  m_hDC = hDC;

  m_pt.x = m_Rect.Width() / 2;
  m_pt.y = m_Rect.Height() / 2;

  m_offset.x = 10;
  m_offset.y = 10;

  m_Brush.CreateSolidBrush(cr);
}

CThread::~CThread()
{
}

BOOL CThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int CThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CThread, CWinThread)
	//{{AFX_MSG_MAP(CThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CThread message handlers

int CThread::Run() 
{
  CDC dc;
  dc.Attach(m_hDC);

  CBrush brush(::GetSysColor(COLOR_WINDOW));

  // ��������� "�����" ��� ���������� ��������� �����.
  // ��� ����� ������ ��� ������� ������ � �����������
  // ������ ������ �����, ����� ������ �� �����������
  srand((unsigned)this);

  // �������� ���� �� ���������� ����������� ��������
  while (!((CGraphicsApp *)AfxGetApp())->m_nDone)
  {
    CPoint pt = m_pt;

    // ���������� ����� ���������
    for (; ;)
    {
      pt += m_offset;
      
      if (m_Rect.PtInRect(pt) && (rand() % 1000) < 900)
      {
        if (m_offset.x < 0)
          m_offset.x -= 1;
        else if (m_offset.x > 0)
          m_offset.x += 1;

        if (m_offset.y < 0)
          m_offset.y -= 1;
        else if (m_offset.y > 0)
          m_offset.y += 1;

        break;
      }
    
      pt = m_pt;

      CPoint offset = m_offset;

      while (offset == m_offset || 
        offset.x == 0 && offset.y == 0 ||
        offset.x == -m_offset.x && offset.y == -m_offset.y)
      {
        offset.x = ((rand() % 11) - 5);
        offset.y = ((rand() % 11) - 5);
      }

      m_offset = offset;
    }

    // ��������� ������ � ��������� ���������� ���
    // ������� ����������� ������� � ��������� 
    // ���������� � ������� ��� ��������� ������ 
    // ��� ������ �������

    CThread::m_csGDILock.Lock();
    {
      CRect rect(m_pt.x-4, m_pt.y-4, m_pt.x+5, m_pt.y+5);
      dc.FillRect(&rect, &brush);

      m_pt = pt;

      CBrush *pBrush = dc.SelectObject(&m_Brush);
      dc.Rectangle(m_pt.x-4, m_pt.y-4, m_pt.x+5, m_pt.y+5);
      dc.SelectObject(pBrush);

      // Windows ���������� ������ ������� ��������� 
      // ��� ������� �� �������, � ��� ��� �� 
      // ��������� �������� ���������� ���������� 
      // ����� ����������� ������� � ��������� ������ 
      // ������� ��� ����������� �������� ���������
      GdiFlush();
    }
    CThread::m_csGDILock.Unlock();

    // ��������� �������� - ����� ������ ����������
    Sleep(50);
  }

  // ���������� ����������� ���������� �� ������� ������,
  // �.�. �� ������ ���� ����� ������ � ����������
  dc.Detach();

  return 0;
}
