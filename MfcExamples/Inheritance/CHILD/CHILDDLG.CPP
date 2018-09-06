// ChildDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Child.h"
#include "ChildDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildDlg dialog

CChildDlg::CChildDlg(HANDLE hThread, CWnd* pParent /*=NULL*/)
	: CDialog(CChildDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChildDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_hThread = hThread;
}

void CChildDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChildDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CChildDlg, CDialog)
	//{{AFX_MSG_MAP(CChildDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildDlg message handlers

BOOL CChildDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	SetTimer(1, 1000, NULL);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CChildDlg::OnPaint() 
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
HCURSOR CChildDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// функция обработки сообщения от таймера
void CChildDlg::OnTimer(UINT nIDEvent) 
{
  // получаем код возврата наследованного потока,
  // дескриптор которого хранится в переменной m_hThread
  DWORD dwExitCode;
  GetExitCodeThread(m_hThread, &dwExitCode);

  // в зависимости от кода возврата отображаем 
  // соответствующую диагностику
  if (dwExitCode == STILL_ACTIVE)
    GetDlgItem(IDC_MSG)->SetWindowText("Thread is ALIVE");
  else
    GetDlgItem(IDC_MSG)->SetWindowText("Thread is DEAD");

  CDialog::OnTimer(nIDEvent);
} 
