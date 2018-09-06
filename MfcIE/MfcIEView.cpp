// MfcIEView.cpp : implementation of the CMfcIEView class
//

#include "stdafx.h"
#include "MfcIE.h"
#include "MainFrm.h"

#include "MfcIEDoc.h"
#include "MfcIEView.h"
#include "PostDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMfcIEView

IMPLEMENT_DYNCREATE(CMfcIEView, CHtmlView)

BEGIN_MESSAGE_MAP(CMfcIEView, CHtmlView)
	//{{AFX_MSG_MAP(CMfcIEView)
	ON_COMMAND(ID_VIEW_STARTREFRESH, OnViewStartrefresh)
	ON_COMMAND(ID_VIEW_POSTDATA, OnViewPostdata)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMfcIEView construction/destruction

CMfcIEView::CMfcIEView()
{
	// TODO: add construction code here

}

CMfcIEView::~CMfcIEView()
{
}

BOOL CMfcIEView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CHtmlView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMfcIEView drawing

void CMfcIEView::OnDraw(CDC* pDC)
{
	CMfcIEDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

void CMfcIEView::OnInitialUpdate()
{
	CHtmlView::OnInitialUpdate();

	// TODO: This code navigates to a popular spot on the web.
	//  change the code to go where you'd like.
/*	m_bStart=FALSE;
	m_bPost=FALSE;*/
	m_bStart=TRUE;
	Navigate2(_T("http://tcblib.tcb.ac.il:4330/ALEPH/HEB/TCB/TCB/TCB/BOR-RENEW-ALL/321478026/321478026"),NULL,NULL);
}

/////////////////////////////////////////////////////////////////////////////
// CMfcIEView diagnostics

#ifdef _DEBUG
void CMfcIEView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CMfcIEView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}

CMfcIEDoc* CMfcIEView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMfcIEDoc)));
	return (CMfcIEDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMfcIEView message handlers

void CMfcIEView::OnBeforeNavigate2(LPCTSTR lpszURL, 
								   DWORD nFlags, 
								   LPCTSTR lpszTargetFrameName, 
								   CByteArray& baPostedData, 
								   LPCTSTR lpszHeaders, 
								   BOOL* pbCancel) 
{
	// TODO: Add your specialized code here and/or call the base class
//	((CMainFrame*)GetParentFrame())->StartAnimation();
//	if (m_bPost)
//	{
//		*pbCancel=TRUE;
//		CPostDlg PostDlg;
//		PostDlg.DoModal();
//		CString strData=PostDlg.GetPostData();
//		baPostedData.RemoveAll();
//		for (UINT i=0; i<strData.GetLength(); i++)
//			baPostedData.Add(strData.GetAt(i));
//		Navigate2(lpszURL,nFlags,baPostedData,NULL,lpszHeaders);
//	}
	CHtmlView::OnBeforeNavigate2(lpszURL,nFlags,lpszTargetFrameName,baPostedData,lpszHeaders,pbCancel);
}

void CMfcIEView::OnDocumentComplete(LPCTSTR lpszURL) 
{
	// TODO: Add your specialized code here and/or call the base class
	((CMainFrame*)GetParentFrame())->SetAddress(lpszURL);
//	LPDISPATCH pDispatch=GetHtmlDocument();
//	if (pDispatch!=NULL)
//	{
//		m_CHtmlDoc.SetHtmlDocument(pDispatch);
//		IHTMLElement *pElement;
//		if ((pElement=m_CHtmlDoc.FindElementByName(_T("id"),0))!=NULL)
//			m_CHtmlDoc.SetInputTextValue(_T("id"),_T("321478026"));
//		if ((pElement=m_CHtmlDoc.FindElementByName(_T("password"),0))!=NULL)
//			m_CHtmlDoc.SetInputTextValue(_T("id"),_T("6zy5ht"));
//		if ((pElement=m_CHtmlDoc.FindElementByName(_T("Submit1"),0))!=NULL)
//			m_CHtmlDoc.ClickInput(pElement);
//	}
	if (m_bStart)
		SetTimer(1,10000,NULL);
	//CHtmlView::OnDocumentComplete(lpszURL);
}

void CMfcIEView::OnViewStartrefresh() 
{
	// TODO: Add your command handler code here
	if (!m_bStart)
	{
		m_bStart=TRUE;
		SetTimer(1,10000,NULL);
		(((CMainFrame *)GetParentFrame())->GetMenu())->CheckMenuItem(ID_VIEW_STARTREFRESH,
			MF_BYCOMMAND | MF_CHECKED);
	}
	else
	{
		m_bStart=FALSE;
		KillTimer(1);
		(((CMainFrame *)GetParentFrame())->GetMenu())->CheckMenuItem(ID_VIEW_STARTREFRESH,
			MF_BYCOMMAND | MF_UNCHECKED);
	}
}

void CMfcIEView::OnViewPostdata() 
{
	// TODO: Add your command handler code here
	if (!m_bPost)
	{
		m_bPost=TRUE;
		(((CMainFrame *)GetParentFrame())->GetMenu())->CheckMenuItem(ID_VIEW_POSTDATA,
			MF_BYCOMMAND | MF_CHECKED);
	}
	else
	{
		m_bPost=FALSE;
		KillTimer(1);
		(((CMainFrame *)GetParentFrame())->GetMenu())->CheckMenuItem(ID_VIEW_POSTDATA,
			MF_BYCOMMAND | MF_UNCHECKED);
	}
}

void CMfcIEView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
//	KillTimer(1);
	Navigate2(_T("http://tcblib.tcb.ac.il:4330/ALEPH/HEB/TCB/TCB/TCB/BOR-RENEW-ALL/321478026/321478026"),NULL,NULL);
	Refresh();
	CHtmlView::OnTimer(nIDEvent);
}
