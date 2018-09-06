/*************************************************************
Файл AnimateDlg.cpp
Copyright (c) 1999 Мешков А., Тихомиров Ю.
*************************************************************/

// AnimateDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Animate.h"
#include "AnimateDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAnimateDlg dialog

CAnimateDlg::CAnimateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAnimateDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAnimateDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

//
// связывание объектов класса CAnimateCtrl 
// с элементами диалога
//
void CAnimateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAnimateDlg)
	DDX_Control(pDX, IDC_ANIMATE_2, m_Animate_2);
	DDX_Control(pDX, IDC_ANIMATE_1, m_Animate_1);
	//}}AFX_DATA_MAP
}

//
// добавляем в карту сообщений функции-обработчики
// уведомлений. (Добавление осуществляется в ручную,
// т.к. ClassWizard не поддерживает эти уведомляющие
// сообщения
//
BEGIN_MESSAGE_MAP(CAnimateDlg, CDialog)
  //{{AFX_MSG_MAP(CAnimateDlg)
  ON_WM_PAINT()
  ON_WM_QUERYDRAGICON()
  //}}AFX_MSG_MAP
  ON_CONTROL(ACN_STOP, IDC_ANIMATE_1, AnimateStop_1)
  ON_CONTROL(ACN_STOP, IDC_ANIMATE_2, AnimateStop_2)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAnimateDlg message handlers

BOOL CAnimateDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
  // "открываем" клип для первого элемента управления
  m_Animate_1.Open(IDR_VISUAL);
  // и немедленно начинаем его просмотр
  m_Animate_1.Play(0, (UINT)-1, 1);

  // "открываем" клип для второго элемента управления
  m_Animate_2.Open(IDR_VISUAL);
		
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAnimateDlg::OnPaint() 
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
HCURSOR CAnimateDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//
// функция обработки уведомления от первого элемента 
// управления о завершении просмотра - начинаем просмотр
// во втором элементе управления
//
void CAnimateDlg::AnimateStop_1()
{
  m_Animate_2.Play(0, (UINT)-1, 1);
}

//
// функция обработки уведомления от второго элемента 
// управления о завершении просмотра - начинаем просмотр
// в первом элементе управления
//
void CAnimateDlg::AnimateStop_2()
{
  m_Animate_1.Play(0, (UINT)-1, 1);
}

