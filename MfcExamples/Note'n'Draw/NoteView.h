// NoteView.h : interface of the CTextView class
//
/////////////////////////////////////////////////////////////////////////////

class CTextView : public CEditView
{
protected: // create from serialization only
	BOOL bFindOnly;
	CTextView();
	DECLARE_DYNCREATE(CTextView)

// Attributes
public:
	CParagraph * FindParagraph(CNoteDoc *pDoc);
  //static const UINT nMsgFndRplc;
// Operations
public:
  CNoteDoc* GetDocument();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTextView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
  virtual void OnTextNotFound(LPCTSTR lpszFind);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTextView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTextView)
	afx_msg void OnChange();
  afx_msg void OnAlign(UINT nID);
	afx_msg void OnFont();
	afx_msg void OnEditFind();
  afx_msg LRESULT OnNewCmd(WPARAM wParam, LPARAM lParam);
	afx_msg void OnEditReplace();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in NoteView.cpp
inline CNoteDoc* CTextView::GetDocument()
   { return (CNoteDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CNoteView view

class CNoteView : public CScrollView
{
protected:
	void PrintHeader(CDC *pDC, CPrintInfo *pInfo, CString strHeader);
	CNoteView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CNoteView)

// Attributes
public:

// Operations
public:
  void DrawMargins(CDC* pDC, CRect &rect);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNoteView)
	public:
  virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct
	protected:
  virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CNoteView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	public:
  //{{AFX_MSG(CNoteView)
	afx_msg void OnPageSetup();
	afx_msg void OnZoom();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
