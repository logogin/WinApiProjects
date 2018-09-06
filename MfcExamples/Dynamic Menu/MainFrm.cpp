// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "DynMenu.h"

#include "MainFrm.h"
#include "DynMenuDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_SYSCOMMAND()
  ON_WM_CREATE()
	ON_COMMAND(ID_DELETE_ALL, OnDeleteAll)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
	
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	return CFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::ChangeColorMenu()
{
	// �������� ������ � ���������
	CDynMenuDoc* pDoc = (CDynMenuDoc*)GetActiveDocument();
	ASSERT_KINDOF(CDynMenuDoc, pDoc);

  // ������� ��� ��������� �� ����� CMenu ��� ������� � ���� ��������
  // ������ pTopMenu � ������������� ���� ������
  CMenu* pColorMenu = NULL;
	CMenu* pTopMenu = AfxGetMainWnd()->GetMenu();
	int iPos;
	// ���� ������� ���� Add Color �� �������������� ID_ADD_COLOR
  for (iPos = pTopMenu->GetMenuItemCount()-1; iPos >= 0; iPos--)
	{
    // �������� ��������� �� ������� ���� �������� ������		
    CMenu* pMenu = pTopMenu->GetSubMenu(iPos);
		if (pMenu && pMenu->GetMenuItemID(0) == ID_ADD_COLOR)
		{
      // ���� ������� "����", �� ���������� �����
			pColorMenu = pMenu;
			break;
		}
	}
  // ����� ������ ����������� �������, ����� ������
	ASSERT(pColorMenu != NULL);

  // ��������� ������ ������� "������ ������" 
  
  // ������� ������� ��� �������� ������� ...
	for (iPos = pColorMenu->GetMenuItemCount()-3; iPos > 0; iPos--)
		pColorMenu->DeleteMenu(iPos, MF_BYPOSITION);
  m_PopupMenu.m_hMenu = NULL;
	
  // ����� ��������� ��� ��������� ����� � ������ �����������
	if(pDoc->m_icolor != -1)
  {
    // ������� ���������� ����
    m_PopupMenu.CreatePopupMenu();

    // � ��������� ��� ����� ������������ � ���������
    // "������� ��� �����"
    pColorMenu->InsertMenu(ID_DELETE_ALL,
                           MF_STRING | MF_POPUP | MF_BYCOMMAND,
			                     (UINT)m_PopupMenu.m_hMenu, "������ ������");
  }

  // ��������� �������� ����������� ����  
  for (int i = 0; i < NUM_COLOR; i++)
	{
    if (pDoc->m_aColor[i].m_btr == TRUE)
		{
			TCHAR strColor[64];
      sprintf(strColor, "���� %d", i);
			m_PopupMenu.AppendMenu(MF_STRING,
				                     pDoc->m_aColor[i].m_nID, strColor);
    }
	}
  // ��������� �����������
  if(pDoc->m_icolor != -1)
    pColorMenu->InsertMenu(ID_DELETE_ALL,
                           MF_BYCOMMAND | MF_SEPARATOR);

}

void CMainFrame::OnDeleteAll() 
{
  // �������� ������ � ���������	
  CDynMenuDoc* pDoc = (CDynMenuDoc*)GetActiveDocument();
	ASSERT_KINDOF(CDynMenuDoc, pDoc);

  // ���������� ���� ���������� ��������
	for (int i = 0; i < NUM_COLOR; i++)
  {
    pDoc->m_aColor[i].m_btr = FALSE;
  }
  // ����������, ��� ��� ���������� �������� �����
  pDoc->m_icolor = -1;
  // ��������� ���������� ����
  ChangeColorMenu();
  // ��������� ����������� � ���� ���������  
  pDoc->UpdateAllViews(NULL);
}

