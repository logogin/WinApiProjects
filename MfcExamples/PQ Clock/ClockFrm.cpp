/*************************************************************
���� ClockFrm.cpp
Copyright (c) 1999 ������ �., ��������� �.
*************************************************************/

// ClockFrm.cpp : implementation file
//

#include "stdafx.h"
#include "PQClock.h"
#include "ClockFrm.h"

#include "math.h"

// ��� ����������� ��������� ������
// ��������� �� � ����� ����� � 
// � ������ �����
#define COLOR_BCKGR   RGB(224,224,224)
#define COLOR_WHITE   RGB(255,255,255)
#define COLOR_BLACK   RGB(  0,  0,  0)
#define COLOR_ARROW   RGB(164,164,  0)
#define COLOR_CLOCK   RGB(164,164,  0)
#define COLOR_ROUND   RGB( 92, 92,  0)
#define COLOR_CRNER   RGB( 92, 92,  0)

#define TWOPI         (2 * 3.14159)

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClockFrame

CClockFrame::CClockFrame()
{
}

CClockFrame::~CClockFrame()
{
}

//
// ������� ���������� ������� ��������� �����
// � ����������� �� ����
//
void CClockFrame::RotatePoint(POINT pt[], int nNum, double nAngle)
{
  POINT ptTemp;

  // ������� �������������� ������ ������ ���������
  for (int i = 0 ; i < nNum; i++)
  {
    ptTemp.x = (int)(pt[i].x * cos (TWOPI * nAngle / 360) +
                     pt[i].y * sin (TWOPI * nAngle / 360));

    ptTemp.y = (int)(pt[i].y * cos (TWOPI * nAngle / 360) -
                     pt[i].x * sin (TWOPI * nAngle / 360));

    pt[i] = ptTemp;
  }
}

//
// ������� ������������ ������� ���������
//
void CClockFrame::SetMode(CDC *pDC)
{
  // ������������� �������, ������ � �����������
  // ������������ ����
  pDC->SetMapMode(MM_ISOTROPIC);
  pDC->SetWindowExt(1000, 1000);
  pDC->SetViewportExt(m_cxClient / 2, -m_cyClient / 2); 
  pDC->SetViewportOrg(m_cxClient / 2,  m_cyClient / 2);
  
  // � ����������:
  //   ������ ��������� � �������� ���������� ������� ����
  //   ���-x ���������� �����
  //   ���-y ���������� �����
  //   ������ ���� 2000 X 2000 ���������� ������
  //     X: [-1000; +1000]
  //     Y: [-1000; +1000]
}

