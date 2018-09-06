// LoadResDoc.h : interface of the CLoadResDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOADRESDOC_H__A9503C41_FD2E_42D2_9209_A9F020673680__INCLUDED_)
#define AFX_LOADRESDOC_H__A9503C41_FD2E_42D2_9209_A9F020673680__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CLoadResDoc : public CDocument
{
protected: // create from serialization only
	CLoadResDoc();
	DECLARE_DYNCREATE(CLoadResDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoadResDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLoadResDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CLoadResDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOADRESDOC_H__A9503C41_FD2E_42D2_9209_A9F020673680__INCLUDED_)
