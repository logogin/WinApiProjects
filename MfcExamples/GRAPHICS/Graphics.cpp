/*************************************************************
‘айл Graphics.cpp
Copyright (c) 1999 ћешков ј., “ихомиров ё.
*************************************************************/

// Graphics.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Graphics.h"
#include "GraphicsFrm.h"
#include "Thread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// количество создаваемых потоков
#define THREAD_NUMBER  10

// возможные относительные приоритеты
int cs_nPrior[] = {
  THREAD_PRIORITY_IDLE,
  THREAD_PRIORITY_LOWEST,
  THREAD_PRIORITY_BELOW_NORMAL,
  THREAD_PRIORITY_NORMAL,
  THREAD_PRIORITY_ABOVE_NORMAL,
  THREAD_PRIORITY_HIGHEST,
  THREAD_PRIORITY_TIME_CRITICAL };

CThread *cs_pThread[THREAD_NUMBER];

/////////////////////////////////////////////////////////////////////////////
// CGraphicsApp

BEGIN_MESSAGE_MAP(CGraphicsApp, CWinApp)
	//{{AFX_MSG_MAP(CGraphicsApp)
	ON_COMMAND(ID_STOP, OnStop)
	ON_COMMAND(ID_RESUME, OnResume)
	//}}AFX_MSG_MAP
  ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphicsApp construction

CGraphicsApp::CGraphicsApp()
{
	// TODO: add construction code here,
  // Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CGraphicsApp object

CGraphicsApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CGraphicsApp initialization

BOOL CGraphicsApp::InitInstance()
{
	// Standard initialization
  // If you are not using these features and wish to reduce the size
  //  of your final executable, you should remove from the following
  //  the specific initialization routines you do not need.

#ifdef _AFXDLL
  Enable3dControls();                     // Call this when using MFC in a shared DLL
#else
  Enable3dControlsStatic();       // Call this when linking to MFC statically
#endif

  // создание главного окна приложени€
  CGraphicsFrame *pWnd = new CGraphicsFrame;
  m_pMainWnd = pWnd;

  int nSizeX = (int)(GetSystemMetrics(SM_CXMAXIMIZED) * 0.3);
  int nSizeY = (int)(GetSystemMetrics(SM_CYMAXIMIZED) * 0.4);

	DWORD dwStyle = (WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME);
	dwStyle &= ~ WS_MAXIMIZEBOX;

  pWnd->Create(NULL, _T("Graphics -- Multithreading"),
    dwStyle, CRect(0, 0, nSizeX, nSizeY), NULL, 
    MAKEINTRESOURCE(IDR_GRAPHICS));

  pWnd->CenterWindow();
  pWnd->ShowWindow(m_nCmdShow);
  pWnd->UpdateWindow();

  // инициализируем переменную по которой осуществл€етс€
  // проверка возможности продолжени€ выполнени€ потоков
  m_nDone = FALSE;

  CDC *pDC = pWnd->GetDC();

	// количество относительных приоритетов
	int nPrior = sizeof(cs_nPrior) / sizeof(int);

  for (int i = 0; i < THREAD_NUMBER; i++)
  {
    COLORREF cr = RGB(12 * i, 12 * i, 12 * i);

    // создаем новый объект потока, передава€ указатель
    // на объект окна (нужно дл€ интерфейсных потоков, в
    // нашем случае этот объект не используетс€ кроме как
    // в главном потоке), дескриптор контекста устройства и цвет
    cs_pThread[i] = new CThread(pWnd, pDC->GetSafeHdc(), cr);

    if (cs_pThread[i] == NULL)
      break;

    ASSERT_VALID(cs_pThread[i]);

    // дл€ исключени€ автоудалени€ объекта потока
    cs_pThread[i]->m_bAutoDelete = FALSE;

    // при создании потока, определ€ем его 
    // как изначально преостановленный, дл€ 
    // того чтобы перед началом его работы 
    // настроить относительный приоритет 
    if (!cs_pThread[i]->CreateThread(CREATE_SUSPENDED))
    {
      delete cs_pThread[i];
      cs_pThread[i] = NULL;

      break;
    }

    VERIFY(cs_pThread[i]->SetThreadPriority(
      cs_nPrior[(i * nPrior) / THREAD_NUMBER]));

    // возобновл€ем поток
    cs_pThread[i]->ResumeThread();
	}

  return TRUE;
}

void CGraphicsApp::CancelThreads() 
{
  // дл€ того чтобы потоки могли продолжить выполенение
  // и обнаружить необходимость завершени€ их необходимо
  // возобновить, если они не были преостановлены ничего
  // не произойдет
  OnResume();

  // теперь все потоки завершатьс€
  m_nDone = TRUE;
  
  // чтобы исключить преждевременное завершение
  // главного потока дождемс€ завершени€ всех
  // остальных
  for (int i = 0; i < THREAD_NUMBER; i++)  
  {
    if (cs_pThread[i] != NULL)
    {
      WaitForSingleObject(cs_pThread[i]->m_hThread, INFINITE);
      delete cs_pThread[i];
    }
  }
}

//
// блокируем и возобновл€ем потоки путем входа или
// выхода из критической секции соответственно
//
 
void CGraphicsApp::OnStop() 
{
  CThread::m_csGDILock.Lock();
}

void CGraphicsApp::OnResume() 
{
  CThread::m_csGDILock.Unlock();
}
