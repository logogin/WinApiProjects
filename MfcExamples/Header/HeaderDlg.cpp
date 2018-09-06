// HeaderDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Header.h"
#include "HeaderDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHeaderDlg dialog

CHeaderDlg::CHeaderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHeaderDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHeaderDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHeaderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHeaderDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CHeaderDlg, CDialog)
	//{{AFX_MSG_MAP(CHeaderDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHeaderDlg message handlers

BOOL CHeaderDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
  CRect rect;
  GetClientRect(&rect);
  rect.bottom = 30;
  rect.DeflateRect(5, 5);

  m_Horz.Create(HDS_BUTTONS | HDS_HORZ | CCS_TOP | HDS_DRAGDROP |
    WS_CHILD | WS_VISIBLE, rect, this, 1000);

  int nWidth = rect.Width() / 5;

  TCHAR szText[2];
  HD_ITEM item = { HDI_TEXT | HDI_WIDTH, nWidth, szText, NULL, 1 };

  for (int i = 0; i < 5; i++)
  {
    m_Offset[i] = nWidth;

    szText[0] = 'A'+i; szText[1] = '\0';

    m_Horz.InsertItem(i, &item);
  }
	
  m_Horz.SetHotDivider(2);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CHeaderDlg::OnPaint() 
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
		CPaintDC dc(this); // device context for painting

    CPen pen(PS_DOT, 1, RGB(0, 0, 0));
    CPen *pPen = dc.SelectObject(&pen);

    CRect rect;
    GetClientRect(&rect);
    rect.DeflateRect(5, 5);
    rect.top += 20;

    dc.FillSolidRect(&rect, RGB(255, 255, 255));

    int nOffset = 4;

    for (int i = 0; i < 5; i++)
    {
      if ((nOffset += m_Offset[i]) >= rect.right)
        break;

      dc.MoveTo(nOffset, 20);
      dc.LineTo(nOffset, rect.bottom);
    }

    for (i = 1; i < 10; i++)
    {
      dc.MoveTo(rect.left, rect.top + (rect.Height() / 10) * i);
      dc.LineTo(rect.right, rect.top + (rect.Height() / 10) * i);
    }

    dc.SelectObject(pPen);

		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CHeaderDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CHeaderDlg::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
  NMHDR *nmhdr = (NMHDR *)lParam;

  if (nmhdr->hwndFrom == m_Horz.m_hWnd)
  {
    if (nmhdr->code == HDN_ENDTRACK)
    {
      HD_NOTIFY *phdn = (HD_NOTIFY *)lParam;
      m_Offset[phdn->iItem] = phdn->pitem->cxy;

      InvalidateRect(NULL);
    }
  }

	return CDialog::OnNotify(wParam, lParam, pResult);
}
