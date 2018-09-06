///////////////////////////////////////////////////////////
// ���� MainFrm.cpp
// Copyright (c) 1999 ������ �., ��������� �.
///////////////////////////////////////////////////////////

// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "MDI.h"

#include "MDIChild.h"
#include "MainFrm.h"

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
 	ON_COMMAND(ID_FILE_TEXT, OnText)
	 ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

LPCTSTR lpszTextClass;

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnText() 
{
 // ������� ������ ������ ��� ��������� ���� "MDI child"
 CTextWnd *pTextWnd = new CTextWnd;

 // ������� ���� Windows "MDI child"
 if (!pTextWnd->Create(lpszTextClass,
                        _TEXT("�������� ���� \"MDI child\""),
                        0, rectDefault, this))
    return;
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// ������������ ����� ����� ���� Windows ��� "MDI child"
 lpszTextClass = AfxRegisterWndClass(
     CS_HREDRAW | CS_VREDRAW,
			  AfxGetApp()->LoadCursor(IDC_MDITEXT),
			  (HBRUSH) (COLOR_WINDOW+1),
			  AfxGetApp()->LoadIcon(IDI_MDITEXT));

 // �������� ���������� ������� ID_FILE_TEXT
 OnText();

	return 0;
}
