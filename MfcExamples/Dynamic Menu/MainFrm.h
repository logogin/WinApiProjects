// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

class CMainFrame : public CFrameWnd
{
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
	CBitmap m_bmpCheck;   // ��� ����������� ���������
  CBitmap m_bmpUnCheck; // ��� �� ����������� ���������
  // ��� �������� ������������� ����������� ����
  CMenu   m_PopupMenu;

// Operations
public:
  // �������� ������ ������������� ����������� ����
	void ChangeColorMenu();
  
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
  // �������� ��� ������� ����� �����
	virtual void ActivateFrame(int nCmdShow = -1);
  // �������������� ���������� ��������� ������
  afx_msg void OnSysCommand( UINT nID, LPARAM lParam );
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
  // ���������� ������� "������� ��� �����"	
  afx_msg void OnDeleteAll();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