//
// ������� ��������� ���������� �����
//
void CClockFrame::DrawClock(CDC *pDC)
{
  CPen *pPen;
  CBrush *pBrush;

  int nAngle;

  //
  // ������ ������� ��� ������� ����,
  // ������ ��� 12-��, 3-�, 6-�� � 9-��
  // ������� - ��������������,
  // ��� ��������� - �����
  //
  
  pBrush = pDC->SelectObject(&m_clkBrush);

  for (nAngle = 0; nAngle < 360; nAngle += 30)
  {
    POINT pt[2] = { 0, 900 };

    RotatePoint(pt, 1, nAngle);

    int x = (nAngle % 180) ? 70 : 250;
    int y = ((nAngle+90) % 180) ? 70 : 250;

    pt[0].x -= x / 2;
    pt[0].y -= y / 2;

    pt[1].x  = pt[0].x + x;
    pt[1].y  = pt[0].y + y;

    if (nAngle % 90)
      pDC->Ellipse(pt[0].x, pt[0].y, pt[1].x, pt[1].y);
    else
    {
      pDC->RoundRect(pt[0].x, pt[0].y, pt[1].x, pt[1].y, 
        min(x, y) / 2, min(x, y) / 2);
    }
  }

  //
  // ������ ���� ����� �������� ���������
  // ���, ����� �� ������� ��� ������� 
  // ������ ���������� �� ������� �����������
  // ������� �������
  //

  pPen = pDC->SelectObject(&m_rndPen);

  POINT ptPrev;

  for (nAngle = -30; nAngle < 360; nAngle += 30)
  {
    POINT pt[2] = { -45, 950, 45, 950 };

    RotatePoint(pt, 2, nAngle);

    if (nAngle != -30)
    {
      pDC->Arc(-980, -980, 980, 980, 
        pt[0].x, pt[0].y, ptPrev.x, ptPrev.y);
    }

    ptPrev = pt[1];
  }

  //
  // ������ "����" �����, ������
  // �������� ���������� ���������
  //

  CRect round(-1100, -1100, 1100, 1100);

  CRgn rgn;
  CRect rect;

  pDC->SelectObject(&m_crnPen);
  pDC->SelectObject(&m_crnBrush);
  
  //
  // 1-�� ������:
  // ������ ����� ������� ����
  //

  rect = CRect(-950, 950, -550, 550);
  pDC->LPtoDP(&rect);

  // ��������� ������� ���������,
  // ��� ����� ����� ���������� � �������� 
  // ���������� ������
  rgn.CreateRectRgnIndirect(&rect);
  pDC->SelectObject(&rgn);

  // ������ ��������� ���� (����), �� ���������
  // ������ �� ����� � ������������ � �������� 
  // �������� ���������
  pDC->Arc(&round, CPoint(0, 0), CPoint(0, 0));

  // ��������� ��� ����� ��� ������������ 
  // ���������� �������
  pDC->MoveTo(-550, 950);
  pDC->LineTo(-950, 950);
  pDC->LineTo(-950, 550);

  // ��������� ��� ��������� ��� ���������� ����� ����
  pDC->SelectClipRgn(NULL);

  // ��������� ��������� ������� 
  // � ���������� ����� �� �������
  pDC->ExtFloodFill(-900, 900, COLOR_CRNER, FLOODFILLBORDER);

  //
  // 2-�� ������:
  // ������ ������ ������� ����
  //

  // ������ ���� � ��� ����� ��� ������������ 
  // ���������� �������
  pDC->Arc(&round, CPoint(950, 550), CPoint(550, 950));
  pDC->MoveTo(550, 950);
  pDC->LineTo(950, 950);
  pDC->LineTo(950, 550);

  // ��������� ��������� �������, �������� ������
  // � ���������� �����
  pDC->ExtFloodFill(900, 900, COLOR_BCKGR, FLOODFILLSURFACE);

  //
  // 3-�� ������:
  // ������ ������ ������ ����
  //

  //
  // ������� ��� �������
  //

  // ������ - �������������, � ����
  //   ������ ������ ����������
  rect = CRect(550, -950, 950, -550);

  CRgn rgn1;
  rgn1.CreateRectRgnIndirect(&rect);

  // ������ - �������������, �� ��� ���
  //   ����� ����������
  CRect rect2 = round;

  CRgn rgn2;
  rgn2.CreateEllipticRgnIndirect(&rect2);

  // �� ������ ��������� �������� �������
  // ��������������� � ������ ��� ������
  rgn.CombineRgn(&rgn1, &rgn2, RGN_DIFF);

  // ����������� ���
  pDC->PaintRgn(&rgn);

  rgn.DeleteObject();
  rgn1.DeleteObject();
  rgn2.DeleteObject();

  //
  // 4-�� ������:
  // ������ ����� ������ ����
  //

  //
  // �������� ������������ �������
  //

  pDC->BeginPath();

  // ������ ����� ��� ��������� 
  // ������ �����
  POINT pt[] = {
    -950, -550,  
    -950, -670,    
    -670, -950, 
    -550, -950 
  };

  // "������" ������ �����, �.�. ������
  // ������� ��������� ������� ������
  // �� ����������� � �������
  pDC->PolyBezier(pt, 4);

  // ��������� ��� ����� ��� ������������ 
  // ���������� �������
  pDC->MoveTo(-950, -550);
  pDC->LineTo(-950, -950);
  pDC->LineTo(-550, -950);

  pDC->EndPath();

  // ����������� ������������ ������������ 
  // �������������� ��������
  pDC->FillPath();

  pDC->SelectObject(pPen);
  pDC->SelectObject(pBrush);
}

