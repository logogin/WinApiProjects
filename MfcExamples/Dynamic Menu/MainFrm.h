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
	CBitmap m_bmpCheck;   // для отмеченного состояния
  CBitmap m_bmpUnCheck; // для не отмеченного состояния
  // для создания динамического выпадающего меню
  CMenu   m_PopupMenu;

// Operations
public:
  // изменяет состав динамического выпадающего меню
	void ChangeColorMenu();
  
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
  // изменять вид маркера будем здесь
	virtual void ActivateFrame(int nCmdShow = -1);
  // переопределяем обработчик системных команд
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
  // Обработчик команды "Удалить все цвета"	
  afx_msg void OnDeleteAll();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
