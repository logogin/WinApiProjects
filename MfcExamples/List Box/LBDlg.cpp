/*************************************************************
Файл LBDlg.cpp
Copyright (c) 1999 Мешков А., Тихомиров Ю.
*************************************************************/

// LBDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LBSmpl.h"
#include "LBDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLBDlg dialog

CLBDlg::CLBDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLBDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLBDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLBDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLBDlg)
	DDX_Control(pDX, IDC_LIST, m_List);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CLBDlg, CDialog)
	//{{AFX_MSG_MAP(CLBDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLBDlg message handlers

BOOL CLBDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	CRect rect;
	GetClientRect(&rect);
	m_List.MoveWindow(&rect);

  // настраиваем начальные размеры для всех
  // элементов списка (в нашем примере в принципе
  // это делать не обязательно)
	m_List.SetItemHeight(0, 36);

  // добавляем три элемента в спискок
	m_List.AddString(_T("Короткий текст"));
	m_List.AddString(_T("Средний по длине текст\nв две строки"));
	m_List.AddString(_T("Длинная строка, для отображения которой "
                            "необходимо несколько строк"));
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CLBDlg::OnPaint() 
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
HCURSOR CLBDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CLBDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
  // настраиваем размеры списка по 
  // размерам окна тогда, когда
  // объект-список уже есть в системе
	if (::IsWindow(m_List.m_hWnd))
	{
		CRect rect(0, 0, cx, cy);

		m_List.MoveWindow(&rect);
		m_List.InvalidateRect(&rect);
	}
}