//
// ������� ��������� ����� ������ �� ����������
//
void CClockFrame::DrawLabel(CDC *pDC)
{
  pDC->SetTextAlign(TA_CENTER);

  // ������ ��� ������ ������, ��� �����
  // ���������� ����������� ������ ����
  COLORREF color = pDC->SetBkColor(COLOR_BCKGR);

  CFont *pFont = pDC->SelectObject(&m_Font_1);
  pDC->TextOut(0,  600, _T("PRAGMA"), 6);

  TEXTMETRIC tm;
  pDC->GetTextMetrics(&tm);

  pDC->SelectObject(&m_Font_2);
  pDC->TextOut(0,  600-(tm.tmHeight+tm.tmExternalLeading), 
    _T("QUARTZ"), 6);

  pDC->SetBkColor(color);

  // ��������� ������ ������ ���, �����
  // ���������� ����� �������� ��������
  // ���������� ��� ��������� - ����
  // ���� ������� �� ��� ������� �� ���������
  pDC->SetBkMode(TRANSPARENT);

  pDC->SelectObject(&m_Font_3);
  pDC->TextOut(0, -500, _T("NO WATER RESIST"));

  pDC->SelectObject(pFont);
}

//
// ������� ������ ������� �������������� ���
// �� �������� ���������� � ������
//
void CClockFrame::DrawArrows(CDC *pDC, CTime &tm)
{
  // ������ �����, ������� ���������� ������� �������
  static POINT pt[3][11] = 
  { 
      0,  -50, -50,    0, -5,   40, -5,  100, -30,  120, 
      0,  600,  30,  
    120,    5, 100,    5, 40,   50,  0,    0, -50,

      0,  -40, -40,    0, -5,   30, -5,   90, -20,  110, 
      0,  800, 
     20,  110,   5,   90,  5,   30, 40,    0,   0,  -40,

      0, -100,  -5, -100, -5, -100, -5, -100,  -5, -100, 
      0,  850,  
      5, -100,   5, -100,  5, -100,  5, -100,   0, -100
  };

  double nAngle[3];

  // ��������� ���� �������� ������ �� ���� �������
  nAngle[0] = (tm.GetHour()   * 30) % 360 + tm.GetMinute() / 2;
  nAngle[1] = (tm.GetMinute() * 60 + tm.GetSecond()) / 10.0;
  nAngle[2] = (tm.GetSecond() *  6);

  POINT ptTemp[3][11];
  memcpy(ptTemp, pt, sizeof(pt));

  for (int i = 0; i < 3; i++)
  {
    // ���������� ������� ��������� ���� �����
    // ������� �������
    RotatePoint(ptTemp[i], 11, nAngle[i]);

    // ��������� �������
    pDC->Polygon(ptTemp[i], 11);
  }
}

//
// ������� ����������� �����, ����� ����������
// ����������� � ����� ������� ���������
//
void CClockFrame::Redraw()
{
  static CTime m_tmPrev;

  if (IsIconic())
    return;

  CClientDC dc(this);

  CTime tmCurrent = CTime::GetCurrentTime();

  if (tmCurrent != m_tmPrev)
  {
    // ������������� ���� ������� ���������
    SetMode(&dc);

    // ������ ���������
    DrawClock(&dc);  

    // ����������� ������ ���� ����� ���������� �������
    CPen *pPen = dc.SelectObject(&m_wndPen);
    CBrush *pBrush = dc.SelectObject(&m_wndBrush);

    DrawArrows(&dc, m_tmPrev);

    // ������� ����� ��������
    DrawLabel(&dc);

    // ������� ������� �� �� ������ �����
    dc.SelectObject(&m_arrPen);
    dc.SelectObject(&m_arrBrush);

    DrawArrows(&dc, tmCurrent);

    dc.SelectObject(pBrush);
    dc.SelectObject(pPen);
  }

  m_tmPrev = tmCurrent;
}


