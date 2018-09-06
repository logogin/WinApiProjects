/*************************************************************
Файл LineThread.h
Copyright (c) 1999 Мешков А., Тихомиров Ю.
*************************************************************/

// LineThread.h : header file
//

#include "LineWnd.h"

/////////////////////////////////////////////////////////////////////////////
// CLineThread thread

class CLineThread : public CWinThread
{
	DECLARE_DYNCREATE(CLineThread)
protected:
	CLineThread();           // protected constructor used by dynamic creation
public:
	CLineThread(HWND hwndParent);
	void operator delete(void* p);

// Attributes
public:
	static HANDLE m_hEventLineThreadKilled;

protected:
	HWND m_hwndParent;
	CLineWnd m_wndLine;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLineThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual BOOL OnIdle(LONG lCount);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CLineThread();

	// Generated message map functions
	//{{AFX_MSG(CLineThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
