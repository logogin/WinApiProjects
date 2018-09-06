//////////////////////////////////////////////////////////////
// ���� MainFrm.cpp
// Copyright (c) 1999 ������ �., ��������� �.
//////////////////////////////////////////////////////////////

// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "DlgSmpl.h"

#include "ChildWnd.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_NEW, OnNew)
	ON_COMMAND(ID_OPEN, OnOpen)
	ON_COMMAND(ID_CLOSE, OnClose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

 OnNew();

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	return CMDIFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnNew() 
{
	CChildWnd *pChildWnd = new CChildWnd;

	if(!pChildWnd->Create(NULL, _T("�������� ����"),
                       0, rectDefault, this))
  return;
}

void CMainFrame::OnOpen() 
{
  // ��������� ����� �������
  TCHAR title[] = "������ ��������� ����� ������� \"�������� �����\"";

  // ������� ������ ����� �������
  CFileDialog fileDlg(TRUE);

  // ��������� ������� ���� ������������ ������
  CString str("��� ����� (*.*)"); str += (TCHAR)NULL;
  str += "*.*"; str += (TCHAR)NULL;
  str += ("����� �������� ������� (cpp, h)"); str += (TCHAR)NULL;
  str += "*.cpp; *.h"; str += (TCHAR)NULL;
  str += "����������� ����� (*.exe)"; str += (TCHAR)NULL;
  str += "*.exe"; str += (TCHAR)NULL;

  // ������������� ������
  fileDlg.m_ofn.lpstrFilter = str;

  // ��� �������� ����� ������� ������������ ������
  // ������, ������� ���������� .cpp ��� .h
  fileDlg.m_ofn.nFilterIndex = 2;

  // ������� ����� ��� ������� ����� ���������� �����
  TCHAR strName[_MAX_PATH];

  // ���� ����� ������ ���� ����
  strName[0] = (TCHAR)NULL;
  fileDlg.m_ofn.lpstrFile = strName;

  // �������� ��������� ����� �������
  fileDlg.m_ofn.lpstrTitle = title;

  // � ������ ��������������� �� ��������� ��������� �����������
  // ������ ���������� ������ ������������
  fileDlg.m_ofn.Flags |= OFN_ALLOWMULTISELECT;

  // ������� ���� ������� �� �����
  if (fileDlg.DoModal() == IDOK)
  {
    // ���� ���� ������� ������ �������� ������ OK,
    // � ��������� �������� ��������� ��������� ����
    // ������� ��� ������� ���������� �����
    CChildWnd *pWnd = (CChildWnd *)GetActiveFrame();
    pWnd->SetWindowText(fileDlg.m_ofn.lpstrFile);
  }
}

void CMainFrame::OnClose() 
{
  // ������� ������ ����� �������
  CFileDialog fileDlg(FALSE);

  // ���������� ����������, ������� ����� �������������
  // ����� ����� �� ���������
  CString ext("hhp");
  fileDlg.m_ofn.lpstrDefExt = ext;

  // ��������� ����� �������
  TCHAR title[] = "������ ��������� ����� ������� \"��������� ����\"";
  fileDlg.m_ofn.lpstrTitle = title;

  // ������ ����� ������ "������ ��� ������" (Read Only) �
  // ������� ����� ��������� (Explorer)
  fileDlg.m_ofn.Flags &= ~(OFN_HIDEREADONLY  | OFN_EXPLORER);

  // ������� ���� ������� �� �����
  if(fileDlg.DoModal() == IDOK)
  {
    // ���� ���� ������� ������ �������� ������ OK,
    // � ��������� �������� ��������� ��������� ����
    // ������� ��� ������� ���������� �����
    CChildWnd *pWnd = (CChildWnd *)GetActiveFrame();
    pWnd->SetWindowText(fileDlg.GetFileName());
  }
}

