/*************************************************************
Файл ClockFrm.cpp
Copyright (c) 1999 Мешков А., Тихомиров Ю.
*************************************************************/

// ClockFrm.cpp : implementation file
//

#include "stdafx.h"
#include "PQClock.h"
#include "ClockFrm.h"

#include "math.h"

// для возможности изменения цветов
// определим их в одном месте и 
// в начале файла
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
// функция вычисления текущих координат точек
// в зависимости от угла
//
void CClockFrame::RotatePoint(POINT pt[], int nNum, double nAngle)
{
  POINT ptTemp;

  // поворот осуществляется вокруг начала координат
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
// функция формирования системы координат
//
void CClockFrame::SetMode(CDC *pDC)
{
  // устанавливаем масштаб, начало и направление
  // координатных осей
  pDC->SetMapMode(MM_ISOTROPIC);
  pDC->SetWindowExt(1000, 1000);
  pDC->SetViewportExt(m_cxClient / 2, -m_cyClient / 2); 
  pDC->SetViewportOrg(m_cxClient / 2,  m_cyClient / 2);
  
  // в результате:
  //   начало координат в середине клиентской области окна
  //   ось-x направлена влево
  //   ось-y направлена вверх
  //   размер окна 2000 X 2000 логических единиц
  //     X: [-1000; +1000]
  //     Y: [-1000; +1000]
}

//
// функция рисования циферблата часов
//
void CClockFrame::DrawClock(CDC *pDC)
{
  CPen *pPen;
  CBrush *pBrush;

  int nAngle;

  //
  // рисуем отметки для каждого часа,
  // причем для 12-ти, 3-х, 6-ти и 9-ти
  // отметки - прямоугольники,
  // для остальных - круги
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
  // рисуем дуги между часовыми отметками
  // так, чтобы их диаметр был немного 
  // больше окружности на которой расположены
  // часовые отметки
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
  // рисуем "углы" часов, причем
  // четырьмя различными способами
  //

  CRect round(-1100, -1100, 1100, 1100);

  CRgn rgn;
  CRect rect;

  pDC->SelectObject(&m_crnPen);
  pDC->SelectObject(&m_crnBrush);
  
  //
  // 1-ый способ:
  // рисуем левый верхний угол
  //

  rect = CRect(-950, 950, -550, 550);
  pDC->LPtoDP(&rect);

  // формируем область отсечения,
  // для этого нужны координаты в единицах 
  // устройства вывода
  rgn.CreateRectRgnIndirect(&rect);
  pDC->SelectObject(&rgn);

  // рисуем замкнутую дугу (круг), но выводится
  // только ее часть в соответствии с заданной 
  // областью отсечения
  pDC->Arc(&round, CPoint(0, 0), CPoint(0, 0));

  // добавляем две линии для формирования 
  // замкнутого контура
  pDC->MoveTo(-550, 950);
  pDC->LineTo(-950, 950);
  pDC->LineTo(-950, 550);

  // разрешаем для рисования всю клиентскую часть окна
  pDC->SelectClipRgn(NULL);

  // заполняем замкнутую область 
  // с внутренней точки до границы
  pDC->ExtFloodFill(-900, 900, COLOR_CRNER, FLOODFILLBORDER);

  //
  // 2-ой способ:
  // рисуем правый верхний угол
  //

  // рисуем дугу и две линии для формирования 
  // замкнутого контура
  pDC->Arc(&round, CPoint(950, 550), CPoint(550, 950));
  pDC->MoveTo(550, 950);
  pDC->LineTo(950, 950);
  pDC->LineTo(950, 550);

  // заполняем замкнутую область, заданную цветом
  // с внутренней точки
  pDC->ExtFloodFill(900, 900, COLOR_BCKGR, FLOODFILLSURFACE);

  //
  // 3-ий способ:
  // рисуем правый нижний угол
  //

  //
  // создаем два региона
  //

  // первый - прямоугольный, в него
  //   вписан радиус окружности
  rect = CRect(550, -950, 950, -550);

  CRgn rgn1;
  rgn1.CreateRectRgnIndirect(&rect);

  // второй - эллиптический, он как раз
  //   равен окружности
  CRect rect2 = round;

  CRgn rgn2;
  rgn2.CreateEllipticRgnIndirect(&rect2);

  // на основе созданных регионов создаем
  // комбинированный с нужной нам формой
  rgn.CombineRgn(&rgn1, &rgn2, RGN_DIFF);

  // закрашиваем его
  pDC->PaintRgn(&rgn);

  rgn.DeleteObject();
  rgn1.DeleteObject();
  rgn2.DeleteObject();

  //
  // 4-ый способ:
  // рисуем левый нижний угол
  //

  //
  // начинаем формирование контура
  //

  pDC->BeginPath();

  // массив точек для рисования 
  // кривой Безье
  POINT pt[] = {
    -950, -550,  
    -950, -670,    
    -670, -950, 
    -550, -950 
  };

  // "рисуем" кривую Безье, т.к. другие
  // функции рисования гладких кривых
  // не фиксируются в контуре
  pDC->PolyBezier(pt, 4);

  // добавляем две линии для формирования 
  // замкнутого контура
  pDC->MoveTo(-950, -550);
  pDC->LineTo(-950, -950);
  pDC->LineTo(-550, -950);

  pDC->EndPath();

  // закрашиваем пространство ограниченное 
  // сформированным контуром
  pDC->FillPath();

  pDC->SelectObject(pPen);
  pDC->SelectObject(pBrush);
}

//
// функция рисования строк текста на циферблате
//
void CClockFrame::DrawLabel(CDC *pDC)
{
  pDC->SetTextAlign(TA_CENTER);

  // первые две строки рисуем, так чтобы
  // промежутки заполнялись цветом фона
  COLORREF color = pDC->SetBkColor(COLOR_BCKGR);

  CFont *pFont = pDC->SelectObject(&m_Font_1);
  pDC->TextOut(0,  600, _T("PRAGMA"), 6);

  TEXTMETRIC tm;
  pDC->GetTextMetrics(&tm);

  pDC->SelectObject(&m_Font_2);
  pDC->TextOut(0,  600-(tm.tmHeight+tm.tmExternalLeading), 
    _T("QUARTZ"), 6);

  pDC->SetBkColor(color);

  // последнюю строку рисуем так, чтобы
  // промежутки между контуров символов
  // оставались без изменения - цвет
  // фона влияния на эти области не оказывает
  pDC->SetBkMode(TRANSPARENT);

  pDC->SelectObject(&m_Font_3);
  pDC->TextOut(0, -500, _T("NO WATER RESIST"));

  pDC->SelectObject(pFont);
}

//
// функция вывода стрелок установленными вне
// ее текущими карандашом и кистью
//
void CClockFrame::DrawArrows(CDC *pDC, CTime &tm)
{
  // массив точек, которые определяют контуры стрелок
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

  // вычисляем углы поворота каждой из трех стрелок
  nAngle[0] = (tm.GetHour()   * 30) % 360 + tm.GetMinute() / 2;
  nAngle[1] = (tm.GetMinute() * 60 + tm.GetSecond()) / 10.0;
  nAngle[2] = (tm.GetSecond() *  6);

  POINT ptTemp[3][11];
  memcpy(ptTemp, pt, sizeof(pt));

  for (int i = 0; i < 3; i++)
  {
    // вычисление текущих координат всех точек
    // контура стрелки
    RotatePoint(ptTemp[i], 11, nAngle[i]);

    // рисование стрелки
    pDC->Polygon(ptTemp[i], 11);
  }
}

//
// функция перерисовки часов, может вызываться
// практически в любой функции программы
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
    // устанавливаем нашу систему координат
    SetMode(&dc);

    // рисуем циферблат
    DrawClock(&dc);  

    // закрашиваем цветом фона ранее выведенные стрелки
    CPen *pPen = dc.SelectObject(&m_wndPen);
    CBrush *pBrush = dc.SelectObject(&m_wndBrush);

    DrawArrows(&dc, m_tmPrev);

    // выводим текст надписей
    DrawLabel(&dc);

    // выводим стрелки по их новому месту
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

  // запоминаем размер клиентской области
  // окна, чтобы каждый раз при перерисовке
  // не запрашивать размер заново
  m_cxClient = cx;
  m_cyClient = cy;
}

