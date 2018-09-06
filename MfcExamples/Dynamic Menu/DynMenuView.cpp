// DynMenuView.cpp : implementation of the CDynMenuView class
//

#include "stdafx.h"
#include "DynMenu.h"

#include "MainFrm.h"
#include "DynMenuDoc.h"
#include "DynMenuView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// ������� ��� �������� ���� � ������ ���������������
#define COLOR_BOX_WIDTH     30
#define COLOR_BOX_HEIGHT    20

/////////////////////////////////////////////////////////////////////////////
// CDynMenuView

IMPLEMENT_DYNCREATE(CDynMenuView, CView)

BEGIN_MESSAGE_MAP(CDynMenuView, CView)
	//{{AFX_MSG_MAP(CDynMenuView)
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDynMenuView construction/destruction

CDynMenuView::CDynMenuView()
{
}

CDynMenuView::~CDynMenuView()
{
}

BOOL CDynMenuView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDynMenuView drawing

void CDynMenuView::OnDraw(CDC* pDC)
{
	CDynMenuDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDC->SetTextColor(pDoc->m_aColor[pDoc->m_icolor].m_clr);
	pDC->SetBkMode(TRANSPARENT);

	// output a string to the center of the client area
	CRect rc;
	GetClientRect(rc);
	pDC->DrawText(_T("��������� ������ � ����������� �������������� ����"), -1,
				  rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

}

/////////////////////////////////////////////////////////////////////////////
// CDynMenuView diagnostics

#ifdef _DEBUG
void CDynMenuView::AssertValid() const
{
	CView::AssertValid();
}

void CDynMenuView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDynMenuDoc* CDynMenuView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDynMenuDoc)));
	return (CDynMenuDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDynMenuView message handlers


void CDynMenuView::OnRButtonDown(UINT nFlags, CPoint point) 
{
  CDynMenuDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

  CColorMenu Menu;
  // ����������� ���� ������������� ������������ ������ - �����
  // ������������� ��������� ������� ���� � �������� ����������
  ClientToScreen(&point);

  // ������� ���������� ���� 
  Menu.CreatePopupMenu();
  for (int i = 0; i < NUM_COLOR; i++)
	{
    if (pDoc->m_aColor[i].m_btr == TRUE)
		{
		  TCHAR strColor[64];
      sprintf(strColor, "Color %d", i);
		  Menu.AppendMenu(MF_OWNERDRAW, pDoc->m_aColor[i].m_nID,
                      (char*)pDoc->m_aColor[i].m_clr);
    }
	}
  // ��� ������ ����� ���� ����� ������� ��������  
  pDoc->bDelete = TRUE;
  // ������� ����������� ���� �� �����
	Menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,point.x,point.y,this);
  
  // ��� ������ �� ������ ���������� ������	
  CView::OnRButtonDown(nFlags, point);
}

// ��������� ������������ ������� �� ����������������,
// ���������� � ����������� ������� ������ ��� ���������
BOOL CDynMenuView::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	CDynMenuDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

  // If pHandlerInfo is NULL, then handle the message
	if (pHandlerInfo == NULL)
	{
    // ���������� ������ ��� ��������� ������ �������
		for (int i = NUM_COLOR-1; i >= 0; i--)
		{
			if (nID == pDoc->m_aColor[i].m_nID)
			{
				if (nCode == CN_COMMAND)
				{
          // ������������ ������������� �������
          
          // ��������� ��������� ��� �������� �������� � ��� �������
          if(pDoc->bDelete)
          {
            pDoc->bDelete = FALSE;
            pDoc->m_aColor[i].m_btr = FALSE;
          }
          else
            pDoc->DoSelectColor(i);

          // �������� ������ � ������
          CMainFrame* pwnd = (CMainFrame*)GetParentFrame();
		      ASSERT_KINDOF(CMainFrame, pwnd);

	        // ��� ���������� ������� ����������� ����
		      pwnd->ChangeColorMenu();
          pDoc->UpdateAllViews(NULL);
				}
				else if (nCode == CN_UPDATE_COMMAND_UI)
				{
          // ��������� ��������� ��������� ����
					pDoc->DoUpdateSelectColor(i, (CCmdUI*)pExtra);
				}
				return TRUE;
			}
		}
	}
  
  // �� �������� ������� ���������� � ����������� ������� ������    
  return CView::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void CColorMenu::MeasureItem(LPMEASUREITEMSTRUCT lpMIS)
{
  // ��� �������� ������ �������, ��,
  // ��� �������, ����� ������� � ������
  lpMIS->itemWidth = COLOR_BOX_WIDTH;
	lpMIS->itemHeight = COLOR_BOX_HEIGHT;
}

void CColorMenu::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
  // ��� ������ ������������ ������ ����� �������� ����������
  CDC* pDC = CDC::FromHandle(lpDIS->hDC);
	
  COLORREF cr = (COLORREF)lpDIS->itemData; // RGB in item data

	if (lpDIS->itemAction & ODA_DRAWENTIRE)
	{
    // ������ ������� ����
		CBrush br(cr);
		pDC->FillRect(&lpDIS->rcItem, &br);
	}

	if ((lpDIS->itemState & ODS_SELECTED) &&
		(lpDIS->itemAction & (ODA_SELECT | ODA_DRAWENTIRE)))
	{
    // ������� ������� �������� ������
		COLORREF crHilite = RGB(255-GetRValue(cr),
						255-GetGValue(cr), 255-GetBValue(cr));
		CBrush br(crHilite);
		pDC->FrameRect(&lpDIS->rcItem, &br);
	}

	if (!(lpDIS->itemState & ODS_SELECTED) &&
		(lpDIS->itemAction & ODA_SELECT))
	{
    // �� ���������� ������� - ��� �����
		CBrush br(cr);
		pDC->FrameRect(&lpDIS->rcItem, &br);
	}
}
