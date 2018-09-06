// LoadResDoc.cpp : implementation of the CLoadResDoc class
//

#include "stdafx.h"
#include "LoadRes.h"

#include "LoadResDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLoadResDoc

IMPLEMENT_DYNCREATE(CLoadResDoc, CDocument)

BEGIN_MESSAGE_MAP(CLoadResDoc, CDocument)
	//{{AFX_MSG_MAP(CLoadResDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoadResDoc construction/destruction

CLoadResDoc::CLoadResDoc()
{
	// TODO: add one-time construction code here

}

CLoadResDoc::~CLoadResDoc()
{
}

BOOL CLoadResDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	((CEditView*)m_viewList.GetHead())->SetWindowText(NULL);

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CLoadResDoc serialization

void CLoadResDoc::Serialize(CArchive& ar)
{
	// CEditView contains an edit control which handles all serialization
	((CEditView*)m_viewList.GetHead())->SerializeRaw(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CLoadResDoc diagnostics

#ifdef _DEBUG
void CLoadResDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CLoadResDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLoadResDoc commands
