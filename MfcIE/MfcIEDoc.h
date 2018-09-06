// MfcIEDoc.h : interface of the CMfcIEDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MFCIEDOC_H__156A9C4C_E773_4B6C_82FF_2A80F298E72C__INCLUDED_)
#define AFX_MFCIEDOC_H__156A9C4C_E773_4B6C_82FF_2A80F298E72C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMfcIEDoc : public CDocument
{
protected: // create from serialization only
	CMfcIEDoc();
	DECLARE_DYNCREATE(CMfcIEDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMfcIEDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMfcIEDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMfcIEDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCIEDOC_H__156A9C4C_E773_4B6C_82FF_2A80F298E72C__INCLUDED_)
