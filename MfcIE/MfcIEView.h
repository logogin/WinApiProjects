// MfcIEView.h : interface of the CMfcIEView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MFCIEVIEW_H__80088147_5B6F_46C3_8306_7688B6CAE641__INCLUDED_)
#define AFX_MFCIEVIEW_H__80088147_5B6F_46C3_8306_7688B6CAE641__INCLUDED_

#include "HtmlDoc.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMfcIEView : public CHtmlView
{
protected: // create from serialization only
	CMfcIEView();
	DECLARE_DYNCREATE(CMfcIEView)

// Attributes
public:
	CMfcIEDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMfcIEView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnBeforeNavigate2(LPCTSTR lpszURL, DWORD nFlags, LPCTSTR lpszTargetFrameName, CByteArray& baPostedData, LPCTSTR lpszHeaders, BOOL* pbCancel);
	virtual void OnDocumentComplete(LPCTSTR lpszURL);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMfcIEView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	BOOL m_bPost;
	BOOL m_bStart;
	CHtmlDoc m_CHtmlDoc;
	//{{AFX_MSG(CMfcIEView)
	afx_msg void OnViewStartrefresh();
	afx_msg void OnViewPostdata();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MfcIEView.cpp
inline CMfcIEDoc* CMfcIEView::GetDocument()
   { return (CMfcIEDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCIEVIEW_H__80088147_5B6F_46C3_8306_7688B6CAE641__INCLUDED_)
