/*************************************************************
Файл TermWnd.cpp
Copyright (c) 1999 Мешков А., Тихомиров Ю.
*************************************************************/

// TermWnd.cpp : implementation file
//

#include "stdafx.h"
#include "Terminal.h"
#include "TerminalDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTermWnd

CTermWnd::CTermWnd()
{
}

CTermWnd::~CTermWnd()
{
}


BEGIN_MESSAGE_MAP(CTermWnd, CEdit)
	//{{AFX_MSG_MAP(CTermWnd)
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTermWnd message handlers

void CTermWnd::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if (nChar != 0x1B)
	{
		((CTerminalDlg *)GetParent())->m_Modem.m_OutBuffer.WriteChar((CHAR)nChar);
		if (nChar == 0x0D)
			((CTerminalDlg *)GetParent())->m_Modem.m_OutBuffer.WriteChar(0x0A);
	}
}

