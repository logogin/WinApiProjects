// RichEditFrm.h : header file
//

#include "REditCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CRichEditFrame frame

class CRichEditFrame : public CFrameWnd
{
public:
	CRichEditFrame(); 

// Attributes
public:
	CREditCtrl m_REditCtrl;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRichEditFrame)
	protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CRichEditFrame();

	// Generated message map functions
	//{{AFX_MSG(CRichEditFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnFormatFont();
	afx_msg void OnParagraphLeft();
	afx_msg void OnParagraphCenter();
	afx_msg void OnParagraphRight();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnEditPaste();
	afx_msg void OnRect();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
