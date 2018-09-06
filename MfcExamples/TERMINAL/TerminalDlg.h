/*************************************************************
Файл TerminalDlg.h
Copyright (c) 1999 Мешков А., Тихомиров Ю.
*************************************************************/

// TerminalDlg.h : header file
//

#include "TermWnd.h"
#include "Modem.h"

/////////////////////////////////////////////////////////////////////////////
// CTerminalDlg dialog

class CTerminalDlg : public CDialog
{
	DECLARE_DYNAMIC(CTerminalDlg)

// Construction
public:
	CTerminalDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTerminalDlg)
	enum { IDD = IDD_TERMINAL_DIALOG };
	CTermWnd m_Terminal;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTerminalDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTerminalDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	afx_msg void OnCom1();
	afx_msg void OnCom2();
	afx_msg void OnCom3();
	afx_msg void OnCom4();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Operations
private:
	void Initialize(LPCTSTR lpCommPort); 
	void UnInitialize();

// Data
public:
  CModem m_Modem;

	CWinThread *m_pOutThread;
	CWinThread *m_pInThread;
	CWinThread *m_pDrawThread;

	CEvent m_Quit;
};
