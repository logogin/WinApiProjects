// ClipPathFrm.cpp : implementation file
//

#include "stdafx.h"
#include "ClipPath.h"
#include "ClipPathFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClipPathFrame

CClipPathFrame::CClipPathFrame()
{
}

CClipPathFrame::~CClipPathFrame()
{
}


BEGIN_MESSAGE_MAP(CClipPathFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CClipPathFrame)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClipPathFrame message handlers

void CClipPathFrame::OnPaint() 
{
	CPaintDC dc(this); 

	CFont font;
	font.CreateFont(80, 30, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY,
		VARIABLE_PITCH | FF_DONTCARE, "Arial");

  // назначаем текущим ранее подготовленный шрифт
  CFont *pFont = dc.SelectObject(&font);

  // т.к. строка нам понадобитьс€ несколько раз 
  // создадим объект типа CString, что позволит,
  // кроме всего прочего, использовать версии
  // функций с меньшим количеством параметров
  CString csText = _T("SelectClipPath");

  // узнаем размеры нашей строки, котора€ будет 
  // выведена с использованием нашего шрифта
  CSize sz = dc.GetTextExtent(csText); 

  // сообщаем системе о создании контура
  dc.BeginPath();

  // строка не будет выведена на экран -
  // на основе ее начертани€ будет создан контур 
  dc.TextOut(10, 10, csText);

  // завершаем создание контура
  dc.EndPath();

  // на основе контура создаем и устанавливаем 
  // область отсечени€
  dc.SelectClipPath(RGN_XOR);

  // выводим горизонтальные линии с измен€емым 
  // рассто€нием между ними
  double delta = 2.0;
  for (int i = 0; i < sz.cy; i += (int)delta)
  {
    dc.MoveTo(10, 10+i);
    dc.LineTo(10+sz.cx, 10+i);

    delta *= 1.025;
  }
  
  // устанавливаем ранее используемый шрифт
  dc.SelectObject(pFont);

  // сообщаем системе о том, что далее областью
  // отсечени€ будет вс€ клиентска€ область окна
  dc.SelectClipRgn(NULL);
}

