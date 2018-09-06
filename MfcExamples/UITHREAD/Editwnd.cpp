/*************************************************************
Файл EditWnd.cpp
Copyright (c) 1999 Мешков А., Тихомиров Ю.
*************************************************************/

// EditWnd.cpp : implementation file
//

#include "stdafx.h"
#include "uithread.h"
#include "EditWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditWnd

CEditWnd::CEditWnd()
{
}

CEditWnd::~CEditWnd()
{
}


BEGIN_MESSAGE_MAP(CEditWnd, CEdit)
	//{{AFX_MSG_MAP(CEditWnd)
	ON_WM_CREATE()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditWnd message handlers

int CEditWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CEdit::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	SetTimer(1, 1000, NULL);
	
	return 0;
}

void CEditWnd::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent == 1)
	{
		((CUIThreadApp *)AfxGetApp())->m_TextLock.Lock();

		GetWindowText(((CUIThreadApp *)AfxGetApp())->m_Text);

		((CUIThreadApp *)AfxGetApp())->m_TextLock.Unlock();
	}
	
	CEdit::OnTimer(nIDEvent);
}

