/*************************************************************
Файл CheckBoxDlg.cpp
Copyright (c) 1999 Мешков А., Тихомиров Ю.
*************************************************************/

// CheckBoxDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CheckBox.h"
#include "CheckBoxDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCheckBoxDlg dialog

CCheckBoxDlg::CCheckBoxDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCheckBoxDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCheckBoxDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCheckBoxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCheckBoxDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCheckBoxDlg, CDialog)
	//{{AFX_MSG_MAP(CCheckBoxDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCheckBoxDlg message handlers

BOOL CCheckBoxDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
  // связываем объект класса CColorBox с элементом
  // управления по идентификатору
  VERIFY(m_CheckBox.SubclassDlgItem(IDC_CHECKBOX, this));

  // заполняем список строками,
  // в которых выводятся различные цвета -
  // цветов всего 8, и их определяет наличие или
  // отсутствие сооставляющей
  for (int red = 0; red <= 255; red += 255)
    for (int green = 0; green <= 255; green += 255)
      for (int blue = 0; blue <= 255; blue += 255)
        m_CheckBox.AddColorItem(RGB(red, green, blue));
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCheckBoxDlg::OnPaint() 
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
HCURSOR CCheckBoxDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
