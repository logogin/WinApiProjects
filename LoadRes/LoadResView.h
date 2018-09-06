// LoadResView.h : interface of the CLoadResView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOADRESVIEW_H__E7ACCCEE_FFDB_4B03_AB29_DFE66C608569__INCLUDED_)
#define AFX_LOADRESVIEW_H__E7ACCCEE_FFDB_4B03_AB29_DFE66C608569__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CLoadResView : public CEditView
{
protected: // create from serialization only
	CLoadResView();
	DECLARE_DYNCREATE(CLoadResView)

// Attributes
public:
	CLoadResDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoadResView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLoadResView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CLoadResView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in LoadResView.cpp
inline CLoadResDoc* CLoadResView::GetDocument()
   { return (CLoadResDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOADRESVIEW_H__E7ACCCEE_FFDB_4B03_AB29_DFE66C608569__INCLUDED_)
