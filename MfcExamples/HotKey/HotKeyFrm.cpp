// HotKeyFrm.cpp : implementation file
//

#include "stdafx.h"
#include "HotKey.h"
#include "HotKeyFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define IDM_HOTKEYBOX	0x0010

static struct { 
	WORD m_wVK;
	WORD m_wMod;
	UINT m_nCmd;
} gHotKey[5] =
{{VK_F1, HOTKEYF_SHIFT | HOTKEYF_CONTROL, SW_MINIMIZE},
 {VK_F2, HOTKEYF_SHIFT | HOTKEYF_CONTROL, SW_MAXIMIZE},
 {VK_F3, HOTKEYF_SHIFT | HOTKEYF_CONTROL, SW_SHOWNORMAL},
 {VK_F4, HOTKEYF_SHIFT | HOTKEYF_CONTROL, SW_HIDE},
 {VK_F5, HOTKEYF_SHIFT | HOTKEYF_CONTROL}
};

UINT TransModifiers(WORD wMod)
{
	UINT uMod = 0;
	if (wMod & HOTKEYF_ALT)
		uMod |= MOD_ALT;
	if (wMod & HOTKEYF_SHIFT)
		uMod |= MOD_SHIFT;
	if (wMod & HOTKEYF_CONTROL)
		uMod |= MOD_CONTROL;

	return uMod;
}

/////////////////////////////////////////////////////////////////////////////
// CHotKeyDlg - диалог "Горячие клавиши"

class CHotKeyDlg : public CDialog
{
public:
	CHotKeyDlg();

	// Dialog Data
		//{{AFX_DATA(CHotKeyDlg)
		enum { IDD = IDD_HOTKEYBOX };
		CHotKeyCtrl m_Minimize;
		CHotKeyCtrl m_Maximize;
		CHotKeyCtrl m_ShowNormal;
		CHotKeyCtrl m_Hide;
		CHotKeyCtrl m_DrawTime;
		//}}AFX_DATA

  // ClassWizard generated virtual function overrides
		//{{AFX_VIRTUAL(CHotKeyDlg)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:
  //{{AFX_MSG(CHotKeyDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

CHotKeyDlg::CHotKeyDlg() : CDialog(CHotKeyDlg::IDD)
{
	//{{AFX_DATA_INIT(CHotKeyDlg)
  //}}AFX_DATA_INIT
}

void CHotKeyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CHotKeyDlg)
	DDX_Control(pDX, IDC_MINIMIZE, m_Minimize);
	DDX_Control(pDX, IDC_MAXIMIZE, m_Maximize);
	DDX_Control(pDX, IDC_SHOWNORMAL, m_ShowNormal);
	DDX_Control(pDX, IDC_HIDE, m_Hide);
	DDX_Control(pDX, IDC_DRAWTIME, m_DrawTime);
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CHotKeyDlg, CDialog)
	//{{AFX_MSG_MAP(CHotKeyDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CHotKeyDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_Minimize.SetHotKey(gHotKey[0].m_wVK, gHotKey[0].m_wMod);
	m_Maximize.SetHotKey(gHotKey[1].m_wVK, gHotKey[1].m_wMod);
	m_ShowNormal.SetHotKey(gHotKey[2].m_wVK, gHotKey[2].m_wMod);
	m_Hide.SetHotKey(gHotKey[3].m_wVK, gHotKey[3].m_wMod);
	m_DrawTime.SetHotKey(gHotKey[4].m_wVK, gHotKey[4].m_wMod);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CHotKeyDlg::OnOK() 
{
	m_Minimize.GetHotKey(gHotKey[0].m_wVK, gHotKey[0].m_wMod);
	RegisterHotKey(AfxGetMainWnd()->m_hWnd, 0, 
		TransModifiers(gHotKey[0].m_wMod), gHotKey[0].m_wVK);

	m_Maximize.GetHotKey(gHotKey[1].m_wVK, gHotKey[1].m_wMod);
	RegisterHotKey(AfxGetMainWnd()->m_hWnd, 1, 
		TransModifiers(gHotKey[1].m_wMod), gHotKey[1].m_wVK);

	m_ShowNormal.GetHotKey(gHotKey[2].m_wVK, gHotKey[2].m_wMod);
	RegisterHotKey(AfxGetMainWnd()->m_hWnd, 2, 
		TransModifiers(gHotKey[2].m_wMod), gHotKey[2].m_wVK);

	m_Hide.GetHotKey(gHotKey[3].m_wVK, gHotKey[3].m_wMod);
	RegisterHotKey(AfxGetMainWnd()->m_hWnd, 3, 
		TransModifiers(gHotKey[3].m_wMod), gHotKey[3].m_wVK);

	m_DrawTime.GetHotKey(gHotKey[4].m_wVK, gHotKey[4].m_wMod);

	DWORD dwKeyAndShift = m_DrawTime.GetHotKey();
	AfxGetMainWnd()->SendMessage(WM_SETHOTKEY, dwKeyAndShift);
	
	CDialog::OnOK();
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

CHotKeyFrame::CHotKeyFrame()
{
}

CHotKeyFrame::~CHotKeyFrame()
{
}

BEGIN_MESSAGE_MAP(CHotKeyFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CHotKeyFrame)
	ON_WM_PAINT()
  ON_WM_SYSCOMMAND()
	ON_WM_CREATE()
	ON_MESSAGE(WM_HOTKEY, OnHotKey)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHotKeyFrame message handlers

void CHotKeyFrame::OnPaint() 
{
	CPaintDC dc(this); 
}

int CHotKeyFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
  CMenu* pSysMenu = GetSystemMenu(FALSE);

  // IDM_HOTKEYBOX must be in the system command range.
  ASSERT((IDM_HOTKEYBOX & 0xFFF0) == IDM_HOTKEYBOX);
  ASSERT(IDM_HOTKEYBOX < 0xF000);

  pSysMenu->AppendMenu(MF_STRING, IDM_HOTKEYBOX, _T("Клавиши вызова"));
	
	return 0;
}

void CHotKeyFrame::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_HOTKEYBOX)
  {
		CHotKeyDlg dlgHotKey;
    dlgHotKey.DoModal();
  }
	else if (nID == SC_HOTKEY)
	{
		if (!IsIconic())
		{
			InvalidateRect(NULL);
			UpdateWindow();

			CClientDC dc(this);

			CRect rect;
			GetClientRect(rect);

			dc.SetBkMode(TRANSPARENT);
			dc.DrawText(CTime::GetCurrentTime().Format(_T("%H:%M:%S")), 
				&rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
	}
  else
    CWnd::OnSysCommand(nID, lParam);
}

LONG CHotKeyFrame::OnHotKey(UINT nID, LPARAM lParam)
{
	if (0 <= nID && nID < 5)
		ShowWindow(gHotKey[nID].m_nCmd);

	return 0;
}

