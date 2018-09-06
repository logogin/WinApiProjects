// DynMenuDoc.cpp : implementation of the CDynMenuDoc class
//

#include "stdafx.h"
#include "DynMenu.h"

#include "MainFrm.h"
#include "DynMenuDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDynMenuDoc

// инициализация массива цветов: исходно все недоступны
MenuColor CDynMenuDoc::m_aColor[NUM_COLOR] =
{
  {0, ID_COLOR0,  RGB(255, 128, 128), FALSE},
  {0, ID_COLOR1,  RGB(255, 255, 128), FALSE},
  {0, ID_COLOR2,  RGB(128, 255, 128), FALSE},
  {0, ID_COLOR3,  RGB(0,   255, 128), FALSE},
  {0, ID_COLOR4,  RGB(128, 255, 255), FALSE},
  {0, ID_COLOR5,  RGB(0,   128, 255), FALSE},
  {0, ID_COLOR6,  RGB(255, 128, 192), FALSE},
  {0, ID_COLOR7,  RGB(255, 128, 255), FALSE}
};

IMPLEMENT_DYNCREATE(CDynMenuDoc, CDocument)

BEGIN_MESSAGE_MAP(CDynMenuDoc, CDocument)
	//{{AFX_MSG_MAP(CDynMenuDoc)
	ON_COMMAND(ID_ADD_COLOR, OnAddColor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDynMenuDoc construction/destruction

CDynMenuDoc::CDynMenuDoc()
{
  m_icolor = -1;
  bDelete  = FALSE;
}

CDynMenuDoc::~CDynMenuDoc()
{
}

BOOL CDynMenuDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CDynMenuDoc serialization

void CDynMenuDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDynMenuDoc diagnostics

#ifdef _DEBUG
void CDynMenuDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDynMenuDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDynMenuDoc commands

void CDynMenuDoc::OnAddColor() 
{
  // настраиваем стандартный блок диалога Color (Цвет)
  CColorDialog dlg;
  dlg.m_cc.Flags |= CC_PREVENTFULLOPEN;

	if(dlg.DoModal() == IDOK)
  {
    // получаем выбранный цвет
    COLORREF color = dlg.GetColor();
    // если его еще нет в списке доступных цветов,
    // то добавляем его туда
    for(int i = 0; i < NUM_COLOR; i++)
    {
      if(color == m_aColor[i].m_clr)
      {
         m_aColor[i].m_btr = TRUE;
         m_icolor = i;
         break;
      }
    }
    // получаем доступ к текущему представлению
    POSITION pos = GetFirstViewPosition();
		CView* pview = GetNextView(pos);
		ASSERT(pview != NULL);

    // получаем доступ к активному фрейму		
    CMainFrame* pwnd = (CMainFrame*)pview->GetParentFrame();
		ASSERT_KINDOF(CMainFrame, pwnd);

    // обновляем состав доступных цветов
		pwnd->ChangeColorMenu();
    // обновляем изображение
    UpdateAllViews(NULL);
  }
}

void CDynMenuDoc::DoSelectColor(int iColor)
{
	ASSERT(iColor >= 0 && iColor < NUM_COLOR);
	ASSERT(m_aColor[iColor].m_btr == TRUE);

	m_icolor = iColor;
	UpdateAllViews(NULL);
}

void CDynMenuDoc::DoUpdateSelectColor(int iColor, CCmdUI*pCmdUI)
{
  ASSERT(iColor >= 0 && iColor < NUM_COLOR);
	ASSERT(m_aColor[iColor].m_btr == TRUE);

	pCmdUI->SetCheck(m_icolor == iColor);
	pCmdUI->Enable(TRUE);
}

