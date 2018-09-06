// LoadResView.cpp : implementation of the CLoadResView class
//

#include "stdafx.h"
#include "LoadRes.h"

#include "LoadResDoc.h"
#include "LoadResView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLoadResView

IMPLEMENT_DYNCREATE(CLoadResView, CEditView)

BEGIN_MESSAGE_MAP(CLoadResView, CEditView)
	//{{AFX_MSG_MAP(CLoadResView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoadResView construction/destruction

CLoadResView::CLoadResView()
{
	// TODO: add construction code here

}

CLoadResView::~CLoadResView()
{
}

BOOL CLoadResView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// Enable word-wrapping

	return bPreCreated;
}

/////////////////////////////////////////////////////////////////////////////
// CLoadResView drawing

void CLoadResView::OnDraw(CDC* pDC)
{
	CLoadResDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CLoadResView diagnostics

#ifdef _DEBUG
void CLoadResView::AssertValid() const
{
	CEditView::AssertValid();
}

void CLoadResView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CLoadResDoc* CLoadResView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLoadResDoc)));
	return (CLoadResDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLoadResView message handlers

void CLoadResView::OnInitialUpdate() 
{
	CEditView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	HMODULE hExe = LoadLibrary(_T("Debug/LoadRes.exe")); 
	if (hExe == NULL) 
	{
		AfxMessageBox(_T("Could not load exe."));
		return;
	}
	CString  sName=_T("#132");
	LPCTSTR lpsName=(char *)IDR_RT_TXT1;
	HRSRC hRes = FindResource(/*hExe*/NULL,/*sName*/lpsName,_T("RT_TXT")); 
	if (hRes == NULL) 
	{
		AfxMessageBox(_T("Could not locate resource.")); 
		return;
	}

	HGLOBAL hResLoad = LoadResource(hExe, hRes); 
	if (hResLoad == NULL) 
	{ 
		AfxMessageBox("Could not load resource."); 
	} 
	LPVOID lpvData=LockResource(hResLoad);
	CEdit &Edit=GetEditCtrl();
	Edit.SetWindowText((LPSTR) lpvData);
}
