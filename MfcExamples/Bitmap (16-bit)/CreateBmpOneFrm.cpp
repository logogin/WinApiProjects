// CreateBmpOneFrm.cpp : implementation file
//

#include "stdafx.h"
#include "CreateBmpOne.h"
#include "CreateBmpOneFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCreateBmpOneFrame

CCreateBmpOneFrame::CCreateBmpOneFrame()
{
}

CCreateBmpOneFrame::~CCreateBmpOneFrame()
{
}


BEGIN_MESSAGE_MAP(CCreateBmpOneFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CCreateBmpOneFrame)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCreateBmpOneFrame message handlers

void CCreateBmpOneFrame::OnPaint() 
{
  CPaintDC dc(this);

  int CX = 400, CY = 100;

  // ��������, ��� ���������� ���
  // ����������� ��� ������ ���� WORD - 16 ���
  WORD *lpvBits = new WORD[CX * CY];

  for (int i = 0; i < CY; i++)
  {
    for (int j = 0; j < CX; j++)
    {
      WORD color = 31-abs(i*31/(CY/2)-31);

      // ��������, ��� ���������� ������
      // ������� ��� �������� ����� 16 ���, ������
      // ��� �������� - ������� 5
      // ��� �������� - ������� 6
      // ��� ������   - ������� 5
      lpvBits[i*CX+j] = 
        (WORD)((color << 11) + (color*2 << 5) + color);
    }
  }

  CBitmap bitmap;

  // ������ ������� �������� �������� �������
  bitmap.CreateCompatibleBitmap(&dc, CX, CY);
  bitmap.SetBitmapBits(sizeof(WORD) * CX * CY, lpvBits);

  // ������ ������� �������� �������� �������
  // bitmap.CreateBitmap(CX, CY, 1, 16, lpvBits);

  // ����� ��������, ��� ���-������ ����� ��������
  dc.DrawState(CPoint(10, 10), 
    CSize(CX, CY), &bitmap, DST_BITMAP);

  delete lpvBits;
}

