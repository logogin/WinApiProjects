// LoadRes.h : main header file for the LOADRES application
//

#if !defined(AFX_LOADRES_H__E0767D8E_6990_4121_9773_383C99FA9D6D__INCLUDED_)
#define AFX_LOADRES_H__E0767D8E_6990_4121_9773_383C99FA9D6D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CLoadResApp:
// See LoadRes.cpp for the implementation of this class
//

class CLoadResApp : public CWinApp
{
public:
	CLoadResApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoadResApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CLoadResApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOADRES_H__E0767D8E_6990_4121_9773_383C99FA9D6D__INCLUDED_)
