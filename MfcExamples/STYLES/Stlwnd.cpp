/////////////////////////////////////////////////////////////
// Файл ChildWindows.cpp
// Copyright (c) 1999 Мешков А., Тихомиров Ю.
/////////////////////////////////////////////////////////////

// implementation file
//

#include "stdafx.h"

#include "Styles.h"
#include "StlWnd.h"

int nCount = 0;

DWORD adwStyles[] =
{
  WS_CAPTION | WS_CLIPSIBLINGS,
  WS_CAPTION | WS_SYSMENU | WS_HSCROLL | WS_VSCROLL |
 WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_CLIPSIBLINGS,
  WS_THICKFRAME | WS_CLIPSIBLINGS,
  WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_CLIPSIBLINGS,
  WS_CAPTION | WS_SYSMENU | WS_HSCROLL | WS_VSCROLL | WS_CLIPSIBLINGS,
  WS_POPUP,
  WS_POPUP | WS_CAPTION | WS_THICKFRAME,
  WS_POPUP | WS_CAPTION | WS_SYSMENU |
 WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
  WS_POPUP | WS_CAPTION | WS_SYSMENU |
 WS_HSCROLL | WS_VSCROLL |WS_DISABLED,
  WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU |
 WS_HSCROLL | WS_VSCROLL
};

char *aszStyles[] =
{
  "WS_CAPTION | WS_CLIPSIBLINGS",
  "WS_CAPTION | WS_SYSMENU | WS_HSCROLL | WS_VSCROLL |\
 WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_CLIPSIBLINGS",
  "WS_THICKFRAME | WS_CLIPSIBLINGS",
  "WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX |\
 WS_MAXIMIZEBOX | WS_CLIPSIBLINGS",
  "WS_CAPTION | WS_SYSMENU | WS_HSCROLL |\
 WS_VSCROLL | WS_CLIPSIBLINGS",
  "WS_POPUP",
  "WS_POPUP | WS_CAPTION | WS_THICKFRAME",
  "WS_POPUP | WS_CAPTION | WS_SYSMENU |\
 WS_MINIMIZEBOX | WS_MAXIMIZEBOX",
  "WS_POPUP | WS_CAPTION | WS_SYSMENU |\
 WS_HSCROLL | WS_VSCROLL",
  "WS_OVERLAPPPED | WS_CAPTION | WS_SYSMENU |\
 WS_HSCROLL | WS_VSCROLL"
};

char szNameWnd[128];

/////////////////////////////////////////////////////////////////////////////
// CChildWnd

CChildWnd::CChildWnd()
{
}

CChildWnd::~CChildWnd()
{
}

BEGIN_MESSAGE_MAP(CChildWnd, CWnd)
	//{{AFX_MSG_MAP(CChildWnd)
	ON_WM_CREATE()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CChildWnd message handlers

BOOL CChildWnd::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style |= adwStyles[nCount];

 sprintf(szNameWnd, "Окно %d", nCount);
 cs.lpszName = szNameWnd;
 
 return CWnd::PreCreateWindow(cs);
}

int CChildWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
 MoveWindow(nCount++*90, 24, 88, 86);
	
 return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CPopupWnd

CPopupWnd::CPopupWnd()
{
}

CPopupWnd::~CPopupWnd()
{
// DestroyWindow();
}

BEGIN_MESSAGE_MAP(CPopupWnd, CFrameWnd)
	//{{AFX_MSG_MAP(CPopupWnd)
	ON_WM_CREATE()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPopupWnd message handlers

BOOL CPopupWnd::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style = adwStyles[nCount];

	return CFrameWnd::PreCreateWindow(cs);
}

int CPopupWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
    
	ModifyStyle((DWORD)-1, adwStyles[nCount]);
	
	int n = nCount++ -5;
	MoveWindow(n*90, 24, 88, 86);
	
	return 0;
}


void CChildWnd::OnLButtonUp(UINT nFlags, CPoint point) 
{
 WORD nWnd = (WORD)::GetWindowLong(this->GetSafeHwnd(),
                                   GWL_USERDATA);
 sprintf(szNameWnd, "Дочернее окно: %d", nWnd);
 MessageBox(aszStyles[nWnd], szNameWnd);
	
	CWnd::OnLButtonUp(nFlags, point);
}

void CPopupWnd::OnLButtonUp(UINT nFlags, CPoint point) 
{
	WORD nWnd = (WORD)::GetWindowLong(this->GetSafeHwnd(),
                                   GWL_USERDATA);
 sprintf(szNameWnd, "Всплывающее окно: %d", nWnd);
 MessageBox(aszStyles[nWnd + 5], szNameWnd);
	
	CFrameWnd::OnLButtonUp(nFlags, point);
}
