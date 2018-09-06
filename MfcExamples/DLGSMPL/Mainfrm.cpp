//////////////////////////////////////////////////////////////
// Файл MainFrm.cpp
// Copyright (c) 1999 Мешков А., Тихомиров Ю.
//////////////////////////////////////////////////////////////

// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "DlgSmpl.h"

#include "ChildWnd.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_NEW, OnNew)
	ON_COMMAND(ID_OPEN, OnOpen)
	ON_COMMAND(ID_CLOSE, OnClose)
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
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
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

 OnNew();

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	return CMDIFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnNew() 
{
	CChildWnd *pChildWnd = new CChildWnd;

	if(!pChildWnd->Create(NULL, _T("Дочернее окно"),
                       0, rectDefault, this))
  return;
}

void CMainFrame::OnOpen() 
{
  // Заголовок блока диалога
  TCHAR title[] = "Пример настройки блока диалога \"Открытие файла\"";

  // Создаем объект блока диалога
  CFileDialog fileDlg(TRUE);

  // Формируем шаблоны имен отображаемых файлов
  CString str("Все файлы (*.*)"); str += (TCHAR)NULL;
  str += "*.*"; str += (TCHAR)NULL;
  str += ("Файлы исходных текстов (cpp, h)"); str += (TCHAR)NULL;
  str += "*.cpp; *.h"; str += (TCHAR)NULL;
  str += "Исполняемые файлы (*.exe)"; str += (TCHAR)NULL;
  str += "*.exe"; str += (TCHAR)NULL;

  // Устанавливает фильтр
  fileDlg.m_ofn.lpstrFilter = str;

  // При открытии блока диалога отображается список
  // файлов, имеющих расширение .cpp или .h
  fileDlg.m_ofn.nFilterIndex = 2;

  // Готовим буфер для полного имени выбранного файла
  TCHAR strName[_MAX_PATH];

  // Этот буфер должен быть пуст
  strName[0] = (TCHAR)NULL;
  fileDlg.m_ofn.lpstrFile = strName;

  // Передаем заголовок блока диалога
  fileDlg.m_ofn.lpstrTitle = title;

  // К флагам устанавливаемым по умолчанию добавляем возможность
  // выбора нескольких файлов одновременно
  fileDlg.m_ofn.Flags |= OFN_ALLOWMULTISELECT;

  // Выводим блок диалога на экран
  if (fileDlg.DoModal() == IDOK)
  {
    // Если блок диалога закрыт нажатием кнопки OK,
    // в заголовок текущего активного дочернего окна
    // выводим имя первого выбранного файла
    CChildWnd *pWnd = (CChildWnd *)GetActiveFrame();
    pWnd->SetWindowText(fileDlg.m_ofn.lpstrFile);
  }
}

void CMainFrame::OnClose() 
{
  // Создаем объект блока диалога
  CFileDialog fileDlg(FALSE);

  // Определяем расширение, которое будет присваиваться
  // имени файла по умолчанию
  CString ext("hhp");
  fileDlg.m_ofn.lpstrDefExt = ext;

  // Заголовок блока диалога
  TCHAR title[] = "Пример настройки блока диалога \"Сохранить файл\"";
  fileDlg.m_ofn.lpstrTitle = title;

  // Задаем вывод флажка "Только для чтения" (Read Only) и
  // снимаем режим Проводник (Explorer)
  fileDlg.m_ofn.Flags &= ~(OFN_HIDEREADONLY  | OFN_EXPLORER);

  // Выводим блок диалога на экран
  if(fileDlg.DoModal() == IDOK)
  {
    // Если блок диалога закрыт нажатием кнопки OK,
    // в заголовок текущего активного дочернего окна
    // выводим имя первого выбранного файла
    CChildWnd *pWnd = (CChildWnd *)GetActiveFrame();
    pWnd->SetWindowText(fileDlg.GetFileName());
  }
}

