//////////////////////////////////////////////////////////////
// Модуль MainFrm.cpp
// Copyright (c) 1999 Мешков А., Тихомиров Ю.
//////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CtrlBars.h"

#include "MainFrm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

// связываем функции с командами и сообщениями
BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
  //{{AFX_MSG_MAP(CMainFrame)
  ON_WM_CREATE()
  ON_COMMAND(IDM_VIEWPANE, OnViewPane)
  ON_UPDATE_COMMAND_UI(IDM_VIEWPANE, OnUpdateViewPane)
  ON_CBN_SELCHANGE(IDC_PANE, OnSelChangePane)
  ON_COMMAND(IDM_PANE_2COLUMN, OnPane2column)
  ON_COMMAND(IDM_PANE_3COLUMN, OnPane3column)
  ON_UPDATE_COMMAND_UI(IDM_PANE_3COLUMN, OnUpdatePane3column)
  ON_UPDATE_COMMAND_UI(IDM_PANE_2COLUMN, OnUpdatePane2column)
  ON_UPDATE_COMMAND_UI(ID_INDICATOR_IDLE, OnUpdateIndicatorIdle)
  ON_WM_TIMER()
  //}}AFX_MSG_MAP
  ON_COMMAND_RANGE(ID_STYLE_LEFT, ID_STYLE_JUSTIFIED, OnStyle)
  ON_UPDATE_COMMAND_UI_RANGE(ID_STYLE_LEFT, ID_STYLE_JUSTIFIED, OnUpdateStyle)
  ON_COMMAND_RANGE(ID_PANEERASE, ID_PANEOVAL, OnPane)
  ON_UPDATE_COMMAND_UI_RANGE(ID_PANEERASE, ID_PANEOVAL, OnUpdatePane)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// массивы идентификаторов для инициализации контрольных панелей

static UINT BASED_CODE toolbar[] =
{
  // тот же порядок, что и в файле 'toolbar.bmp'
  ID_FILE_NEW, 
  ID_FILE_OPEN, 
  ID_FILE_SAVE, 
    ID_SEPARATOR,
  ID_EDIT_CUT, 
  ID_EDIT_COPY, 
  ID_EDIT_PASTE, 
    ID_SEPARATOR,
  ID_SEPARATOR,           // резервируем для combo box
    ID_SEPARATOR,
  ID_FILE_PRINT, 
  ID_APP_ABOUT,
  ID_CONTEXT_HELP
};

static UINT BASED_CODE pane[] =
{
  // тот же порядок, что и в файле 'pane.bmp'
  ID_PANEERASE,
  ID_PANEPEN,
  ID_PANESELECT,
  ID_PANEBRUSH,
  ID_PANESPRAY,
  ID_PANEPAINT,
  ID_PANELINE,
  ID_PANEEYEDROP,
  ID_PANEMAG,
  ID_PANERECT,
  ID_PANEROUND,
  ID_PANEOVAL
};

static UINT BASED_CODE indicators[] =
{
  ID_SEPARATOR,           // индикатор выбираемой команды
  ID_INDICATOR_NUM,
  ID_INDICATOR_IDLE,	
  ID_INDICATOR_TIME
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

CMainFrame::CMainFrame()
{
  m_nPaneCol = 3;
}

CMainFrame::~CMainFrame()
{
}

// перегружаем функцию PreCreateWindow для задания своего класса окна,
// задавая иной фон и отказываясь от стилей CS_VREDRAW/CS_HREDRAW,
// чтобы исключить перерисовку контрольных панелей при изменении
// размеров главного окна
BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
  cs.lpszClass = AfxRegisterWndClass(CS_DBLCLKS,
    AfxGetApp()->LoadStandardCursor(IDC_ARROW), (HBRUSH)(COLOR_WINDOW+1),
    AfxGetApp()->LoadIcon(IDR_MAINFRAME));

  return TRUE;
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
  if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
    return -1;

  if (!CreateToolBar())
    return -1;
  if (!CreatePaneBar())
    return -1;
  if (!CreateStatusBar())
    return -1;

  if (!m_wndDlgBar.Create(this, IDD_VIEWSELECT,
    CBRS_LEFT|CBRS_TOOLTIPS|CBRS_FLYBY, IDD_VIEWSELECT))
  {
    TRACE0("Ошибка при создании панели \n");
    return -1; 
  }

  // разрешаем привязку панели инструментов
  EnableDocking(CBRS_ALIGN_ANY);

  m_wndPaneBar.EnableDocking(CBRS_ALIGN_ANY);
  DockControlBar(&m_wndPaneBar, AFX_IDW_DOCKBAR_TOP);

  // размещаем панель инструментов в задаваемом месте экрана
  CPoint pt(::GetSystemMetrics(SM_CXSCREEN) - 200,
    ::GetSystemMetrics(SM_CYSCREEN) / 3);

  FloatControlBar(&m_wndPaneBar, pt);

  // создаем таймер для смены содержимого области строки состояния
  SetTimer(0, 1000, NULL);

  return 0;
}

