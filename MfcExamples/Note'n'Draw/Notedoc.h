// NoteDoc.h : interface of the CNoteDoc class
//
/////////////////////////////////////////////////////////////////////////////

class CParagraph : public CObject
{
protected:
	CParagraph();
  // Обязательный макрос, обеспечивающий поддержку сериализации
  DECLARE_SERIAL(CParagraph);

public:
	CParagraph(UINT align, TCHAR *name, WORD size, COLORREF color);
  void Serialize(CArchive& ar);
 
public:
	CFont    m_font;
  UINT     m_align;
  COLORREF m_color;
  CString  m_words;
};

class CNoteDoc : public CDocument
{
protected: // create from serialization only
	CNoteDoc();
	DECLARE_DYNCREATE(CNoteDoc)


// Attributes
// данные текстовых документов
public:
  // список указателей на объекты класса CParagraph,
  // содержащего параметры форматирования абзаца текста
  CTypedPtrList<CObList, CParagraph*> m_listPar;

// Operations
public:
	void initDoc();
	CParagraph* OnNewPar(UINT align, TCHAR *name = "Arial",
                       WORD size = 11, COLORREF color = 0);
 
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNoteDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void DeleteContents();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CNoteDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CNoteDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
