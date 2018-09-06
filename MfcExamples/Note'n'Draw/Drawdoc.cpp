// DrawDoc.cpp : implementation file
//

#include "stdafx.h"
#include "NoteDraw.h"
#include "DrawDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDrawDoc

IMPLEMENT_DYNCREATE(CDrawDoc, CDocument)

CDrawDoc::CDrawDoc()
{
  m_nWidth   = 2;
  m_curColor = RGB(0, 0, 0);
}

BOOL CDrawDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	ReplacePen();
  return TRUE;
}

BOOL CDrawDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	ReplacePen();
	return TRUE;
}

CDrawDoc::~CDrawDoc()
{
}


BEGIN_MESSAGE_MAP(CDrawDoc, CDocument)
	//{{AFX_MSG_MAP(CDrawDoc)
	ON_COMMAND(ID_WIDTH, OnWidth)
	ON_COMMAND(ID_COLOR, OnColor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrawDoc diagnostics

#ifdef _DEBUG
void CDrawDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDrawDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDrawDoc serialization

void CDrawDoc::Serialize(CArchive& ar)
{
  // действия относящиеся и к загрузке и к сохранению архива
  CRect *pRect;
  int i, nCount;
  if (ar.IsStoring())
	{
		nCount = m_lineArray.GetSize();
    ar << nCount;
    ar << m_nWidth;
    ar << m_curColor;
    for(i = 0; i< nCount; i++)
    {
      pRect = m_lineArray[i];
      ar << *pRect;
    }
	}
	else
	{
		ar >> nCount;
    ar >> m_nWidth;
    ar >> m_curColor;
    for(i = 0; i< nCount; i++)
    {
      pRect = NewLine();
      ar >> *pRect;
    }
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDrawDoc commands

CRect* CDrawDoc::NewLine()
{
  CRect *pLineItem = new CRect;
  m_lineArray.Add(pLineItem);
  return pLineItem;
}

void CDrawDoc::DeleteContents() 
{
	int nCount = m_lineArray.GetSize();
  for(int i = 0; i< nCount; i++)
  {
    delete m_lineArray[i];
  }
  m_lineArray.RemoveAll();
  CDocument::DeleteContents();
}

void CDrawDoc::OnWidth() 
{
	CPenDlg dlg;
  dlg.m_nWidth = m_nWidth;
	if(dlg.DoModal() == IDOK)
  {
    m_nWidth = dlg.m_nWidth;
    ReplacePen();
    UpdateAllViews(NULL);
  }
}

void CDrawDoc::OnColor() 
{
	CColorDialog dlg;
  dlg.m_cc.rgbResult = m_curColor;
  if(dlg.DoModal() == IDOK)
  {
    m_curColor = dlg.m_cc.rgbResult;
    ReplacePen();
    UpdateAllViews(NULL);
  }
	
}

void CDrawDoc::ReplacePen()
{
  m_curPen.DeleteObject();
  m_curPen.CreatePen(PS_SOLID, m_nWidth, m_curColor);
}

/*void CDrawDoc::InitDoc()
{
 m_nWidth   = 2;
 m_curColor = RGB(0, 0, 0);
 ReplacePen();
}
*/

/////////////////////////////////////////////////////////////////////////////
// CPenDlg dialog

CPenDlg::CPenDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPenDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPenDlg)
	m_nWidth = 2;
	//}}AFX_DATA_INIT
}

void CPenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPenDlg)
  DDX_Text(pDX, IDC_WIDTH, m_nWidth);
  DDV_MinMaxInt(pDX, m_nWidth, 1, 10);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPenDlg, CDialog)
	//{{AFX_MSG_MAP(CPenDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPenDlg message handlers
