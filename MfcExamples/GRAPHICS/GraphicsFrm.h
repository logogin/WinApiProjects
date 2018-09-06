/*************************************************************
Файл GraphicsFrm.h
Copyright (c) 1999 Мешков А., Тихомиров Ю.
*************************************************************/

// GraphicsFrm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGraphicsFrame frame

class CGraphicsFrame : public CFrameWnd
{
public:
	CGraphicsFrame(); 

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphicsFrame)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CGraphicsFrame();

	// Generated message map functions
	//{{AFX_MSG(CGraphicsFrame)
	afx_msg void OnPaint();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
