// DynMenuDoc.h : interface of the CDynMenuDoc class
//
/////////////////////////////////////////////////////////////////////////////

// максимально разрешенное число элементов выпадающего меню
#define NUM_COLOR 8

struct MenuColor
{
  int      m_pos; // порядковый номер в меню
  UINT     m_nID; // идентификатор меню
  COLORREF m_clr; // цвет
  BOOL     m_btr;
};

class CDynMenuDoc : public CDocument
{
protected: // create from serialization only
	CDynMenuDoc();
	DECLARE_DYNCREATE(CDynMenuDoc)

// Attributes
public:
	BOOL bDelete;  // удаляем или вставляем элемент в меню
	
  int       m_icolor; // текущий цвет
  static MenuColor m_aColor[NUM_COLOR]; // массив элементов меню

// Operations
public:
  // обработчик команды обновления интерфейса пользователя
 	void DoUpdateSelectColor(int iColor, CCmdUI*pCmdUI);
  // дополнение к обработчику команды ID_COLOR для добавления
  // элемента в меню
	void DoSelectColor(int iColor);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDynMenuDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDynMenuDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDynMenuDoc)
  // обработчик команды ID_COLOR для добавления элемента в меню
  afx_msg void OnAddColor();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
