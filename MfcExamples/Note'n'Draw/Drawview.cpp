// DrawView.cpp : implementation file
//

#include "stdafx.h"
#include "NoteDraw.h"

#include "DrawDoc.h"
#include "DrawView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDrawView

IMPLEMENT_DYNCREATE(CDrawView, CScrollView)

CDrawView::CDrawView()
{
}

CDrawView::~CDrawView()
{
}

BEGIN_MESSAGE_MAP(CDrawView, CScrollView)
	//{{AFX_MSG_MAP(CDrawView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
	ON_COMMAND(ID_ZOOM, OnZoom)
	//}}AFX_MSG_MAP
  ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
//	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrawView drawing

void CDrawView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
  
  CRect rect;
  GetClientRect(rect);

  GetParentFrame()->RecalcLayout();  	
  SetScaleToFitSize(CSize(rect.right, rect.bottom));
}

void CDrawView::OnDraw(CDC* pDC)
{
	CRect *pLine;
  // Поскольку отобразить нужно данные документа,
  // то получаем указатель на него
  CDrawDoc *pDoc = (CDrawDoc*)GetDocument();
  
  // Мы могли нарисовать несколько объектов,
  // и все их нужно вывести на экран, поэтому организуем цикл
  for(int i = 0; i< pDoc->m_lineArray.GetSize(); i++)
  {
    // получаем координаты текущей линии
    pLine = pDoc->m_lineArray[i];
    // выбираем в контекст устройства, которым может быть
    // как экран, так и принтер, текущий карандаш
    CPen *pOld = pDC->SelectObject(pDoc->GetPen());
    // выводим текущую линию на экран
    pDC->MoveTo(pLine->left,  pLine->top);
    pDC->LineTo(pLine->right, pLine->bottom);
    // восстанавливаем параметры "старого" карандаша,    
    pDC->SelectObject(pOld);
  }
	
}

/////////////////////////////////////////////////////////////////////////////
// CDrawView diagnostics

#ifdef _DEBUG
void CDrawView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CDrawView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDrawView message handlers

void CDrawView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CClientDC dc(this);
  OnPrepareDC(&dc);
  dc.DPtoLP(&point);

  CDrawDoc *pDoc = (CDrawDoc*)GetDocument();
  m_pLineCur = pDoc->NewLine();

  m_pLineCur->left    = point.x;
  m_pLineCur->top     = point.y;
  m_pLineCur->right   = point.x;
  m_pLineCur->bottom  = point.y;
		
  SetCapture();
  pDoc->SetModifiedFlag();
}

void CDrawView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if(GetCapture() != this)
    return;

  CDrawDoc *pDoc = (CDrawDoc *)GetDocument();

  CClientDC dc(this);
  OnPrepareDC(&dc);
  dc.DPtoLP(&point);

  m_pLineCur->right   = point.x;
  m_pLineCur->bottom  = point.y;

  
	pDoc->UpdateAllViews(NULL);
  ReleaseCapture();
}


void CDrawView::OnMouseMove(UINT nFlags, CPoint point) 
{
	if(GetCapture() != this)
    return;

  CPen penLine;
  if(!penLine.CreatePen(PS_DOT, 1, RGB(0, 0, 255)))
    return;
	
  CDrawDoc *pDoc = (CDrawDoc *)GetDocument();

  CClientDC dc(this);
  OnPrepareDC(&dc);
  dc.DPtoLP(&point);

  CPen *pOld = dc.SelectObject(&penLine);
  dc.SetROP2(R2_NOTXORPEN);
  dc.MoveTo(m_pLineCur->left,  m_pLineCur->top);
  dc.LineTo(m_pLineCur->right, m_pLineCur->bottom);
  
  m_pLineCur->right   = point.x;
  m_pLineCur->bottom  = point.y;
 
  dc.MoveTo(m_pLineCur->left,  m_pLineCur->top);
  dc.LineTo(m_pLineCur->right, m_pLineCur->bottom);
  
	dc.SelectObject(pOld);
}

BOOL CDrawView::OnPreparePrinting(CPrintInfo* pInfo) 
{
  pInfo->SetMaxPage(2);
	return DoPreparePrinting(pInfo);
}


void CDrawView::OnFilePrintPreview() 
{
  // при переопределении функции CView::OnFilePrintPreview
  // необходимо самому создать структуру для сохранения
  // текущего состояния фрейма
  CPrintPreviewState* pState = new CPrintPreviewState;

  // обязательный вызов, в котором задаем идентификатор
  // блока диалога для отображаемой панели инструментов
  if (!DoPrintPreview(IDD_PREVIEW, this,
                      RUNTIME_CLASS(CPreviewView), pState))
  {
    // для отображения в окне отладки
    TRACE0("Ошибка: DoPrintPreview отработала неправильно.\n");
    // для отображения на экране
    AfxMessageBox(AFX_IDP_COMMAND_FAILURE);
    delete pState;
  }
}

void CDrawView::OnZoom() 
{
		ResizeParentToFit();
	
}
