/*************************************************************
���� VListBox.cpp
Copyright (c) 1999 ������ �., ��������� �.
*************************************************************/

// VListBox.cpp : implementation file
//

#include "stdafx.h"
#include "LBSmpl.h"
#include "VListBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// ����������� �������� ���������� 
// ����������� � �������� ������
#define FRAME  2

//////////////////////////////////////////////////////////////////// CVListBox

CVListBox::CVListBox()
{
}

CVListBox::~CVListBox()
{
}


BEGIN_MESSAGE_MAP(CVListBox, CListBox)
  //{{AFX_MSG_MAP(CVListBox)
    // NOTE - the ClassWizard will add and 
    //        remove mapping macros here.
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////// CVListBox message handlers

void CVListBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
  CDC dc;
  dc.Attach(lpDrawItemStruct->hDC);

  CRect rect = lpDrawItemStruct->rcItem;

  // �������� ��� ������ ������ (32 - ������ �����������)
  rect.left += 32 + FRAME + FRAME;

  // ��������� ��������� ������ ������� ������ ������
  int nHeight = dc.DrawText((LPCTSTR)lpDrawItemStruct->itemData, 
    rect, DT_CALCRECT | DT_LEFT | DT_WORDBREAK) + FRAME + FRAME;

  rect.bottom = rect.top + nHeight;

  if (nHeight < 32 + FRAME + FRAME)
    rect.bottom = rect.top + 32 + FRAME + FRAME;

  // �������� ������ �������� ����������
  SetItemHeight(lpDrawItemStruct->itemID, rect.Height());

  // ���� ��������� ���������� �������� ��������������
  lpDrawItemStruct->rcItem.bottom = rect.bottom;
  rect = lpDrawItemStruct->rcItem;

  // ���������� ��������� �������� ������
  if (lpDrawItemStruct->itemState & ODS_SELECTED)
  {
    // ������ ���������� "������"
    dc.DrawFrameControl(&rect, DFC_BUTTON, 
      DFCS_BUTTONPUSH | DFCS_PUSHED);
  }
  else
  {
    // ������ �������� "������"
    dc.DrawFrameControl(&rect, DFC_BUTTON, DFCS_BUTTONPUSH);
  }

  // ������ �����������, ���������� �� �� ���������
  rect.top += (rect.Height() - 32) / 2;
  dc.DrawIcon(rect.left+FRAME, rect.top, 
    AfxGetApp()->LoadIcon(IDR_MAINFRAME));

  rect = lpDrawItemStruct->rcItem;
  rect.left += 32 + FRAME;

  rect.DeflateRect(FRAME, FRAME);
  rect.top += (rect.Height() - (nHeight - FRAME)) / 2;

  // ������� ����� �������� ����������
  dc.SetBkMode(TRANSPARENT);
  dc.DrawText((LPCTSTR)lpDrawItemStruct->itemData, rect, 
    DT_LEFT | DT_WORDBREAK);
  
  dc.Detach();
}

// ��� ������� ���������� ���� �����������, ��, �.�.
// ��� ���������� ������ ��� ���������� �������� � ������,
// � ���� ���������� ����������� ������ �������� ��� ������ 
// ����������� - ���������� �� ������ �� ������
void CVListBox::MeasureItem(
  LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
}
