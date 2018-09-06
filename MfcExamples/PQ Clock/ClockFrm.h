/*************************************************************
Файл ClockFrm.h
Copyright (c) 1999 Мешков А., Тихомиров Ю.
*************************************************************/

// ClockFrm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CClockFrame frame

class CClockFrame : public CFrameWnd
{
public:
	CClockFrame(); 

// Attributes
public:

// Operations
public:
	void Redraw();

private:
	void RotatePoint(POINT pt[], int nNum, double nAngle);
	void SetMode(CDC *pDC);
	void DrawClock(CDC *pDC);
	void DrawLabel(CDC *pDC);
	void DrawArrows(CDC *pDC, CTime &tm);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClockFrame)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CClockFrame();

	// Generated message map functions
	//{{AFX_MSG(CClockFrame)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	int m_cxClient;
	int m_cyClient;

	CFont m_Font_1;
	CFont m_Font_2;
	CFont m_Font_3;

	CBrush m_wndBrush;
	CPen m_wndPen;

	CBrush m_arrBrush;
	CPen m_arrPen;

	CBrush m_clkBrush;
	CPen m_clkPen;

	CBrush m_rndBrush;
	CPen m_rndPen;

	CBrush m_crnBrush;
	CPen m_crnPen;
};

/////////////////////////////////////////////////////////////////////////////
