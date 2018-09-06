/////////////////////////////////////////////////////////
// Файл TempDlg.h
// Copyright (c) 1997 Мешков А., Тихомиров Ю.
/////////////////////////////////////////////////////////

// Описания классов CItem, CMemory и TemplateDlg
//

/////////////////////////////////////////////////////////////////////////////
// Класс CItem для элементов управления

class CItem{
public:
	DLGITEMTEMPLATE  m_ctrItem;

	enum			ctrtype {EDITTEXT = 0x0081, STATICTEXT};
	ctrtype		m_ctrtype;
	CString		m_strTitle;

public:
	CItem(enum ctrtype cType);
	CItem() {};

	void Initialize(enum ctrtype cType, UINT nID, CRect* prect = NULL, LPCTSTR pszCaption = NULL);
};

/////////////////////////////////////////////////////////////////////////////
// Класс CMemory для шаблона блока диалога

class CMemory{
public:
	DLGTEMPLATE m_dlgMemory;
	CItem	m_dlgItem[2]; // в шаблоне будет 2 элемента

	CMemory();
	void Show();
};

/////////////////////////////////////////////////////////////////////////////
// CTemplateDlg dialog

class CTemplateDlg : public CDialog{
public:
	CTemplateDlg(CWnd* pParent = NULL);

// Dialog Data
	//{{AFX_DATA(CTemplateDlg)
 	enum { IDD = IDD_TEMPLATE_DIALOG };
	 CString	m_strTitle;
	 UINT	m_x;
	 UINT	m_y;
	 UINT	m_nWidth;
	 UINT	m_nHeight;
	 int		m_nItem;
  CString m_strItem;
	//}}AFX_DATA

  int m_nActiveItem;
  CMemory m_dlgTemplate;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTemplateDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

 void InfoToDialog(int nItem, LPCTSTR lpszItem);

	// Generated message map functions
	//{{AFX_MSG(CTemplateDlg)
	virtual BOOL OnInitDialog();
 afx_msg void OnShow();
 afx_msg void OnEdit();
 afx_msg void OnStatic();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
