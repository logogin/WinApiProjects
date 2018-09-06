// CreateBmpTwoFrm.cpp : implementation file
//

#include "stdafx.h"
#include "CreateBmpTwo.h"
#include "CreateBmpTwoFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCreateBmpTwoFrame

CCreateBmpTwoFrame::CCreateBmpTwoFrame()
{
}

CCreateBmpTwoFrame::~CCreateBmpTwoFrame()
{
}


BEGIN_MESSAGE_MAP(CCreateBmpTwoFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CCreateBmpTwoFrame)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCreateBmpTwoFrame message handlers

void CCreateBmpTwoFrame::OnPaint() 
{
  CPaintDC dc(this);

  int CX = 400, CY = 100;

  DWORD *lpbInit = new DWORD[CX * CY];

  for (int i = 0; i < CY; i++)
  {
    for (int j = 0; j < CX; j++)
    {
      BYTE color = (BYTE)(255-abs(i*255/(CY/2)-255));

      lpbInit[i*CX+j] = RGB(color, color, color);
    }
  }

  BITMAPINFO bmi = {
    sizeof(BITMAPINFOHEADER), CX, CY, 1, 32, BI_RGB, 0,
    0, 0, 0, 0 
  };

  HBITMAP hBitmap = ::CreateDIBitmap(
    dc.GetSafeHdc(), &bmi.bmiHeader, CBM_INIT,
    lpbInit, &bmi, DIB_RGB_COLORS);

  CBitmap bitmap;
  bitmap.Attach(hBitmap);

  dc.DrawState(CPoint(10, 10), CSize(CX, CY), 
    &bitmap, DST_BITMAP);

  bitmap.DeleteObject();

  delete lpbInit;
}

