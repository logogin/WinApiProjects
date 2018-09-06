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
	// получаем доступ к документу
	CDynMenuDoc* pDoc = (CDynMenuDoc*)GetActiveDocument();
	ASSERT_KINDOF(CDynMenuDoc, pDoc);

  // Создаем два указателя на класс CMenu для доступа к меню верхнего
  // уровня pTopMenu и динамического меню цветов
  CMenu* pColorMenu = NULL;
	CMenu* pTopMenu = AfxGetMainWnd()->GetMenu();
	int iPos;
	// ищем элемент меню Add Color по идентификатору ID_ADD_COLOR
  for (iPos = pTopMenu->GetMenuItemCount()-1; iPos >= 0; iPos--)
	{
    // Получаем указатель на элемент меню верхнего уровня		
    CMenu* pMenu = pTopMenu->GetSubMenu(iPos);
		if (pMenu && pMenu->GetMenuItemID(0) == ID_ADD_COLOR)
		{
      // если элемент "Цвет", то прекращаем поиск
			pColorMenu = pMenu;
			break;
		}
	}
  // поиск должен закончиться успешно, иначе ошибка
	ASSERT(pColorMenu != NULL);

  // Обновляем состав подменю "Список цветов" 
  
  // Сначала удаляем все элементы подменю ...
	for (iPos = pColorMenu->GetMenuItemCount()-3; iPos > 0; iPos--)
		pColorMenu->DeleteMenu(iPos, MF_BYPOSITION);
  m_PopupMenu.m_hMenu = NULL;
	
  // затем вставляем все выбранные цвета и полосу разделителя
	if(pDoc->m_icolor != -1)
  {
    // создаем выпадающее меню
    m_PopupMenu.CreatePopupMenu();

    // и вставляем его между разделителем и элементом
    // "Удалить все цвета"
    pColorMenu->InsertMenu(ID_DELETE_ALL,
                           MF_STRING | MF_POPUP | MF_BYCOMMAND,
			                     (UINT)m_PopupMenu.m_hMenu, "Список цветов");
  }

  // вставляем элементы выпадающего меню  
  for (int i = 0; i < NUM_COLOR; i++)
	{
    if (pDoc->m_aColor[i].m_btr == TRUE)
		{
			TCHAR strColor[64];
      sprintf(strColor, "Цвет %d", i);
			m_PopupMenu.AppendMenu(MF_STRING,
				                     pDoc->m_aColor[i].m_nID, strColor);
    }
	}
  // вставляем разделитель
  if(pDoc->m_icolor != -1)
    pColorMenu->InsertMenu(ID_DELETE_ALL,
                           MF_BYCOMMAND | MF_SEPARATOR);

}

void CMainFrame::OnDeleteAll() 
{
  // получаем доступ к документу	
  CDynMenuDoc* pDoc = (CDynMenuDoc*)GetActiveDocument();
	ASSERT_KINDOF(CDynMenuDoc, pDoc);

  // сбрасываем флаг активности элемента
	for (int i = 0; i < NUM_COLOR; i++)
  {
    pDoc->m_aColor[i].m_btr = FALSE;
  }
  // определяем, что нет доступного текущего цвета
  pDoc->m_icolor = -1;
  // обновляем содержимое меню
  ChangeColorMenu();
  // обновляем изображение в окне документа  
  pDoc->UpdateAllViews(NULL);
}