BEGIN_MESSAGE_MAP(CClockFrame, CFrameWnd)
  //{{AFX_MSG_MAP(CClockFrame)
  ON_WM_SIZE()
  ON_WM_PAINT()
  ON_WM_CREATE()
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClockFrame message handlers

void CClockFrame::OnSize(UINT nType, int cx, int cy) 
{
  CFrameWnd::OnSize(nType, cx, cy);

  // ���������� ������ ���������� �������
  // ����, ����� ������ ��� ��� �����������
  // �� ����������� ������ ������
  m_cxClient = cx;
  m_cyClient = cy;
}

void CClockFrame::OnPaint() 
{
  CPaintDC dc(this); 

  // ����������� ���������� �������
  CBrush brush(COLOR_BCKGR);
  dc.FillRect(
    CRect(0, 0, m_cxClient, m_cyClient), &brush);

  // ���������, ����� � ������� �������� �� �����, 
  // ���� �������� ������� CPQClock::OnIdle
}

int CClockFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
  if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
    return -1;
  
  //
  // ��� �������� ������� ������ ����, ����� ���
  // ��������� ��������� ������, ��������� � �����
  // ������� ��� ���� ���, ��� ���� ���� �������, ���
  // ����������� ����� ������� ������� ����� �����������
  // ��� �������� ������� ������ CClockFrame
  //

  m_Font_1.CreateFont(130, 0, 0, 0, FW_BOLD, 
    0, 0, 0, DEFAULT_CHARSET, 
    OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY,
    VARIABLE_PITCH | FF_DONTCARE, "Arial");

  m_Font_2.CreateFont(100, 0, 0, 0, FW_BOLD, 
    0, 0, 0, DEFAULT_CHARSET, 
    OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY,
    VARIABLE_PITCH | FF_SWISS, "Arial");

  m_Font_3.CreateFont(70, 0, 0, 0, FW_BOLD, 
    0, 0, 0, DEFAULT_CHARSET, 
    OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY,
    VARIABLE_PITCH | FF_SWISS, "Arial");

  m_wndBrush.CreateSolidBrush(COLOR_BCKGR);
  m_wndPen.CreatePen(PS_SOLID, 1, COLOR_BCKGR);

  m_arrBrush.CreateHatchBrush(HS_DIAGCROSS, COLOR_ARROW);
  m_arrPen.CreatePen(PS_SOLID, 1, COLOR_BLACK);

  m_clkBrush.CreateSolidBrush(COLOR_CLOCK);
  m_clkPen.CreatePen(PS_SOLID, 1, COLOR_BLACK);

  m_rndBrush.CreateSolidBrush(COLOR_ROUND);

	// ������� ������������� ������ ��� �����, 
	// ��� ������� ������� ��������, � ����� �������
	// �� ������ �� ���������, �.�. ��� ��������
	// �����������, ����� ��������� �������������� 
	// ��� ������ �������� ��������, � ������ ��������
	// ����� ��������������� ��� ��������� ���, �������
	// �������� CDC::StrokePath �� �������������
  LOGBRUSH lb;
  m_rndBrush.GetLogBrush(&lb);
  m_rndPen.CreatePen(PS_SOLID | PS_GEOMETRIC | 
		PS_ENDCAP_SQUARE, 20, &lb);

  m_crnBrush.CreateSolidBrush(COLOR_CRNER);
  m_crnPen.CreatePen(PS_SOLID, 1, COLOR_CRNER);
  
  return 0;
}
