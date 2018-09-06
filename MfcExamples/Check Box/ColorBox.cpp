/*************************************************************
���� ColorBox.cpp
Copyright (c) 1999 ������ �., ��������� �.
*************************************************************/

// ColorBox.cpp : implementation file
//

#include "stdafx.h"
#include "CheckBox.h"
#include "ColorBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define COLOR_ITEM_HEIGHT 20

/////////////////////////////////////////////////////////////////////////////
// CColorBox

CColorBox::CColorBox()
{
}

CColorBox::~CColorBox()
{
}


BEGIN_MESSAGE_MAP(CColorBox, CCheckListBox)
	//{{AFX_MSG_MAP(CColorBox)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CColorBox::AddColorItem(COLORREF color)
{
  // ��������� ������ � ������
  AddString((LPCTSTR) color);
}

/////////////////////////////////////////////////////////////////////////////
// CColorBox message handlers

// �������������� ������� ��� ��������� ����� ������
int CColorBox::CompareItem(
  LPCOMPAREITEMSTRUCT lpCompareItemStruct)
{
	// return -1 = item 1 sorts before item 2
	// return 0 = item 1 and item 2 sort the same
	// return 1 = item 1 sorts after item 2

  COLORREF cr1 = (COLORREF)lpCompareItemStruct->itemData1;
  COLORREF cr2 = (COLORREF)lpCompareItemStruct->itemData2;

  if (cr1 == cr2)
   return 0; // ������ ���������

  // ������� �������� ������ �� �������������
  int intensity1 = GetRValue(cr1) + 
                   GetGValue(cr1) +
                   GetBValue(cr1);

  int intensity2 = GetRValue(cr2) + 
                   GetGValue(cr2) + 
                   GetBValue(cr2);

  if (intensity1 < intensity2)
    return -1; // ������� ���� ������ � ������� ��������
  else if (intensity1 > intensity2)
    return 1; // ����� ����� ������ ���� �������

  // ���� ������ ����� ���������� �������������, 
  // �� ��������� �� ������:
  //   ������ - �����, ��������� - �������
  if (GetBValue(cr1) > GetBValue(cr2))
    return -1;
  else if (GetGValue(cr1) > GetGValue(cr2))
    return -1;
  else if (GetRValue(cr1) > GetRValue(cr2))
    return -1;
  else
    return 1;

  return 0;
}

// �������������� ������� ��� ��������� ����� ������
// ������ ������ ������ ���������� ������� ��
// ��������� - ������� � ���� � ��� (�������/�� �������)
// ������ ��� ������ ������� 
void CColorBox::DrawItem(
  LPDRAWITEMSTRUCT lpDrawItemStruct)
{
  CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
  COLORREF cr = (COLORREF)lpDrawItemStruct->itemData;

  if (lpDrawItemStruct->itemAction & ODA_DRAWENTIRE)
  {
    CBrush br(cr);
    pDC->FillRect(&lpDrawItemStruct->rcItem, &br);
  }

  if ((lpDrawItemStruct->itemState & ODS_SELECTED) &&
    (lpDrawItemStruct->itemAction & 
    (ODA_SELECT | ODA_DRAWENTIRE)))
  {
    // ��������� ����� ���� ������ ��������
    COLORREF crHilite = RGB(255-GetRValue(cr),
                            255-GetGValue(cr), 
                            255-GetBValue(cr));

    CBrush br(crHilite);
    pDC->FrameRect(&lpDrawItemStruct->rcItem, &br);
  }

  if (!(lpDrawItemStruct->itemState & ODS_SELECTED) &&
    (lpDrawItemStruct->itemAction & ODA_SELECT))
  {
    // �������� ����� ���� ��������� � ������ ������ �����
    CBrush br(cr);
    pDC->FrameRect(&lpDrawItemStruct->rcItem, &br);
  }
}

// �������������� ������� ��� ����������� �������� ����� ������
void CColorBox::MeasureItem(
  LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
  lpMeasureItemStruct->itemHeight = COLOR_ITEM_HEIGHT;
}

