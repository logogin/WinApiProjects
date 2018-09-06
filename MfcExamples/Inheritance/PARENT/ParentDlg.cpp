// ParentDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Parent.h"
#include "ParentDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

UINT InheritedThread(LPVOID pParam);

/////////////////////////////////////////////////////////////////////////////
// CParentDlg dialog

CParentDlg::CParentDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CParentDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CParentDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CParentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CParentDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CParentDlg, CDialog)
	//{{AFX_MSG_MAP(CParentDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_CHILD, OnChild)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CParentDlg message handlers

BOOL CParentDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	CString csMessage = "Number of threads\n"
		                  "and child processes:\t0";

	GetDlgItem(IDC_MSG)->SetWindowText(csMessage);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CParentDlg::OnPaint() 
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
HCURSOR CParentDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//
// ������� ��������� ������� �������� 
// ������ ������ � ��������� ��������
//
void CParentDlg::OnChild() 
{
  // ������� ���������
  static int s_nCount = 0;

  // �������� ������������ ������
  SECURITY_ATTRIBUTES sa = 
  { 
    sizeof(SECURITY_ATTRIBUTES),
    NULL, TRUE 
  };

  // �������� ������ �������� ������
  CWinThread *pThread = AfxBeginThread(
    (AFX_THREADPROC)InheritedThread, 0, 
    THREAD_PRIORITY_NORMAL, 0, 0, &sa);

  // ��������� ����������� ��� �������� ������ ��������
  PROCESS_INFORMATION pi;
  STARTUPINFO si;

  // ��������� ��������� STARTUPINFO 
  GetStartupInfo(&si);

  // ��������� ��������� ������ ��� 
  // ��������/������� ������ ��������
  // (������ ������ CWinTread �������� 
  // ���������� ������)
  CString csCommand;
	csCommand.Format("Child.exe %d", pThread->m_hThread);

  // �������� ��������� �� �������������� ������
  LPTSTR lpCmdLine = 
    csCommand.GetBuffer(csCommand.GetLength());

  // �������� ��������� ��������
  CreateProcess(
    NULL,       // ��� ������ ��������� �� ������ ���������
    lpCmdLine,                 // ��������� ������ �������� 
    NULL,                     // ���������� �������� ������ 
                                   // �������� �� ��������� 
    NULL, // ���������� �������� ������ ������ �� ��������� 
    TRUE,                        // ����������� ����������� 
    CREATE_DEFAULT_ERROR_MODE,      // ���������� ��������� 
                                                  // ������ 
    NULL,                  // ���������� ��������� �� ����� 
    NULL,                  // ������� ������� �� ���������� 
    &si,                      // �������� ����� ����������� 
                                   // ��������� STARTUPINFO 
    &pi // ������� ��������� � ������ ���������� � �������� 
    );

  // ����������� �����
  csCommand.ReleaseBuffer();

  //
  // ���������� ���������� � ������� � �������� ���������
  //
  CString csMessage;
  csMessage.Format("Number of threads\n"
    "and child processes:\t%d", ++s_nCount);

  GetDlgItem(IDC_MSG)->SetWindowText(csMessage);
}

// ����������� ������� ������
UINT InheritedThread(LPVOID pParam)
{
  // ����� ����������� ������ ��� ����������
  // �������� ��� ������� ������� ��-���!
  // �������������� ����� �� ����������� �������
  for (; ;)
    Sleep(10);  // ��� �������� ������������� ����������

  return 0;
}
