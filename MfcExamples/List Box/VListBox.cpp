/*************************************************************
Файл VListBox.cpp
Copyright (c) 1999 Мешков А., Тихомиров Ю.
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

// минимальная величина обрамления 
// пиктограммы в элементе списка
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

  // смещение для вывода текста (32 - размер пиктограммы)
  rect.left += 32 + FRAME + FRAME;

  // вычисляем требуемую высоту области вывода текста
  int nHeight = dc.DrawText((LPCTSTR)lpDrawItemStruct->itemData, 
    rect, DT_CALCRECT | DT_LEFT | DT_WORDBREAK) + FRAME + FRAME;

  rect.bottom = rect.top + nHeight;

  if (nHeight < 32 + FRAME + FRAME)
    rect.bottom = rect.top + 32 + FRAME + FRAME;

  // изменяем высоту элемента управления
  SetItemHeight(lpDrawItemStruct->itemID, rect.Height());

  // поле структуры необходимо изменить самостоятельно
  lpDrawItemStruct->rcItem.bottom = rect.bottom;
  rect = lpDrawItemStruct->rcItem;

  // определяем состояние элемента списка
  if (lpDrawItemStruct->itemState & ODS_SELECTED)
  {
    // рисуем утопленную "кнопку"
    dc.DrawFrameControl(&rect, DFC_BUTTON, 
      DFCS_BUTTONPUSH | DFCS_PUSHED);
  }
  else
  {
    // рисуем выпуклую "кнопку"
    dc.DrawFrameControl(&rect, DFC_BUTTON, DFCS_BUTTONPUSH);
  }

  // рисуем пиктограмму, центруируя ее по вертикали
  rect.top += (rect.Height() - 32) / 2;
  dc.DrawIcon(rect.left+FRAME, rect.top, 
    AfxGetApp()->LoadIcon(IDR_MAINFRAME));

  rect = lpDrawItemStruct->rcItem;
  rect.left += 32 + FRAME;

  rect.DeflateRect(FRAME, FRAME);
  rect.top += (rect.Height() - (nHeight - FRAME)) / 2;

  // выводим текст элемента управления
  dc.SetBkMode(TRANSPARENT);
  dc.DrawText((LPCTSTR)lpDrawItemStruct->itemData, rect, 
    DT_LEFT | DT_WORDBREAK);
  
  dc.Detach();
}

// эту функцию необходимо было перегрузить, но, т.к.
// она вызывается только при добавлении элемента в список,
// а наша реализация настраивает высоту элемента при каждом 
// отображении - реализация ее ничего не делает
void CVListBox::MeasureItem(
  LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
}
