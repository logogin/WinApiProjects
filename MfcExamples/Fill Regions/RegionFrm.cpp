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

  // определяем треугольную область с одной вершиной 
  // в центре клиентской части окна и двумя другими,
  // совпадающими с левым верхним и левым нижним углами
  POINT pt_1[4] = { 0, 0, 
                    rect.right / 2, rect.bottom / 2,
                    0, rect.bottom, 
                    0, 0 };

  CRgn rgn_1;
  rgn_1.CreatePolygonRgn(pt_1, 4, WINDING);

  // определяем треугольную область с одной вершиной 
  // в центре клиентской части окна и двумя другими,
  // совпадающими с правым верхним и правым нижним углами
  POINT pt_2[4] = { rect.right, 0, 
                    rect.right / 2, rect.bottom / 2,
                    rect.right, rect.bottom, 
                    rect.right, 0 };

  CRgn rgn_2;
  rgn_2.CreatePolygonRgn(pt_2, 4, WINDING);

  // определяем прямоугольную область, лежащую точно в
  // центре клиентской области окна и немного ее меньше 
  CRgn rgn;
  rgn.CreateRectRgn(40, 40, rect.right-40, rect.bottom-40);

  // определяем регион как комбинацию трех заданных
  rgn.CombineRgn(&rgn, &rgn_1, RGN_XOR);
  rgn.CombineRgn(&rgn, &rgn_2, RGN_XOR);

  //
  // определяем параметры рисования
  //

  // кисть
  CBrush brush(HS_DIAGCROSS, RGB(0, 0, 0));
  CBrush *pBrush = dc.SelectObject(&brush);

  // цвет фона
  dc.SetBkColor(RGB(128, 128, 128));

  // область отсечения
  dc.SelectObject(&rgn);

  // рисуем прямоугольник на всю клиентскую часть окна
  dc.Rectangle(rect);

  dc.SelectObject(pBrush);
}