void CClockFrame::OnPaint() 
{
  CPaintDC dc(this); 

  // закрашиваем клиентскую область
  CBrush brush(COLOR_BCKGR);
  dc.FillRect(
    CRect(0, 0, m_cxClient, m_cyClient), &brush);

  // циферблат, текст и стрелки рисовать не будем, 
  // этим займется функция CPQClock::OnIdle
}

int CClockFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
  if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
    return -1;
  
  //
  // для экономии времени вместо того, чтобы при
  // рисовании создавать шрифты, карандаши и кисти
  // сделаем это один раз, при этом надо помнить, что
  // захваченные таким образом ресурсы будут освобождены
  // при удалении объекта класса CClockFrame
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

	// задание прямоугольных концов для линий, 
	// для которых создаем карандаш, в нашем примере
	// не влияет на рисование, т.к. это свойство
	// проявляется, когда рисование осуществляется 
	// при помощи создания контуров, а данный карандаш
	// будет использвоваться для рисования дуг, которые
	// функцией CDC::StrokePath не отображаеются
  LOGBRUSH lb;
  m_rndBrush.GetLogBrush(&lb);
  m_rndPen.CreatePen(PS_SOLID | PS_GEOMETRIC | 
		PS_ENDCAP_SQUARE, 20, &lb);

  m_crnBrush.CreateSolidBrush(COLOR_CRNER);
  m_crnPen.CreatePen(PS_SOLID, 1, COLOR_CRNER);
  
  return 0;
}
