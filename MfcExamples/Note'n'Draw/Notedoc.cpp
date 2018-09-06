// NoteDoc.cpp : implementation of the CNoteDoc class
//

#include "stdafx.h"
#include "NoteDraw.h"

#include "NoteDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNoteDoc

IMPLEMENT_DYNCREATE(CNoteDoc, CDocument)

BEGIN_MESSAGE_MAP(CNoteDoc, CDocument)
	//{{AFX_MSG_MAP(CNoteDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNoteDoc construction/destruction

CNoteDoc::CNoteDoc()
{
}

CNoteDoc::~CNoteDoc()
{
}

BOOL CNoteDoc::OnNewDocument()
{
  // ��� ����������� ��������� �� �������� ���������
  // ��������� �� ���������� MFC - ��� ������ ��� ���������
  if (!CDocument::OnNewDocument())
		return FALSE;
  // ����� ��������� �������� �������� "���������"
  // ����������� ���������
  initDoc();

  return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CNoteDoc serialization

void CNoteDoc::Serialize(CArchive& ar)
{
	CNDApp *pApp = (CNDApp*)AfxGetApp();
  if (ar.IsStoring())
	{
    // ��������� ������� ������ ������
		ar << pApp->m_sizePaper;
	}
	else
	{
    // ��������������� ������� ������ ������
		ar >> pApp->m_sizePaper;
	}
  // ��� ���������� � �������������� ���������� �����������
  // ��������� �������� ������� Serialize ������ CObList,
  // �������, � ���� �������, ��������������� ��������
  // ����������� ������� ��� ������� ���������.
  // ��������� ���� ���������� ���� ��������������,
  // ����� ��������� ������ ����������� ���������
  m_listPar.Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CNoteDoc diagnostics

#ifdef _DEBUG
void CNoteDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CNoteDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CNoteDoc commands

void CNoteDoc::initDoc()
{
}

CParagraph* CNoteDoc::OnNewPar(UINT align, TCHAR *name,
                               WORD size, COLORREF color)
{
  CParagraph *pParItem = new CParagraph(align, name,
                                        size, color);
  return pParItem;
}

void CNoteDoc::DeleteContents() 
{
  // ������� ������� ������� ��������� � ������
  POSITION pos = m_listPar.GetHeadPosition();
  while(pos != NULL)
  {
    // ��������������� �������� ���� ������  
    CParagraph *pPar = m_listPar.GetNext(pos);
    // ����������� ������ ���������� ������� ����������
    // ���� ����� �� �������, �� ��� ������� ������
    // ����� ��������, ���� Windows 95 � Windows NT
    // � ����������� ������� "������" �� ����
    delete pPar;
  }
  // ������� ������ - ������ ��� "������"
  m_listPar.RemoveAll();

  // �������� ������� �������� ������ ��� ����������� ����������
	CDocument::DeleteContents();
}


/////////////////////////////////////////////////////////////////////////////
// CParagraph

// ������������ ������, �������������� ��������� ������������
IMPLEMENT_SERIAL(CParagraph, CObject, 2)

CParagraph::CParagraph(UINT align, TCHAR *name,
                       WORD size, COLORREF color)
{
  m_align     = align;
  m_color     = color;
  m_words     = "";

  LOGFONT lf;
  memset(&lf, 0, sizeof(LOGFONT));
  lf.lfHeight = size*25;
  strcpy(lf.lfFaceName, name); // (LPCTSTR)
  lf.lfCharSet   = RUSSIAN_CHARSET;
  lf.lfItalic    = FALSE;
  lf.lfUnderline = FALSE;
  lf.lfStrikeOut = FALSE;
  lf.lfWeight    = FW_NORMAL;

  m_font.CreatePointFontIndirect(&lf);
}

CParagraph::CParagraph()
{
}

void CParagraph::Serialize(CArchive& ar)
{
	LOGFONT lf;
  if (ar.IsStoring())
	{
		m_font.GetLogFont(&lf);
    
    ar << m_align;
    ar << m_color;
    ar << lf.lfCharSet;
    ar << lf.lfItalic;
    ar << lf.lfUnderline;
    ar << lf.lfStrikeOut;
    ar << lf.lfWeight;
    ar << lf.lfFaceName;
    ar << (long)(lf.lfHeight/2.3);
    ar << m_words;
	}
	else
	{
    CString tmp;
    memset(&lf, 0, sizeof(LOGFONT));
    ar >> m_align;
    ar >> m_color;
    ar >> lf.lfCharSet;
    ar >> lf.lfItalic;
    ar >> lf.lfUnderline;
    ar >> lf.lfStrikeOut;
    ar >> lf.lfWeight;
    ar >> tmp;
    strcpy(lf.lfFaceName, tmp);
    ar >> lf.lfHeight;
    lf.lfHeight = (long)(lf.lfHeight*17.55);
    ar >> m_words;

    m_font.CreatePointFontIndirect(&lf);
	}
  
}