void CMainFrame::ActivateFrame(int nCmdShow) 
{
  // загружаем битовые массивы  
  m_bmpCheck.LoadBitmap(IDB_MENU_DOWN);
  m_bmpUnCheck.LoadBitmap(IDB_MENU_UP);

  // получаем системные размеры маркера
  int cx = ::GetSystemMetrics(SM_CXMENUCHECK);
  int cy = ::GetSystemMetrics(SM_CYMENUCHECK);
  
  // приводим текущие размеры битовых массивов к системным
  m_bmpUnCheck.SetBitmapDimension(cx, cy);
  m_bmpCheck.SetBitmapDimension(cx, cy);

  CMenu *pViewMenu = NULL;
  CMenu *pTopMenu = AfxGetMainWnd()->GetMenu();
	int iPos;
	// ищем элемент меню Add Color по идентификатору ID_ADD_COLOR
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
  
  // устанавливаем новые маркеры для отмеченного и
  // не отмеченного состояний  
  pViewMenu->SetMenuItemBitmaps(ID_VIEW_TOOLBAR, MF_BYCOMMAND,
                                &m_bmpUnCheck, &m_bmpCheck);
  pViewMenu->SetMenuItemBitmaps(ID_VIEW_STATUS_BAR, MF_BYCOMMAND,
                                &m_bmpUnCheck, &m_bmpCheck);

// добавляем элемент "Разблокировать меню Цвет" в системное меню

// IDM_COLOR должен находиться в границах системных команд
  ASSERT((IDM_COLOR & 0xFFF0) == IDM_COLOR);
	ASSERT(IDM_COLOR < 0xF000);

  // получаем доступ к системному меню
  CMenu* pSysMenu = GetSystemMenu(FALSE);
	CString strColorMenu(" Разблокировать меню Цвет");

  // добавляем в него разделитель и новый элемент
  // "Разблокировать меню Цвет"
	pSysMenu->AppendMenu(MF_SEPARATOR);
	pSysMenu->AppendMenu(MF_BYCOMMAND | MF_STRING,
                       IDM_COLOR, strColorMenu);

  // сбрасываем метку, показывая, что элемент "Цвет"
  // меню верхнего уровня заблокирован
  pSysMenu->CheckMenuItem(IDM_COLOR, MF_BYCOMMAND | MF_UNCHECKED);
  
	// ищем элемент меню Add Color по идентификатору ID_ADD_COLOR
  for (iPos = pTopMenu->GetMenuItemCount()-1; iPos >= 0; iPos--)
	{
	  CMenu* pMenu = pTopMenu->GetSubMenu(iPos);
	  if (pMenu && pMenu->GetMenuItemID(0) == ID_ADD_COLOR)
		{
		  break;
		}
	}
  
  // разблокируем элемент "Цвет" в полосе меню
  pTopMenu->EnableMenuItem(iPos,
                           MF_BYPOSITION | MF_GRAYED);
  // перерисовываем полосу меню  
  DrawMenuBar();

  // передаем управление фрейму	
  CFrameWnd::ActivateFrame(nCmdShow);
}

// поскольку команда не зарегистрирована,
// необходимо переопределить обработчик
void CMainFrame::OnSysCommand( UINT nID, LPARAM lParam )
{
	if ((nID & 0xFFF0) == IDM_COLOR)
	{
    CMenu* pColorMenu = NULL;
	  CMenu* pTopMenu = AfxGetMainWnd()->GetMenu();
	  int iPos;
	  // ищем элемент меню Add Color по идентификатору ID_ADD_COLOR
    for (iPos = pTopMenu->GetMenuItemCount()-1; iPos >= 0; iPos--)
	  {
		  CMenu* pMenu = pTopMenu->GetSubMenu(iPos);
		  if (pMenu && pMenu->GetMenuItemID(0) == ID_ADD_COLOR)
		  {
			  break;
		  }
	  }

    // получаем доступ к системному меню
    CMenu *pSysMenu = GetSystemMenu(FALSE);
    // определяем текущее состояние элемента
    UINT nState = pSysMenu->GetMenuState(IDM_COLOR, MF_BYCOMMAND);
    // если элемент отмечен, то сбрасываем и запрещаем
    // доступ к элементу "Цвет" полосы меню, и наоборот
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
    // перерисовываем полосу меню
    DrawMenuBar();
  }
	else
	{
    // если не наша команда,
    // необходимо передать ее для корректной обработки
		CWnd::OnSysCommand(nID, lParam);
	}
}

