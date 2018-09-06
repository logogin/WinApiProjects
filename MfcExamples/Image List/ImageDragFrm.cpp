/*************************************************************
���� ImageDragFrm.cpp
Copyright (c) 1999 ������ �., ��������� �.
*************************************************************/

// ImageDragFrm.cpp : implementation file
//

#include "stdafx.h"
#include "ImageDrag.h"
#include "ImageDragFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////
// CImageDragFrame

CImageDragFrame::CImageDragFrame()
{
}

CImageDragFrame::~CImageDragFrame()
{
}


BEGIN_MESSAGE_MAP(CImageDragFrame, CFrameWnd)
  //{{AFX_MSG_MAP(CImageDragFrame)
  ON_WM_PAINT()
  ON_WM_CREATE()
  ON_WM_LBUTTONDOWN()
  ON_WM_MOUSEMOVE()
  ON_WM_LBUTTONUP()
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////
// CImageDragFrame message handlers

void CImageDragFrame::OnPaint() 
{
  CPaintDC dc(this); 

  // ����������� �����������
  m_List.Draw(&dc, 0, m_pt, ILD_TRANSPARENT);
}


int CImageDragFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
  if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
    return -1;

  // �������� ������ �����������
  m_List.Create(32, 32, TRUE, 1, 1);
  // ���������� �����������
  m_List.Add(AfxGetApp()->LoadIcon(IDR_IMAGEDRAG));

  // ��������� ������������� �������������� ����������
  m_pt = CPoint(0, 0);
  m_Drag = FALSE;

  return 0;
}

void CImageDragFrame::OnLButtonDown(UINT nFlags, CPoint point) 
{
  CRect rect(m_pt.x, m_pt.y, m_pt.x+32, m_pt.y+32);

  // �������� �� ������� ������� ���� � ������ �����������
  if (rect.PtInRect(point))
  {
    // �������� �����������
    m_Drag = TRUE;
    m_List.BeginDrag(0, CPoint(0, 0));

    // �������������� ���������
    GetWindowRect(&rect);

    CPoint pt = point;
    ClientToScreen(&pt);
    m_List.DragEnter(this,
      CPoint(pt.x - rect.left, pt.y - rect.top));
  }
  else
    m_Drag = FALSE;
  
  CFrameWnd::OnLButtonDown(nFlags, point);
}

void CImageDragFrame::OnMouseMove(UINT nFlags, CPoint point) 
{
  if (m_Drag)
  {
    // �������������� ���������
    CRect rect;
    GetWindowRect(&rect);
    
    CPoint pt = m_pt = point;
    ClientToScreen(&pt);

    // �����������
    m_List.DragMove(CPoint(pt.x - rect.left, pt.y - rect.top));
  }
  
  CFrameWnd::OnMouseMove(nFlags, point);
}

void CImageDragFrame::OnLButtonUp(UINT nFlags, CPoint point) 
{
  if (m_Drag)
  {
    // ���������� �����������
    m_List.DragLeave(this);

    m_List.EndDrag();
    m_Drag = FALSE;

    // ���������� ����������� ����, �.�. ����� ������
    // ������� DragLeave ����������� ���� ������
    InvalidateRect(NULL);
  }
  
  CFrameWnd::OnLButtonUp(nFlags, point);
}
