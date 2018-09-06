// RichEditFrm.cpp : implementation file
//

#include "stdafx.h"
#include "RichEdit.h"
#include "RichEditFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CRichEditFrame

CRichEditFrame::CRichEditFrame()
{
}

CRichEditFrame::~CRichEditFrame()
{
}


BEGIN_MESSAGE_MAP(CRichEditFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CRichEditFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_FORMAT_FONT, OnFormatFont)
	ON_COMMAND(ID_PARAGRAPH_LEFT, OnParagraphLeft)
	ON_COMMAND(ID_PARAGRAPH_CENTER, OnParagraphCenter)
	ON_COMMAND(ID_PARAGRAPH_RIGHT, OnParagraphRight)
	ON_WM_SIZE()
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_COMMAND(IDM_RECT, OnRect)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRichEditFrame message handlers

int CRichEditFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
  if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
    return -1;

  CRect rect;
  GetClientRect(&rect);

  // создаем объект редактора, в дальнейшем размеры 
  // его будут мен€тьс€ в зависимости от требований 
  // уведомл€ющего сообщени€ EN_REQUESTRESIZE
  m_REditCtrl.Create(WS_CHILD | WS_VISIBLE | 
    WS_VSCROLL | ES_MULTILINE | ES_NOHIDESEL | 
    ES_SAVESEL | ES_SUNKEN, rect, this, 1000);

  // после создани€ объекта редактора 
  // добавл€ем еще два параметра
  m_REditCtrl.SetOptions(ECOOP_OR, 
    ECO_AUTOVSCROLL | ECO_AUTOHSCROLL);

  // мен€ем цвет редактора и задаем 
  // маску уведомл€ющих сообщений
  m_REditCtrl.SetBackgroundColor(FALSE, RGB(224, 224, 224));
  m_REditCtrl.SetEventMask(ENM_REQUESTRESIZE);

  m_REditCtrl.SetRect(CRect(10, 10, 10, 10));

  m_REditCtrl.SetFocus();

  return 0;
}

BOOL CRichEditFrame::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	NMHDR *nmhdr = (NMHDR *)lParam;

	if (nmhdr->hwndFrom == m_REditCtrl.m_hWnd)
	{
		if (nmhdr->code == EN_REQUESTRESIZE)
		{
			REQRESIZE *lpResize = (REQRESIZE *)lParam;

			int count = m_REditCtrl.GetLineCount();

			m_REditCtrl.MoveWindow(&lpResize->rc);
		}
	}

	return CFrameWnd::OnNotify(wParam, lParam, pResult);
}

void CRichEditFrame::OnFormatFont() 
{
	CHARFORMAT cf;
	m_REditCtrl.GetSelectionCharFormat(cf);

	CFontDialog dlg(cf);

  if (dlg.DoModal() == IDOK)
  {
		dlg.GetCharFormat(cf);

		m_REditCtrl.SetSelectionCharFormat(cf);
	}

	m_REditCtrl.SetFocus();
}

void CRichEditFrame::OnParagraphLeft() 
{
	PARAFORMAT pf;
	m_REditCtrl.GetParaFormat(pf);

	pf.wAlignment = PFA_LEFT;
	m_REditCtrl.SetParaFormat(pf);
}

void CRichEditFrame::OnParagraphCenter() 
{
	PARAFORMAT pf;
	m_REditCtrl.GetParaFormat(pf);

	pf.wAlignment = PFA_CENTER;
	m_REditCtrl.SetParaFormat(pf);
}

void CRichEditFrame::OnParagraphRight() 
{
	PARAFORMAT pf;
	m_REditCtrl.GetParaFormat(pf);

	pf.wAlignment = PFA_RIGHT;
	m_REditCtrl.SetParaFormat(pf);
}

void CRichEditFrame::OnSize(UINT nType, int cx, int cy) 
{
  CRect rect(10, 10, 10, 10);

  CFrameWnd::OnSize(nType, cx, cy);

  //m_REditCtrl.SetRect(rect);
	m_REditCtrl.MoveWindow(10, 10, cx-20, cy-20);
}

void CRichEditFrame::OnEditPaste() 
{
	m_REditCtrl.OnPaste();
}

void CRichEditFrame::OnRect() 
{
  CRect rect(10, 10, 10, 10);

  m_REditCtrl.SetRect(rect);
}
