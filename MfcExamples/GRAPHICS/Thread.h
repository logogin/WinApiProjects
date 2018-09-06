/*************************************************************
Файл Thread.h
Copyright (c) 1999 Мешков А., Тихомиров Ю.
*************************************************************/

// Thread.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CThread thread

class CThread : public CWinThread
{
public:
	DECLARE_DYNAMIC(CThread)
  CThread(CWnd* pWnd, HDC hDC, COLORREF &cr); 

// Attributes
public:
  static CCriticalSection m_csGDILock;

private:
	CRect m_Rect;
  HDC m_hDC;
	CPoint m_pt, m_offset;
	CBrush m_Brush;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual int Run();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CThread();

protected:
	// Generated message map functions
	//{{AFX_MSG(CThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
