// CreateFontFrm.cpp : implementation file
//

#include "stdafx.h"
#include "CreateFont.h"
#include "CreateFontFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCreateFontFrame

CCreateFontFrame::CCreateFontFrame()
{
}

CCreateFontFrame::~CCreateFontFrame()
{
}


BEGIN_MESSAGE_MAP(CCreateFontFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CCreateFontFrame)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCreateFontFrame message handlers

void CCreateFontFrame::OnPaint() 
{
  CPaintDC dc(this);

	CRect rect;
	GetClientRect(rect);

  CFont font;
  LOGFONT lf = { 
    32, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 
    OUT_TT_ONLY_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY,
    VARIABLE_PITCH | FF_DONTCARE, NULL 
  };

  dc.SetBkMode(TRANSPARENT);

  for (int angle = 0; angle < 3600; angle += 450)
  {
    lf.lfEscapement = angle;
    lf.lfOrientation = angle;

    font.CreateFontIndirect(&lf);

    // назначаем текущим ранее подготовленный шрифт
    CFont *pFont = dc.SelectObject(&font);

    dc.TextOut(rect.Width() / 2, rect.Height() / 2, 
      _T("    Visual C++"));

    dc.SelectObject(pFont);
    font.DeleteObject();
  }
}

