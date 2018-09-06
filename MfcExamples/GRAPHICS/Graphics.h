/*************************************************************
Файл Graphics.h
Copyright (c) 1999 Мешков А., Тихомиров Ю.
*************************************************************/

// Graphics.h : main header file for the TEMPLATE application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CGraphicsApp:
// See Graphics.cpp for the implementation of this class
//

class CGraphicsApp : public CWinApp
{
public:
	CGraphicsApp();

// Operations
	void CancelThreads();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphicsApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CGraphicsApp)
	afx_msg void OnStop();
	afx_msg void OnResume();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Data
public:
	BOOL m_nDone;
};


/////////////////////////////////////////////////////////////////////////////