void CMainFrame::ActivateFrame(int nCmdShow) 
{
  // ��������� ������� �������  
  m_bmpCheck.LoadBitmap(IDB_MENU_DOWN);
  m_bmpUnCheck.LoadBitmap(IDB_MENU_UP);

  // �������� ��������� ������� �������
  int cx = ::GetSystemMetrics(SM_CXMENUCHECK);
  int cy = ::GetSystemMetrics(SM_CYMENUCHECK);
  
  // �������� ������� ������� ������� �������� � ���������
  m_bmpUnCheck.SetBitmapDimension(cx, cy);
  m_bmpCheck.SetBitmapDimension(cx, cy);

  CMenu *pViewMenu = NULL;
  CMenu *pTopMenu = AfxGetMainWnd()->GetMenu();
	int iPos;
	// ���� ������� ���� Add Color �� �������������� ID_ADD_COLOR
  for (iPos = pTopMenu->GetMenuItemCount()-1; iPos >= 0; iPos--)
	{
		CMenu* pMenu = pTopMenu->GetSubMenu(iPos);
		if (pMenu && pMenu->GetMenuItemID(0) == ID_VIEW_TOOLBAR)
		{
			pViewMenu = pMenu;
			break;
		}
	}
	ASSERT(pViewMenu != NULL);
  
  // ������������� ����� ������� ��� ����������� �
  // �� ����������� ���������  
  pViewMenu->SetMenuItemBitmaps(ID_VIEW_TOOLBAR, MF_BYCOMMAND,
                                &m_bmpUnCheck, &m_bmpCheck);
  pViewMenu->SetMenuItemBitmaps(ID_VIEW_STATUS_BAR, MF_BYCOMMAND,
                                &m_bmpUnCheck, &m_bmpCheck);

// ��������� ������� "�������������� ���� ����" � ��������� ����

// IDM_COLOR ������ ���������� � �������� ��������� ������
  ASSERT((IDM_COLOR & 0xFFF0) == IDM_COLOR);
	ASSERT(IDM_COLOR < 0xF000);

  // �������� ������ � ���������� ����
  CMenu* pSysMenu = GetSystemMenu(FALSE);
	CString strColorMenu(" �������������� ���� ����");

  // ��������� � ���� ����������� � ����� �������
  // "�������������� ���� ����"
	pSysMenu->AppendMenu(MF_SEPARATOR);
	pSysMenu->AppendMenu(MF_BYCOMMAND | MF_STRING,
                       IDM_COLOR, strColorMenu);

  // ���������� �����, ���������, ��� ������� "����"
  // ���� �������� ������ ������������
  pSysMenu->CheckMenuItem(IDM_COLOR, MF_BYCOMMAND | MF_UNCHECKED);
  
	// ���� ������� ���� Add Color �� �������������� ID_ADD_COLOR
  for (iPos = pTopMenu->GetMenuItemCount()-1; iPos >= 0; iPos--)
	{
	  CMenu* pMenu = pTopMenu->GetSubMenu(iPos);
	  if (pMenu && pMenu->GetMenuItemID(0) == ID_ADD_COLOR)
		{
		  break;
		}
	}
  
  // ������������ ������� "����" � ������ ����
  pTopMenu->EnableMenuItem(iPos,
                           MF_BYPOSITION | MF_GRAYED);
  // �������������� ������ ����  
  DrawMenuBar();

  // �������� ���������� ������	
  CFrameWnd::ActivateFrame(nCmdShow);
}

// ��������� ������� �� ����������������,
// ���������� �������������� ����������
void CMainFrame::OnSysCommand( UINT nID, LPARAM lParam )
{
	if ((nID & 0xFFF0) == IDM_COLOR)
	{
    CMenu* pColorMenu = NULL;
	  CMenu* pTopMenu = AfxGetMainWnd()->GetMenu();
	  int iPos;
	  // ���� ������� ���� Add Color �� �������������� ID_ADD_COLOR
    for (iPos = pTopMenu->GetMenuItemCount()-1; iPos >= 0; iPos--)
	  {
		  CMenu* pMenu = pTopMenu->GetSubMenu(iPos);
		  if (pMenu && pMenu->GetMenuItemID(0) == ID_ADD_COLOR)
		  {
			  break;
		  }
	  }

    // �������� ������ � ���������� ����
    CMenu *pSysMenu = GetSystemMenu(FALSE);
    // ���������� ������� ��������� ��������
    UINT nState = pSysMenu->GetMenuState(IDM_COLOR, MF_BYCOMMAND);
    // ���� ������� �������, �� ���������� � ���������
    // ������ � �������� "����" ������ ����, � ��������
    if(nState == MF_CHECKED)
    {
      pSysMenu->CheckMenuItem(IDM_COLOR, MF_BYCOMMAND | MF_UNCHECKED);
      pTopMenu->EnableMenuItem(iPos,
                               MF_BYPOSITION | MF_GRAYED);
    }
    else
    {
      pSysMenu->CheckMenuItem(IDM_COLOR, MF_BYCOMMAND | MF_CHECKED);
      pTopMenu->EnableMenuItem(iPos,
                               MF_BYPOSITION | MF_ENABLED);
    }
    // �������������� ������ ����
    DrawMenuBar();
  }
	else
	{
    // ���� �� ���� �������,
    // ���������� �������� �� ��� ���������� ���������
		CWnd::OnSysCommand(nID, lParam);
	}
}

