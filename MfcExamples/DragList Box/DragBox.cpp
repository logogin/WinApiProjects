/*************************************************************
Файл DragBox.cpp
Copyright (c) 1999 Мешков А., Тихомиров Ю.
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

// пример реализации функции рисования
// указателя перемещения
void CDragBox::DrawInsert(int nItem)
{
  // проверяем было ли перемещение 
  // в новое место
  if (m_nLast != nItem)
  {
    DrawSingle(m_nLast);
    DrawSingle(nItem);

    m_nLast = nItem;
  }
}

// основную работу пусть делает функция
// базового класса - мы только заменим
// тип курсора
UINT CDragBox::Dragging(CPoint pt)
{
  if (CDragListBox::Dragging(pt) == DL_MOVECURSOR)
    return DL_COPYCURSOR;

  return DL_STOPCURSOR;
}

void CDragBox::Dropped(int nSrcIndex, CPoint pt)
{
  // проверяем допустимость стилей списка
  ASSERT(!(GetStyle() & LBS_OWNERDRAWFIXED | 
    LBS_OWNERDRAWVARIABLE) ||
    (GetStyle() & LBS_HASSTRINGS));

  // удаляем указатель перемещения
  DrawInsert(-1);

  // определяем новое место для вставки
  int nDestIndex = ItemFromPt(pt);

  // проверка необходимости вставки
  if (nSrcIndex == -1 || nDestIndex == -1)
     return;

  if (nDestIndex == nSrcIndex || nDestIndex == nSrcIndex+1)
    return; 
       
  // получаем информацию об элементе
  CString str;
  DWORD dwData;
  GetText(nSrcIndex, str);
  dwData = GetItemData(nSrcIndex);

  // вот сейчас можно текущий элемент удалить -
  // тогда функция будет реализовать перемещение
  
  // вставляем новый элемент и связываем с ним данные
  if (nSrcIndex < nDestIndex)
    nDestIndex--;
  nDestIndex = InsertString(nDestIndex, str);
  SetItemData(nDestIndex, dwData);

  // назначаем новый элемент текущим
  SetCurSel(nDestIndex);
}

/////////////////////////////////////////////////////////////////////////////
// CDragBox message handlers