// разбивка панели на столбцы - находим
// конечные кнопки каждой строки
void CMainFrame::SetColumns(UINT nColumns)
{
  int nCount = m_wndPaneBar.GetToolBarCtrl().GetButtonCount();

  for (int i = 0; i < nCount; i++)
  {
    UINT nStyle = m_wndPaneBar.GetButtonStyle(i);
    BOOL bWrap = (((i + 1) % nColumns) == 0);
    if (bWrap)
      nStyle |= TBBS_WRAPPED;
    else
      nStyle &= ~TBBS_WRAPPED;
    m_wndPaneBar.SetButtonStyle(i, nStyle);
  }
  
  m_wndPaneBar.Invalidate();
  m_wndPaneBar.GetParentFrame()->RecalcLayout();
}

BOOL CMainFrame::CreateToolBar()
{
  const int nDropHeight = 100;

  // вставлять комбинированный список легче, если панель инструментов 
  // или любой другой элемент управления формируется на основе 
  // массива команд, когда место для элемента заранее зарезервировано
  if (!m_wndToolBar.Create(this, WS_CHILD|WS_VISIBLE|CBRS_TOP|
      CBRS_TOOLTIPS|CBRS_FLYBY) ||
    !m_wndToolBar.LoadBitmap(IDB_TOOLBAR) ||
    !m_wndToolBar.SetButtons(toolbar, sizeof(toolbar)/sizeof(UINT)))
  {
    TRACE0("Ошибка при создании панели\n");
    return FALSE;       // fail to create
  }

  //
  // создание комбинированного списка
  //

  // задаем ширину для списка и связываем его 
  // идентификатор с местом в панели
  m_wndToolBar.SetButtonInfo(8, IDW_COMBO, TBBS_SEPARATOR, 100);

  // Microsoft требует (и не следует сама!), чтобы расстояние между
  // списками и кнопками было 12 пикселей в ширину
  m_wndToolBar.SetButtonInfo(7, ID_SEPARATOR, TBBS_SEPARATOR, 12);
  m_wndToolBar.SetButtonInfo(9, ID_SEPARATOR, TBBS_SEPARATOR, 12);

  CRect rect;
  m_wndToolBar.GetItemRect(8, &rect);
  rect.top = 2;
  rect.bottom = rect.top + nDropHeight;
  if (!m_comboBox.Create(CBS_NOINTEGRALHEIGHT|
      CBS_DROPDOWNLIST|WS_VISIBLE|WS_TABSTOP,
      rect, &m_wndToolBar, IDW_COMBO))
  {
    TRACE0("Ошибка при создании комбинированного списка\n");
    return FALSE;
  }

  m_comboBox.AddString(_T("Влево"));
  m_comboBox.AddString(_T("По ценру"));
  m_comboBox.AddString(_T("Вправо"));
  m_comboBox.AddString(_T("По ширине"));

  // Про работу со шрифтами тоже говорить будем не скоро
  // пока поверьте на слово
  LOGFONT logFont;
  memset(&logFont, 0, sizeof(logFont));

  if (!::GetSystemMetrics(SM_DBCSENABLED))
  {
    logFont.lfHeight = -12;
    logFont.lfWeight = FW_BOLD;
    logFont.lfPitchAndFamily = VARIABLE_PITCH | FF_SWISS;
    lstrcpy(logFont.lfFaceName, _T("MS Sans Serif"));
    if (!m_font.CreateFontIndirect(&logFont))
      TRACE0("Не возможно создание шрифта для списка\n");
    else
      m_comboBox.SetFont(&m_font);
  }
  else
  {
    m_font.Attach(::GetStockObject(SYSTEM_FONT));
    m_comboBox.SetFont(&m_font);
  }
  
  return TRUE;
}

BOOL CMainFrame::CreatePaneBar()
{
  if (!m_wndPaneBar.Create(this, WS_CHILD | WS_VISIBLE | CBRS_SIZE_FIXED |
    CBRS_TOP | CBRS_TOOLTIPS, ID_PANEBAR) ||
    !m_wndPaneBar.LoadBitmap(IDB_PANE) ||
    !m_wndPaneBar.SetButtons(pane,
      sizeof(pane)/sizeof(UINT)))
  {
    TRACE0("Ошибка при создании панели\n");
    return FALSE;     
  }

  //
  // добавляем к изображениям на кнопках текстовые строки 
  //

  // узнаем и запоминаем размер изображений
  CRect imageRect;
  m_wndPaneBar.GetItemRect(0, &imageRect);

  // добавляем по строке на каждую кнопку,
  // если строк будет меньше - все оставшиеся кнопки
  // будут осчастливлены ПЕРВОЙ ЗАДАННОЙ СТРОКОЙ !!!
  for (int index = ID_PANEERASE; index <= ID_PANEOVAL; index++)
  {
    CString szPane;  
    szPane.LoadString(index);
    
    // строки хранятся в следующем виде:
    //   - сообщение для строки состояния о возможном выборе,
    //   - символ '\n',
    //   - краткое наименование для всплывающих подсказок.
    // именно последнее мы и используем
    m_wndPaneBar.SetButtonText(index - ID_PANEERASE, 
      szPane.Mid(szPane.Find('\n')+1));
  }

  // после каждой вставки текста автоматически происходило изменение размеров,
  // но об этом знает Windows, объект класса CToolBar об этом знать не знает - 
  // сообщим ему об этом, помятуя, что размер изображений остался без изменений
  // константы 7 и 6 - требования Microsoft 
  CRect buttonRect;
  m_wndPaneBar.GetItemRect(0, &buttonRect);
  m_wndPaneBar.SetSizes(CSize(buttonRect.Width() + 2, buttonRect.Height() + 2),
    CSize(imageRect.Width()-7, imageRect.Height()-6));

  // заголовок для будущего окна, если панель будет в плавающем режиме 
  // (будет-будет)
  m_wndPaneBar.SetWindowText(_T("Инструменты"));

  // сразу настраиваем кол-во столбцов
  SetColumns(m_nPaneCol);
  
  return TRUE;
}

