/////////////////////////////////////////////////////////////
// Файл MainFrm.cpp
// Copyright (c) 1999 Мешков А., Тихомиров Ю.
/////////////////////////////////////////////////////////////

// implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Styles.h"

#include "MainFrm.h"

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_GETMINMAXINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

extern char szNameWnd[128];

CMainFrame::CMainFrame()
{
 for(int i = 0; i < 5; i++)
 {
  apChildWnd[i] = NULL;
  apPopupWnd[i] = NULL;
 }

}

CMainFrame::~CMainFrame()
{
 
 for(int i = 0; i < 5; i++)
 {
  if(apChildWnd[i] != NULL)
   delete apChildWnd[i];
 }
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
 cs.lpszName = "Главное окно приложения \"Стили\"";

	return CFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
 int i;
	for(i = 0; i < 5; i++)
 {
  apChildWnd[i] = new CChildWnd;
  apChildWnd[i]->Create(NULL,
                        NULL,
                        WS_VISIBLE,
                        CRect(0, 0, 0, 0),
                        this,
                        (WORD)i);
  ::SetWindowLong(apChildWnd[i]->GetSafeHwnd(),
                  GWL_USERDATA,
                  i);
 }

 for(i = 0; i < 4; i++)
 {
  apPopupWnd[i] = new CPopupWnd;
  apPopupWnd[i]->Create(NULL,
                        NULL,
                        0,
                        rectDefault,
                        this);
  ::SetWindowLong(apPopupWnd[i]->GetSafeHwnd(),
                  GWL_USERDATA,
                  i);
  sprintf(szNameWnd, "Окно %d", i);
  apPopupWnd[i]->SetWindowText(szNameWnd);
 }

 apPopupWnd[4] = new CPopupWnd;
 apPopupWnd[4]->Create(NULL,
                       NULL,
                       0,
                       rectDefault);

 ::SetWindowLong(apPopupWnd[4]->GetSafeHwnd(),
                 GWL_USERDATA,
                 4);
 sprintf(szNameWnd, "Окно 4");
 apPopupWnd[i]->SetWindowText(szNameWnd);
	
 ::SetClassLong(apChildWnd[0]->GetSafeHwnd(),
                GCL_HCURSOR,
                (LONG)AfxGetApp()->LoadStandardCursor(IDC_IBEAM));

 ::SetClassLong(apPopupWnd[0]->GetSafeHwnd(),
                GCL_HCURSOR,
                (LONG)AfxGetApp()->LoadStandardCursor(IDC_UPARROW));

 HBRUSH hNewBrush = ::CreateSolidBrush(RGB(255, 255, 220));
 ::SetClassLong(apPopupWnd[3]->GetSafeHwnd(),
                GCL_HBRBACKGROUND,
                (LONG)hNewBrush);

 for(i = 0; i < 5; i++)
 {
  apPopupWnd[i]->ShowWindow(SW_SHOWNORMAL);
  apPopupWnd[i]->UpdateWindow();
 }

 return 0;
}

void CMainFrame::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{

 int cx = ::GetSystemMetrics(SM_CXSCREEN)/8;
 int cy = ::GetSystemMetrics(SM_CYSCREEN)/4;

 lpMMI->ptMinTrackSize.x = 6*cx;
 lpMMI->ptMinTrackSize.y = 2*cy;
 lpMMI->ptMaxTrackSize.x = 6*cx;
 lpMMI->ptMaxTrackSize.y = 2*cy;
 lpMMI->ptMaxPosition.x  = cx;
 lpMMI->ptMaxPosition.y  = cy;
 
 CFrameWnd::OnGetMinMaxInfo(lpMMI);
}
