// MfcIE.h : main header file for the MFCIE application
//

#if !defined(AFX_MFCIE_H__5785E3E9_1E67_4706_88A0_3C9E304A1F4B__INCLUDED_)
#define AFX_MFCIE_H__5785E3E9_1E67_4706_88A0_3C9E304A1F4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMfcIEApp:
// See MfcIE.cpp for the implementation of this class
//

class CMfcIEApp : public CWinApp
{
public:
	CMfcIEApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMfcIEApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMfcIEApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCIE_H__5785E3E9_1E67_4706_88A0_3C9E304A1F4B__INCLUDED_)
