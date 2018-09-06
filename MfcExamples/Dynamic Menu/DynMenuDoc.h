// DynMenuDoc.h : interface of the CDynMenuDoc class
//
/////////////////////////////////////////////////////////////////////////////

// ����������� ����������� ����� ��������� ����������� ����
#define NUM_COLOR 8

struct MenuColor
{
  int      m_pos; // ���������� ����� � ����
  UINT     m_nID; // ������������� ����
  COLORREF m_clr; // ����
  BOOL     m_btr;
};

class CDynMenuDoc : public CDocument
{
protected: // create from serialization only
	CDynMenuDoc();
	DECLARE_DYNCREATE(CDynMenuDoc)

// Attributes
public:
	BOOL bDelete;  // ������� ��� ��������� ������� � ����
	
  int       m_icolor; // ������� ����
  static MenuColor m_aColor[NUM_COLOR]; // ������ ��������� ����

// Operations
public:
  // ���������� ������� ���������� ���������� ������������
 	void DoUpdateSelectColor(int iColor, CCmdUI*pCmdUI);
  // ���������� � ����������� ������� ID_COLOR ��� ����������
  // �������� � ����
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
  // ���������� ������� ID_COLOR ��� ���������� �������� � ����
  afx_msg void OnAddColor();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
