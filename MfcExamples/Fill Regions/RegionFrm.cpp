// RegionFrm.cpp : implementation file
//

#include "stdafx.h"
#include "Region.h"
#include "RegionFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRegionFrame

CRegionFrame::CRegionFrame()
{
}

CRegionFrame::~CRegionFrame()
{
}


BEGIN_MESSAGE_MAP(CRegionFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CRegionFrame)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRegionFrame message handlers

void CRegionFrame::OnPaint() 
{
  CPaintDC dc(this);

  CRect rect;
  GetClientRect(rect);

  // ���������� ����������� ������� � ����� �������� 
  // � ������ ���������� ����� ���� � ����� �������,
  // ������������ � ����� ������� � ����� ������ ������
  POINT pt_1[4] = { 0, 0, 
                    rect.right / 2, rect.bottom / 2,
                    0, rect.bottom, 
                    0, 0 };

  CRgn rgn_1;
  rgn_1.CreatePolygonRgn(pt_1, 4, WINDING);

  // ���������� ����������� ������� � ����� �������� 
  // � ������ ���������� ����� ���� � ����� �������,
  // ������������ � ������ ������� � ������ ������ ������
  POINT pt_2[4] = { rect.right, 0, 
                    rect.right / 2, rect.bottom / 2,
                    rect.right, rect.bottom, 
                    rect.right, 0 };

  CRgn rgn_2;
  rgn_2.CreatePolygonRgn(pt_2, 4, WINDING);

  // ���������� ������������� �������, ������� ����� �
  // ������ ���������� ������� ���� � ������� �� ������ 
  CRgn rgn;
  rgn.CreateRectRgn(40, 40, rect.right-40, rect.bottom-40);

  // ���������� ������ ��� ���������� ���� ��������
  rgn.CombineRgn(&rgn, &rgn_1, RGN_XOR);
  rgn.CombineRgn(&rgn, &rgn_2, RGN_XOR);

  //
  // ���������� ��������� ���������
  //

  // �����
  CBrush brush(HS_DIAGCROSS, RGB(0, 0, 0));
  CBrush *pBrush = dc.SelectObject(&brush);

  // ���� ����
  dc.SetBkColor(RGB(128, 128, 128));

  // ������� ���������
  dc.SelectObject(&rgn);

  // ������ ������������� �� ��� ���������� ����� ����
  dc.Rectangle(rect);

  dc.SelectObject(pBrush);
}

