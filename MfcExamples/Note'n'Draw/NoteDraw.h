// NoteDraw.h : main header file for the NOTEDRAW application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CNDApp:
// See NoteDraw.cpp for the implementation of this class
//

class CNDApp : public CWinApp
{
public:
	CRect m_rtMargin;
	CSize m_sizePaper;
	CNDApp();

public:
//  CMap<WORD, WORD, CString, CString&> theFont;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNDApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CNDApp)
	afx_msg void OnAppAbout();
	afx_msg void OnPrintSetup();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
