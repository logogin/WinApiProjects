///////////////////////////////////////////////////////////
// Файл AppAbout.cpp
// Copyright (c) 1999 Мешков А., Тихомиров Ю.
///////////////////////////////////////////////////////////

// AppAbout.cpp : implementation file
//

#include "stdafx.h"
#include "MDI.h"
#include "AppAbout.h"

/////////////////////////////////////////////////////////////////////////////
// CAppAbout dialog

CAppAbout::CAppAbout(CWnd* pParent /*=NULL*/)
{
 Create(CAppAbout::IDD, pParent);
	//{{AFX_DATA_INIT(CAppAbout)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BEGIN_MESSAGE_MAP(CAppAbout, CDialog)
	//{{AFX_MSG_MAP(CAppAbout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
