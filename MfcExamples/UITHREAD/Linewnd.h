/*************************************************************
Файл LineWnd.h
Copyright (c) 1999 Мешков А., Тихомиров Ю.
*************************************************************/

// LineWnd.h : header file
//

#define IDC_LINE_WND 1

// структура CCmdMsg используется для передачи параметров
// командных сообщений между окнами различных потоков
struct CCmdMsg
{
  int m_nID;
  int m_nCode;
  void* m_pExtra;
  AFX_CMDHANDLERINFO* m_pHandlerInfo;
};

#define WM_USER_ONCMDMSG (WM_USER + 0x1000)
#define WM_USER_PREPARE_TO_CLOSE (WM_USER + 0x1001)

/////////////////////////////////////////////////////////////////////////////
// CLineWnd window

class CLineWnd : public CWnd
{
	DECLARE_DYNAMIC(CLineWnd)
public:
	CLineWnd();
	BOOL Create(LPCTSTR szTitle, LONG style, const RECT& rect, CWnd* pParent);

// Attributes
public:
	CBrush m_Brush;
	int m_cxClient;
	int m_cyClient;
	int m_Speed;

	enum { SlowSpeed = 5000, NormalSpeed = 2500, FastSpeed = 1000 };

// Operations
public:
	void Redraw();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLineWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLineWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CLineWnd)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnSpeedSlow();
	afx_msg void OnSpeedNormal();
	afx_msg void OnSpeedFast();
	afx_msg void OnUpdateSpeedSlow(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSpeedNormal(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSpeedFast(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg LRESULT OnDelegatedCmdMsg(WPARAM, LPARAM);
	afx_msg LRESULT OnPrepareToClose(WPARAM wParam = 0, LPARAM lParam = 0);

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
