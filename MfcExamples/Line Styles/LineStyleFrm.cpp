// LineStyleFrm.cpp : implementation file
//

#include "stdafx.h"
#include "LineStyle.h"
#include "LineStyleFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLineStyleFrame

CLineStyleFrame::CLineStyleFrame()
{
}

CLineStyleFrame::~CLineStyleFrame()
{
}


BEGIN_MESSAGE_MAP(CLineStyleFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CLineStyleFrame)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLineStyleFrame message handlers

void CLineStyleFrame::OnPaint() 
{
  CPaintDC dc(this);

  struct { int m_nStyle; LPTSTR m_csStyle; } lnStyle[] = {
    PS_SOLID,       _T("PS_SOLID"),
    PS_DASH,        _T("PS_DASH"), 
    PS_DOT,         _T("PS_DOT"),
    PS_DASHDOT,     _T("PS_DASHDOT"), 
    PS_DASHDOTDOT,  _T("PS_DASHDOTDOT"),
    PS_NULL,        _T("PS_NULL"),  
    PS_INSIDEFRAME, _T("PS_INSIDEFRAME")
  };

  //
  // чтобы при любом размере шрифта 
  // текст не налезал друг на друга
  // получим характеристики текущего
  // шрифта
  //
    
  TEXTMETRIC tm;
  dc.GetTextMetrics(&tm);

  // устанавливаем режим "прозрачного" вывода
	dc.SetBkMode(TRANSPARENT);

  for (int i = 0; i < sizeof(lnStyle) / sizeof(lnStyle[0]); i++)
  {
    // будем рисовать разными по стилю карандашами,
    // но имеющими единичную толщину и черный цвет
    CPen pen(lnStyle[i].m_nStyle, 1, RGB(0, 0, 0));
    CPen *pPen = dc.SelectObject(&pen);

    // учитываем высоту символов и расстояние между строками
    int nY = 10+i*(tm.tmHeight+tm.tmExternalLeading);

    dc.TextOut(10, nY, lnStyle[i].m_csStyle);

    dc.MoveTo(200, nY+(tm.tmHeight+tm.tmExternalLeading) / 2);
    dc.LineTo(400, nY+(tm.tmHeight+tm.tmExternalLeading) / 2);

    dc.SelectObject(pPen);
  }
}

