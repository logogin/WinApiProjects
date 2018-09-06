// MfcIEDoc.cpp : implementation of the CMfcIEDoc class
//

#include "stdafx.h"
#include "MfcIE.h"

#include "MfcIEDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMfcIEDoc

IMPLEMENT_DYNCREATE(CMfcIEDoc, CDocument)

BEGIN_MESSAGE_MAP(CMfcIEDoc, CDocument)
	//{{AFX_MSG_MAP(CMfcIEDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMfcIEDoc construction/destruction

CMfcIEDoc::CMfcIEDoc()
{
	// TODO: add one-time construction code here

}

CMfcIEDoc::~CMfcIEDoc()
{
}

BOOL CMfcIEDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMfcIEDoc serialization

void CMfcIEDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMfcIEDoc diagnostics

#ifdef _DEBUG
void CMfcIEDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMfcIEDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMfcIEDoc commands
