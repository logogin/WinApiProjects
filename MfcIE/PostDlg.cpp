// PostDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MfcIE.h"
#include "PostDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPostDlg dialog


CPostDlg::CPostDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPostDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPostDlg)
	m_strData = _T("");
	//}}AFX_DATA_INIT
}


void CPostDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPostDlg)
	DDX_Text(pDX, IDC_EDIT_DATA, m_strData);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPostDlg, CDialog)
	//{{AFX_MSG_MAP(CPostDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPostDlg message handlers

void CPostDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	m_strPostData=m_strData;
	CDialog::OnOK();
}

void CPostDlg::SetPostData(const CString &strData)
{
	m_strPostData=strData;
}

CString CPostDlg::GetPostData()
{
	return m_strPostData;
}

BOOL CPostDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_strData=m_strPostData;
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
