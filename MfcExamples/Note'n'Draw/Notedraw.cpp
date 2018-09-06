// NoteDraw.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "NoteDraw.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "NoteDoc.h"
#include "NoteView.h"
#include "DrawDoc.h"
#include "DrawView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNDApp

BEGIN_MESSAGE_MAP(CNDApp, CWinApp)
	//{{AFX_MSG_MAP(CNDApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_PRINT_SETUP, OnPrintSetup)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
  // Standard print based document commands
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNDApp construction

CNDApp::CNDApp()
{
  PRINTDLG pd;
  GetPrinterDeviceDefaults(&pd);
  SelectPrinter(pd.hDevNames, pd.hDevMode, FALSE);
  
  CDC dc;
  CreatePrinterDC(dc);

  m_sizePaper = CSize(dc.GetDeviceCaps(HORZSIZE)*10,
                      dc.GetDeviceCaps(VERTSIZE)*10);
  
  m_rtMargin  = CRect(200, 300, 200, 200);
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CNDApp object

CNDApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CNDApp initialization

BOOL CNDApp::InitInstance()
{
	// Standard initialization

	Enable3dControls();			// Call this when using MFC in a shared DLL

	CMultiDocTemplate* pDocTemplate;
  
  // Создаем объект шаблона документа для работы с текстом
  pDocTemplate = new CMultiDocTemplate(
		IDR_NOTETYPE,
		RUNTIME_CLASS(CNoteDoc),
		RUNTIME_CLASS(CNoteFrame),
		RUNTIME_CLASS(CNoteView));
  // Добавляем шаблон в список	
  AddDocTemplate(pDocTemplate);

  // Создаем объект шаблона документа для работы с графикой
  pDocTemplate = new CMultiDocTemplate(
		IDR_DRAWTYPE,
		RUNTIME_CLASS(CDrawDoc),
		RUNTIME_CLASS(CDrawFrame),
		RUNTIME_CLASS(CDrawView));
	// Добавляем шаблон в список
  AddDocTemplate(pDocTemplate);

  // create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

  OnFileNew();
	return TRUE;
}

// App command to run the dialog
void CNDApp::OnAppAbout()
{
	CDialog aboutDlg(IDD_ABOUTBOX);
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CNDApp commands

void CNDApp::OnPrintSetup()
{
  // создаем объект стандартного блока диалога
  // Print Setup (Настройка печати)
  CPrintDialog dlgPD(TRUE);
 
  // для получения параметров принтера, установленного
  // по умолчанию создаем объект
  PRINTDLG pd;
  // устанавливаем указатель на глобальный блок памяти в NULL,
  // с тем, чтобы запросить у системы параметры принтера
	pd.hDevMode = NULL;
  // позволяет получить текущую конфигурацию принтера
  GetPrinterDeviceDefaults(&pd);

  // поскольку параметр pd.hDevMode указавает на глобальный
  // перемещаемый блок памяти, то перед началом работы с ним,
  // необходимо его зафиксировать, иначе ничего не получится
  DEVMODE *dm = (DEVMODE *)LocalLock(pd.hDevMode);
  // теперь можно заполнять поля структуры DEVMODE, значениями
  // необходимыми для инициализации блока диалога
  // Print Setup (Настройка печати)
  dm->dmFields = DM_ORIENTATION | DM_PAPERSIZE;
  dm->dmOrientation = DMORIENT_LANDSCAPE;
  dm->dmPaperSize = DMPAPER_LETTER;

  // передаем указатель на заполненную структуру DEVMODE
  // объекту класса CPrintDialog
  dlgPD.m_pd.hDevMode  = pd.hDevMode;
  // теперь зафиксированный блок памяти можно освободить
  LocalUnlock(pd.hDevMode);

  // выводим блок диалога на экран
  if(dlgPD.DoModal() == IDOK)
  {
    // здесь можно зафиксировать выбор пользователя
  }
}
