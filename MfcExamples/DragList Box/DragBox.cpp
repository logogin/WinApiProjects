/*************************************************************
���� DragBox.cpp
Copyright (c) 1999 ������ �., ��������� �.
*************************************************************/

// DragBox.cpp : implementation file
//

#include "stdafx.h"
#include "DragList.h"
#include "DragBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDragBox

CDragBox::CDragBox()
{
}

CDragBox::~CDragBox()
{
}


BEGIN_MESSAGE_MAP(CDragBox, CDragListBox)
	//{{AFX_MSG_MAP(CDragBox)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// ������ ���������� ������� ���������
// ��������� �����������
void CDragBox::DrawInsert(int nItem)
{
  // ��������� ���� �� ����������� 
  // � ����� �����
  if (m_nLast != nItem)
  {
    DrawSingle(m_nLast);
    DrawSingle(nItem);

    m_nLast = nItem;
  }
}

// �������� ������ ����� ������ �������
// �������� ������ - �� ������ �������
// ��� �������
UINT CDragBox::Dragging(CPoint pt)
{
  if (CDragListBox::Dragging(pt) == DL_MOVECURSOR)
    return DL_COPYCURSOR;

  return DL_STOPCURSOR;
}

void CDragBox::Dropped(int nSrcIndex, CPoint pt)
{
  // ��������� ������������ ������ ������
  ASSERT(!(GetStyle() & LBS_OWNERDRAWFIXED | 
    LBS_OWNERDRAWVARIABLE) ||
    (GetStyle() & LBS_HASSTRINGS));

  // ������� ��������� �����������
  DrawInsert(-1);

  // ���������� ����� ����� ��� �������
  int nDestIndex = ItemFromPt(pt);

  // �������� ������������� �������
  if (nSrcIndex == -1 || nDestIndex == -1)
     return;

  if (nDestIndex == nSrcIndex || nDestIndex == nSrcIndex+1)
    return; 
       
  // �������� ���������� �� ��������
  CString str;
  DWORD dwData;
  GetText(nSrcIndex, str);
  dwData = GetItemData(nSrcIndex);

  // ��� ������ ����� ������� ������� ������� -
  // ����� ������� ����� ����������� �����������
  
  // ��������� ����� ������� � ��������� � ��� ������
  if (nSrcIndex < nDestIndex)
    nDestIndex--;
  nDestIndex = InsertString(nDestIndex, str);
  SetItemData(nDestIndex, dwData);

  // ��������� ����� ������� �������
  SetCurSel(nDestIndex);
}

/////////////////////////////////////////////////////////////////////////////
// CDragBox message handlers

