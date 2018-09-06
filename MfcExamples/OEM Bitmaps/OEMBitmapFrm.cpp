// OEMBitmapFrm.cpp : implementation file
//

#include "stdafx.h"
#include "OEMBitmap.h"
#include "OEMBitmapFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

struct { int m_nBitmap; LPTSTR m_csBitmap; } btBitmap[] = {
  OBM_LFARROWI,   _T("OBM_LFARROWI"),
  OBM_LFARROWD,   _T("OBM_LFARROWD"),
  OBM_LFARROW,    _T("OBM_LFARROW"),

  OBM_RGARROWI,   _T("OBM_RGARROWI"),
  OBM_RGARROWD,   _T("OBM_RGARROWD"),
  OBM_RGARROW,    _T("OBM_RGARROW"),

  OBM_DNARROWI,   _T("OBM_DNARROWI"),
  OBM_DNARROWD,   _T("OBM_DNARROWD"),
  OBM_DNARROW,    _T("OBM_DNARROW"),

  OBM_UPARROWI,   _T("OBM_UPARROWI"),
  OBM_UPARROWD,   _T("OBM_UPARROWD"),
  OBM_UPARROW,    _T("OBM_UPARROW"),

  OBM_COMBO,      _T("OBM_COMBO"),
  OBM_MNARROW,    _T("OBM_MNARROW"),

  OBM_RESTORED,   _T("OBM_RESTORED"),
  OBM_RESTORE,    _T("OBM_RESTORE"),

  OBM_ZOOMD,      _T("OBM_ZOOMD"),
  OBM_ZOOM,       _T("OBM_ZOOM"),

  OBM_REDUCED,    _T("OBM_REDUCED"),
  OBM_REDUCE,     _T("OBM_REDUCE"),

  OBM_BTNCORNERS, _T("OBM_BTNCORNERS"),

  OBM_CHECK,      _T("OBM_CHECK"),

  OBM_BTSIZE,     _T("OBM_BTSIZE"),
  OBM_SIZE,       _T("OBM_SIZE"),

  OBM_CHECKBOXES, _T("OBM_CHECKBOXES"),

  OBM_CLOSE,      _T("OBM_CLOSE") };

/////////////////////////////////////////////////////////////////////////////
// COEMBitmapFrame

COEMBitmapFrame::COEMBitmapFrame()
{
}

COEMBitmapFrame::~COEMBitmapFrame()
{
}


BEGIN_MESSAGE_MAP(COEMBitmapFrame, CFrameWnd)
	//{{AFX_MSG_MAP(COEMBitmapFrame)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COEMBitmapFrame message handlers

void COEMBitmapFrame::OnPaint() 
{
  CPaintDC dc(this);

  TEXTMETRIC tm;
  dc.GetTextMetrics(&tm);

  // устанавливаем режим "прозрачного" вывода 
  dc.SetBkMode(TRANSPARENT);

	int nY = 10;
  int nX = 10;

  CBitmap bitmap;

  for (int i = 0; i < sizeof(btBitmap) / sizeof(btBitmap[0]); i++)
  {
    // загружаем системный битовый массив
    bitmap.LoadOEMBitmap(btBitmap[i].m_nBitmap);

    // 
    // получаем размеры, заполняя структуру BITMAP
    //

    BITMAP bmp;

    // первый способ -
    // используем функцию GetObject
    bitmap.GetObject(sizeof(BITMAP), &bmp);

    // второй способ -
    // используем функцию GetBitmap
    // bitmap.GetBitmap(&bmp);

    CSize sz(bmp.bmWidth, bmp.bmHeight);

    dc.DrawState(CPoint(nX, nY), sz, 
      bitmap, DST_BITMAP);

    dc.TextOut(nX+60, 
      nY-tm.tmInternalLeading, btBitmap[i].m_csBitmap);

    // сдвиг вниз на 5 пикселей больше, чем
    // максимальная высота битового массива или
    // соответствующего текста
    nY += max(sz.cy, tm.tmHeight) + 5;

    bitmap.DeleteObject();  

    // выводим изображения и текст в две колонки
    if (i == sizeof(btBitmap) / sizeof(btBitmap[0]) / 2)
    {
      nX += 200;
      nY = 10;
    }
	}
}

