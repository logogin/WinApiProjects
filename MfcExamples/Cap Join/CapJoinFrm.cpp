// CapJoinFrm.cpp : implementation file
//

#include "stdafx.h"
#include "CapJoin.h"
#include "CapJoinFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCapJoinFrame

CCapJoinFrame::CCapJoinFrame()
{
}

CCapJoinFrame::~CCapJoinFrame()
{
}


BEGIN_MESSAGE_MAP(CCapJoinFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CCapJoinFrame)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCapJoinFrame message handlers

void CCapJoinFrame::OnPaint() 
{
  CPaintDC dc(this);

  int nEnd[] = 
    { PS_ENDCAP_ROUND, PS_ENDCAP_SQUARE, PS_ENDCAP_FLAT };

  int nJoin[] = 
    { PS_JOIN_BEVEL, PS_JOIN_MITER, PS_JOIN_ROUND };

  CString csEnd[] = { _T("PS_ENDCAP_ROUND"), 
    _T("PS_ENDCAP_SQUARE"), _T("PS_ENDCAP_FLAT") };

  CString csJoin[] = { _T("PS_JOIN_BEVEL"), 
    _T("PS_JOIN_MITER"), _T("PS_JOIN_ROUND") };

  //
  // создаем и заменяем текущий шрифт,
  // т.к. он слишком велик для вывода 
  // имен режимов
  //

  CFont font;
  font.CreateFont(12, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 
    OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY,
    VARIABLE_PITCH | FF_DONTCARE, "Arial");

  CFont *pFont = dc.SelectObject(&font);

  // устанавливаем режим "прозрачного" вывода 
  dc.SetBkMode(TRANSPARENT);

  // перебираем все возможные комбинации (их 9)
  for (int i = 0; i < 3; i++)
  {
    dc.TextOut(100+i*120, 10, csEnd[i]);
    dc.TextOut(10, 90+i*80, csJoin[i]);

    for (int j = 0; j < 3; j++)
    {
      //
      // для создания карандашей понадобится
      // структура LOGBRUSH
      //

      LOGBRUSH lb;

      lb.lbStyle = BS_SOLID;
      lb.lbColor = RGB(128, 128, 128);
      lb.lbHatch = 0;

      CPen pen(
				PS_SOLID | PS_GEOMETRIC | nEnd[i] | nJoin[j], 
        20, &lb);

      CPen *pPen = dc.SelectObject(&pen);

      // 
      // чтобы увидеть различие режимов
      // придется создавать контуры и только
      // затем их обводить
      //

      dc.BeginPath();

      dc.MoveTo(100+i*120,  50+j*80);
      dc.LineTo(140+i*120, 150+j*80);
      dc.LineTo(180+i*120, 120+j*80);

      dc.EndPath();

      dc.StrokePath();

      // для рисования базовых линий используем
      // карандаш по умолчанию
      dc.SelectObject(pPen);

      dc.MoveTo(100+i*120,  50+j*80);
      dc.LineTo(140+i*120, 150+j*80);
      dc.LineTo(180+i*120, 120+j*80);
    }
  }

  // шрифт так же как и другие графические объекты
  // надо восстановить
  dc.SelectObject(pFont);
}

