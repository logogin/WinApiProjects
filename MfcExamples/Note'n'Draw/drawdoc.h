// DrawDoc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDrawDoc document

class CDrawDoc : public CDocument
{
protected:
	CDrawDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CDrawDoc)

// Attributes
// данные графических документов
protected:
  // параметры, используемые всеми нарисованными линиями
  int m_nWidth;
  CPen m_curPen;
	COLORREF m_curColor;

public:
  // массив указателей на объекты класса CRect, содержащего
  // координаты начальной и конечной точек рисуемой линии
  CArray<CRect*, CRect*> m_lineArray;

// Operations
public:
  void   ReplacePen();
  CRect *NewLine();
	CPen  *GetPen() {return &m_curPen;}
  
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrawDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	virtual void DeleteContents();
	protected:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
  virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDrawDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CDrawDoc)
	afx_msg void OnWidth();
	afx_msg void OnColor();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CPenDlg dialog

class CPenDlg : public CDialog
{
// Construction
public:
	CPenDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPenDlg)
	enum { IDD = IDD_PENWIDTH };
  int m_nWidth;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPenDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPenDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