BOOL CMainFrame::CreateStatusBar()
{
  if (!m_wndStatusBar.Create(this) ||
    !m_wndStatusBar.SetIndicators(indicators,
      sizeof(indicators)/sizeof(UINT)))
  {
    TRACE0("Ошибка при создании панели \n");
    return FALSE;       
  }

  return TRUE;
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
// Обработчики сообщений класса CMainFrame

// управление отображением панели инструментов рисования
void CMainFrame::OnViewPane()
{
  BOOL bVisible = ((m_wndPaneBar.GetStyle() & WS_VISIBLE) != 0);

  ShowControlBar(&m_wndPaneBar, !bVisible, FALSE);
  RecalcLayout();
}

void CMainFrame::OnUpdateViewPane(CCmdUI* pCmdUI)
{
  BOOL bVisible = ((m_wndPaneBar.GetStyle() & WS_VISIBLE) != 0);
  pCmdUI->SetCheck(bVisible);
}

// обработчик изменения выбора инструмента рисования
void CMainFrame::OnSelChangePane()
{
  CString strText;
  CString strItem;
  CComboBox* pCBox = (CComboBox*)m_wndDlgBar.GetDlgItem(IDC_PANE);
  int nIndex = pCBox->GetCurSel();
  if (nIndex == CB_ERR)
    return;
  pCBox->GetLBText(nIndex, strItem);
  AfxFormatString1(strText, IDS_SELECTED_PROMPT, (LPCTSTR)strItem);
  SetMessageText(strText);
}

// обработчики команд смены количества
// столбцов панели инструментов рисования
void CMainFrame::OnPane2column()
{
  SetColumns(m_nPaneCol = 2);
}

void CMainFrame::OnPane3column()
{
  SetColumns(m_nPaneCol = 3);
}

void CMainFrame::OnUpdatePane2column(CCmdUI* pCmdUI)
{
  pCmdUI->SetCheck(m_nPaneCol == 2);
}

void CMainFrame::OnUpdatePane3column(CCmdUI* pCmdUI)
{
  pCmdUI->SetCheck(m_nPaneCol == 3);
}

// каждый раз меняем символ в области строки состояния,
// кстати эта функция при отсутствии каких либо действий
// вызывается примерно раз в секунду, а при манипуляциях с мышью
// практически постоянно
void CMainFrame::OnUpdateIndicatorIdle(CCmdUI* pCmdUI)
{
  static BOOL bIdle = FALSE;
  pCmdUI->SetText(bIdle ? " " : "\x95");
  bIdle = !bIdle;
}

// обработчик таймера
void CMainFrame::OnTimer(UINT nIDEvent) 
{
  m_wndStatusBar.SetPaneText(m_wndStatusBar.CommandToIndex(ID_INDICATOR_TIME),
    CTime::GetCurrentTime().Format("%H:%M:%S"));
  
  CFrameWnd::OnTimer(nIDEvent);
}

// обработчик смены выбора стилей выравнивания
void CMainFrame::OnStyle(UINT nID)
{
  m_comboBox.SetCurSel((int)(nID-ID_STYLE_LEFT));
}

void CMainFrame::OnUpdateStyle(CCmdUI* pCmdUI)
{
  UINT nIndex = m_comboBox.GetCurSel();
  pCmdUI->SetCheck((UINT)(ID_STYLE_LEFT+nIndex) == pCmdUI->m_nID);
}

// обработчик смены выбора инструментов рисования
void CMainFrame::OnPane(UINT nID)
{
  CComboBox* pCBox = (CComboBox*)m_wndDlgBar.GetDlgItem(IDC_PANE);
  pCBox->SetCurSel((int)(nID - ID_PANEERASE));
  OnSelChangePane();
}

void CMainFrame::OnUpdatePane(CCmdUI* pCmdUI)
{
  CComboBox* pCBox = (CComboBox*)m_wndDlgBar.GetDlgItem(IDC_PANE);
  UINT nIndex = pCBox->GetCurSel();
  pCmdUI->SetCheck((UINT)(ID_PANEERASE + nIndex) == pCmdUI->m_nID);
}
