/*************************************************************
Файл TerminalDlg.cpp
Copyright (c) 1999 Мешков А., Тихомиров Ю.
*************************************************************/

// TerminalDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Terminal.h"
#include "TerminalDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

DWORD OutData(LPVOID lParam);
DWORD InData(LPVOID lParam);
DWORD DrawData(LPVOID lParam);

IMPLEMENT_DYNAMIC(CTerminalDlg, CDialog)

/////////////////////////////////////////////////////////////////////////////
// CTerminalDlg dialog

CTerminalDlg::CTerminalDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTerminalDlg::IDD, pParent),
	  m_Quit(FALSE, TRUE)
{
	//{{AFX_DATA_INIT(CTerminalDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_pOutThread = NULL;
	m_pInThread = NULL;
	m_pDrawThread = NULL;
}

void CTerminalDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTerminalDlg)
	DDX_Control(pDX, IDC_TERMINAL, m_Terminal);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTerminalDlg, CDialog)
	//{{AFX_MSG_MAP(CTerminalDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_COM1, OnCom1)
	ON_BN_CLICKED(IDC_COM2, OnCom2)
	ON_BN_CLICKED(IDC_COM3, OnCom3)
	ON_BN_CLICKED(IDC_COM4, OnCom4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTerminalDlg message handlers

BOOL CTerminalDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	Initialize("COM1");
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTerminalDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTerminalDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTerminalDlg::OnClose() 
{
	UnInitialize();

	CDialog::OnClose();
}

void CTerminalDlg::OnCom1() 
{
	Initialize(_T("COM1"));
}

void CTerminalDlg::OnCom2() 
{
	Initialize(_T("COM2"));
}

void CTerminalDlg::OnCom3() 
{
	Initialize(_T("COM3"));
}

void CTerminalDlg::OnCom4() 
{
	Initialize(_T("COM4"));
}

void CTerminalDlg::Initialize(LPCTSTR lpCommPort) 
{
	UnInitialize();

	CString csTitle = _T("Terminal");
	
	if (m_Modem.Initialize(lpCommPort))
	{
		m_Terminal.EnableWindow(TRUE);
		GotoDlgCtrl(&m_Terminal);

		m_pOutThread = AfxBeginThread((AFX_THREADPROC)OutData, this);
		m_pOutThread->m_bAutoDelete = FALSE;

		m_pInThread = AfxBeginThread((AFX_THREADPROC)InData, this);
		m_pInThread->m_bAutoDelete = FALSE;

		m_pDrawThread = AfxBeginThread((AFX_THREADPROC)DrawData, this);
		m_pDrawThread->m_bAutoDelete = FALSE;

		csTitle.Format("%s -- %s", _T("Terminal"), lpCommPort);
	}

	SetWindowText(csTitle);
}

void CTerminalDlg::UnInitialize() 
{
	m_Terminal.EnableWindow(FALSE);

	m_Quit.SetEvent();

	if (m_pOutThread)
	{
		WaitForSingleObject(m_pOutThread->m_hThread, INFINITE);

		delete m_pOutThread;
		m_pOutThread = NULL;
	}

	if (m_pInThread)
	{
		m_Modem.UnInitialize();

		WaitForSingleObject(m_pInThread->m_hThread, INFINITE);

		delete m_pInThread;
		m_pInThread = NULL;
	}

	if (m_pDrawThread)
	{
		WaitForSingleObject(m_pDrawThread->m_hThread, INFINITE);

		delete m_pDrawThread;
		m_pDrawThread = NULL;
	}

	m_Quit.ResetEvent();
}

DWORD OutData(LPVOID lParam)
{
	CTerminalDlg *pWnd = (CTerminalDlg *)lParam;
	ASSERT(pWnd->IsKindOf(RUNTIME_CLASS(CTerminalDlg)));
	
	CSyncObject *pObject[] = 
	  { &pWnd->m_Modem.m_OutBuffer.m_NotEmpty, &pWnd->m_Quit };

	DWORD dwBytes;
	CHAR cChar;

	for (; ;)
	{
		CMultiLock Lock(pObject, 2);
		
		switch (Lock.Lock(INFINITE, FALSE))
		{
		case WAIT_OBJECT_0:
			if (pWnd->m_Modem.m_OutBuffer.ReadChar(cChar))
			{
				WriteFile(pWnd->m_Modem.m_hComm, &cChar, 
					sizeof(CHAR), &dwBytes, NULL);
			}
			break;
		default:
			return 0;
		}
	}

	return 0;
}

DWORD InData(LPVOID lParam)
{
	BYTE szBuffer[4096];

	DWORD dwEvtMask;
	DWORD dwError;
	DWORD dwBytes;
	COMSTAT csStat;

	CTerminalDlg *pWnd = (CTerminalDlg *)lParam;
	ASSERT(pWnd->IsKindOf(RUNTIME_CLASS(CTerminalDlg)));

	CEvent& event = pWnd->m_Quit;

	OVERLAPPED o;
	o.hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

	HANDLE Handles[] = { o.hEvent, event };

	for (; ;)
	{
		ResetEvent(o.hEvent);

		if (!WaitCommEvent(pWnd->m_Modem.m_hComm, &dwEvtMask, &o))
		{
			if (WaitForMultipleObjects(2, Handles, FALSE, INFINITE) ==
				WAIT_OBJECT_0+1)
				break;
		}

		if (dwEvtMask & EV_BREAK)
			break;
		else if (dwEvtMask & EV_RXCHAR)
		{
			ClearCommError(pWnd->m_Modem.m_hComm,	&dwError, &csStat);

			ResetEvent(o.hEvent);

			if (!ReadFile(pWnd->m_Modem.m_hComm, szBuffer, 
				csStat.cbInQue, &dwBytes, &o))
			{
				if (WaitForMultipleObjects(2, Handles, FALSE, INFINITE) ==
					WAIT_OBJECT_0+1)
					break;
			}
		
			for (UINT i = 0; i < csStat.cbInQue; i++)
				pWnd->m_Modem.m_InBuffer.WriteChar(szBuffer[i]);
		}
	}

	return 0;
}

DWORD DrawData(LPVOID lParam)
{
	CTerminalDlg *pWnd = (CTerminalDlg *)lParam;
	ASSERT(pWnd->IsKindOf(RUNTIME_CLASS(CTerminalDlg)));

	CSyncObject *pObject[] = 
	  { &pWnd->m_Modem.m_InBuffer.m_NotEmpty, &pWnd->m_Quit };

	CHAR cChar;
	CString csString;

	for (; ;)
	{
		CMultiLock Lock(pObject, 2);

		switch (Lock.Lock(INFINITE, FALSE))
		{
		case WAIT_OBJECT_0:
			csString.Empty();

			for (; ;)
			{
				if (!pWnd->m_Modem.m_InBuffer.ReadChar(cChar))
					break;
			
				csString += cChar;
			}

			pWnd->m_Terminal.ReplaceSel(csString);
			break;
		default:
			return 0;
		}
	}

	return 0;
}


