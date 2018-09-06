// ChildFrm.cpp : implementation of the CNoteFrame class
//

#include "stdafx.h"
#include "NoteDraw.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "NoteDoc.h"
#include "NoteView.h"
#include "DrawDoc.h"
#include "DrawView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNoteFrame

// Для возможности динамического создания объекта
// класса CNoteFrame
IMPLEMENT_DYNCREATE(CNoteFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CNoteFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CNoteFrame)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNoteFrame construction/destruction

CNoteFrame::CNoteFrame()
{
}

CNoteFrame::~CNoteFrame()
{
}

/////////////////////////////////////////////////////////////////////////////
// CNoteFrame diagnostics

#ifdef _DEBUG
void CNoteFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CNoteFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CNoteFrame message handlers

BOOL CNoteFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
  // создаем разделенное окно Windows с двумя строками и одним столбцом
  if(!m_spltWnd.CreateStatic(this, 2, 1))
  {
    TRACE0("Ошибка при создании разделенного окна\n");
    return FALSE;
  }

  // создаем представление в первой строке (горизонтальной области)
  if(!m_spltWnd.CreateView(0, 0, pContext->m_pNewViewClass,
      CSize(lpcs->cx, lpcs->cy*2/3), pContext))
  {
    TRACE0("Ошибка при создании представления для вывода\n");
    return FALSE;
  }

  // создаем представление во второй строке (горизонтальной области)
  if(!m_spltWnd.CreateView(1, 0, RUNTIME_CLASS(CTextView),
      CSize(0, 0), pContext))
  {
    TRACE0("Ошибка при создании представления для ввода\n");
    return FALSE;
  }

  // Установить фокус на область (1, 0)
  SetActiveView((CView*)m_spltWnd.GetPane(1, 0));

  return TRUE;
}

void CNoteFrame::ActivateFrame(int nCmdShow) 
{
  // Максимизируем фрейм документа
	CMDIChildWnd::ActivateFrame(SW_MAXIMIZE);
}
/////////////////////////////////////////////////////////////////////////////
// CDrawFrame

IMPLEMENT_DYNCREATE(CDrawFrame, CMDIChildWnd)

CDrawFrame::CDrawFrame()
{
}

CDrawFrame::~CDrawFrame()
{
}


BEGIN_MESSAGE_MAP(CDrawFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CDrawFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrawFrame message handlers

BOOL CDrawFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	  // создаем динамическое разделяемое окно с двумя строками
    // двумя столбцами, устанавливая некоторые начальные
    // минимальные размеры, чтобы сначала представление занимало
    // все разделяемое окно
  return m_splitWnd.Create(this, 2, 2, CSize(10, 10), pContext);
}

void CDrawFrame::ActivateFrame(int nCmdShow) 
{
	CMDIChildWnd::ActivateFrame(SW_MAXIMIZE);
}

