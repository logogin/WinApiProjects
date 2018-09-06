// DynMenuView.h : interface of the CDynMenuView class
//
/////////////////////////////////////////////////////////////////////////////

// ��� ���������� ������ ��������������� �������� ���� ����������
// ������� ���� ����� �� ���� CMenu
class CColorMenu : public CMenu
{
public:
	CColorMenu(){}

// Implementation
  // �������������� ����������� ����������� �������
  virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMIS);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDIS);
};

class CDynMenuView : public CView
{
protected: // create from serialization only
	CDynMenuView();
	DECLARE_DYNCREATE(CDynMenuView)

// Attributes
public:
	CDynMenuDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDynMenuView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
  // ��� ��������� � ����������� ������� ������
  // ��� ���������� � �������� ��������� ����
  virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDynMenuView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDynMenuView)
  
  // ���������� ��� �������� ������������ ����
  afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DynMenuView.cpp
inline CDynMenuDoc* CDynMenuView::GetDocument()
   { return (CDynMenuDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
