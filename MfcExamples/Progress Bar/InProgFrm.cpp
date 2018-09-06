// InProgFrm.cpp : implementation file
//

#include "stdafx.h"
#include "InProg.h"
#include "InProgFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ID_PULSE	1
#define ID_INPROG	2

static UINT BASED_CODE indicators[] =
{
	ID_SEPARATOR,           // status line indicator
  ID_INDICATOR_NUM,
  ID_INDICATOR_CAPS,
  ID_INDICATOR_OVR
};

/////////////////////////////////////////////////////////////////////////////
// CInProgFrame

CInProgFrame::CInProgFrame()
{
}

CInProgFrame::~CInProgFrame()
{
}


BEGIN_MESSAGE_MAP(CInProgFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CInProgFrame)
	ON_WM_CREATE()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// перегружаем функцию PreCreateWindow для задания своего класса окна,
// задавая иной фон и отказываясь от стилей CS_VREDRAW/CS_HREDRAW,
// чтобы исключить перерисовку контрольных панелей при изменении
// размеров главного окна
BOOL CInProgFrame::PreCreateWindow(CREATESTRUCT& cs)
{
  cs.lpszClass = AfxRegisterWndClass(CS_DBLCLKS,
    AfxGetApp()->LoadStandardCursor(IDC_ARROW), (HBRUSH)(COLOR_WINDOW+1),
    AfxGetApp()->LoadIcon(IDR_INPROG));

  return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CInProgFrame message handlers

int CInProgFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

  if (!m_wndStatusBar.Create(this) ||
      !m_wndStatusBar.SetIndicators(indicators,
      sizeof(indicators)/sizeof(UINT)))
  {
    TRACE0("Ошибка при создании панели \n");
    return FALSE;       
  }

	ShowControlBar(&m_wndStatusBar, FALSE, FALSE);
	
  if (!m_wndDlgBar.Create(this, IDD_PROGRESS,
    CBRS_BOTTOM, IDD_PROGRESS))
  {
    TRACE0("Ошибка при создании панели \n");
    return -1; 
  }

  // разрешаем привязку панели инструментов
  EnableDocking(CBRS_ALIGN_BOTTOM);

	CProgressCtrl *pProgress = 
	  (CProgressCtrl *)m_wndDlgBar.GetDlgItem(IDC_PROGRESS);

	pProgress->SetRange(0, 1000);
	pProgress->SetPos(0);
	pProgress->SetStep(10);

	SetTimer(ID_PULSE, 10000, NULL);
	SetTimer(ID_INPROG,  100, NULL);
	
	return 0;
}

void CInProgFrame::OnTimer(UINT nIDEvent) 
{
	static int nCheck = 1;

	CProgressCtrl *pProgress = 
	  (CProgressCtrl *)m_wndDlgBar.GetDlgItem(IDC_PROGRESS);

	if (nIDEvent == ID_PULSE)
	{
		if (nCheck = !nCheck)
		{
			pProgress->SetRange(0, 1000);
			pProgress->SetPos(0);
			pProgress->SetStep(10);

			ShowControlBar(&m_wndStatusBar, FALSE, FALSE);
			ShowControlBar(&m_wndDlgBar, TRUE, FALSE);
		}
		else
		{
			ShowControlBar(&m_wndDlgBar, FALSE, FALSE);
			ShowControlBar(&m_wndStatusBar, TRUE, FALSE);
		}
	}
	else if (nIDEvent == ID_INPROG && nCheck)
		pProgress->StepIt();

	CFrameWnd::OnTimer(nIDEvent);
}

