/*************************************************************
Файл ListCtrlFrm.cpp
Copyright (c) 1999 Мешков А., Тихомиров Ю.
*************************************************************/

// ListCtrlFrm.cpp : implementation file
//

#include "stdafx.h"
#include "ListCtrl.h"
#include "ListCtrlFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// функция сортировки записей, 
// тип сортировки определяется
// значением третьего параметра
int CALLBACK SortFunc(LPARAM lParam1, 
  LPARAM lParam2, LPARAM dwType)
{
  WIN32_FIND_DATA *item1 = (WIN32_FIND_DATA *)lParam1;
  WIN32_FIND_DATA *item2 = (WIN32_FIND_DATA *)lParam2;

  switch (dwType)
  {
  case ID_VIEW_ARRANGE_BYNAME:
    return strcmp(item1->cFileName, item2->cFileName);
  case ID_VIEW_ARRANGE_BYTYPE:
    return strcmp(strrchr(item1->cAlternateFileName, '.'),
      strrchr(item2->cAlternateFileName, '.'));
  case ID_VIEW_ARRANGE_BYSIZE:
    return item1->nFileSizeLow - item2->nFileSizeLow;
  case ID_VIEW_ARRANGE_BYDATE:
    return CompareFileTime(&item1->ftLastWriteTime, 
      &item2->ftLastWriteTime);
  default:
    ASSERT(FALSE);
  }
  
  return 0;
}

////////////////////////////////////////////////////////////
// CListCtrlFrame

CListCtrlFrame::CListCtrlFrame()
{
  // инициализация переменных, используемых
  // для реализации перемещения записей
  m_bDragging = FALSE;
  m_pImageListDrag = NULL;
}

CListCtrlFrame::~CListCtrlFrame()
{
}

// функция изменения стиля списка просмотра
// для смены режимов отображения
void CListCtrlFrame::SetStyle(DWORD dwViewStyle)
{
  ASSERT(::IsWindow(m_List.m_hWnd));

  DWORD dwStyle = GetWindowLong(m_List.m_hWnd, GWL_STYLE);

  if ((dwStyle & LVS_TYPEMASK) != dwViewStyle)
    SetWindowLong(m_List.m_hWnd, GWL_STYLE, 
    (dwStyle & ~LVS_TYPEMASK) | dwViewStyle); 
}

BEGIN_MESSAGE_MAP(CListCtrlFrame, CFrameWnd)
  //{{AFX_MSG_MAP(CListCtrlFrame)
  ON_WM_CREATE()
  ON_COMMAND(ID_VIEW_LARGEICONS, OnViewLargeIcons)
  ON_COMMAND(ID_VIEW_SMALLICONS, OnViewSmallIcons)
  ON_COMMAND(ID_VIEW_LISTS, OnViewList)
  ON_COMMAND(ID_VIEW_DETAILS1, OnViewDetails)
  ON_COMMAND(ID_VIEW_ARRANGE_BYNAME, OnViewArrangeByName)
  ON_COMMAND(ID_VIEW_ARRANGE_BYTYPE, OnViewArrangeByType)
  ON_COMMAND(ID_VIEW_ARRANGE_BYSIZE, OnViewArrangeBySize)
  ON_COMMAND(ID_VIEW_ARRANGE_BYDATE, OnViewArrangeByDate)
  ON_COMMAND(ID_VIEW_ARRANGE_AUTOARRANGE, 
    OnViewArrangeAutoArrange)
  ON_WM_MOUSEMOVE()
  ON_WM_LBUTTONUP()
  ON_WM_RBUTTONUP()
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////
// CListCtrlFrame message handlers

int CListCtrlFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
  if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
    return -1;
  
  CRect rect;
  GetClientRect(rect);

  // создание и инициализация списка просмотра
  m_List.Create(LVS_ICON | LVS_REPORT | LVS_EDITLABELS | 
    WS_VISIBLE, rect, this, 1000);

  // создание и заполнение списков изображений
  m_ImageNormal.Create(32, 32, TRUE, 1, 1);
  m_ImageNormal.Add(AfxGetApp()->LoadIcon(IDI_FILE));

  m_ImageSmall.Create(16, 16, TRUE, 1, 1);
  m_ImageSmall.Add(AfxGetApp()->LoadIcon(IDI_FILE));
  
  m_List.SetImageList(&m_ImageNormal, LVSIL_NORMAL);
  m_List.SetImageList(&m_ImageSmall, LVSIL_SMALL);

  // добавление в спискок просмотра
  // четырех колонок, для реализации
  // режима таблицы
  m_List.InsertColumn(0, _T("Name"),
    LVCFMT_LEFT, rect.Width() / 3);
  m_List.InsertColumn(1, _T("Type"),
    LVCFMT_LEFT, 2 * rect.Width() / 9);
  m_List.InsertColumn(2, _T("Size"),
    LVCFMT_RIGHT, rect.Width() / 9);
  m_List.InsertColumn(3, _T("Modified"), 
    LVCFMT_LEFT, rect.Width() / 3);

  // поиск файлов и создание записей с
  // информацией о найденных файлах
  WIN32_FIND_DATA FindFileData;
  
  HANDLE hFile = FindFirstFile("*.*", &FindFileData);
  
  if (hFile != INVALID_HANDLE_VALUE)
  {
    LV_ITEM item;
    item.iItem = 0;
    item.iImage = 0;

    CString csText;
    SYSTEMTIME stTime;

    do
    {
      // директории игнорируем
      if (FindFileData.dwFileAttributes & 
        FILE_ATTRIBUTE_DIRECTORY)
        continue;

      item.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;

      // для реализации сортировки сохраняем дополнительно
      // информацию о найденном файле
      WIN32_FIND_DATA *lpFindFileData = new WIN32_FIND_DATA;
      *lpFindFileData = FindFileData;

      item.lParam = (DWORD)lpFindFileData;

      // имя файла
      item.iSubItem = 0;
      item.pszText = FindFileData.cFileName;
      m_List.InsertItem(&item);

      item.mask = LVIF_TEXT;

      // тип файла
      item.iSubItem = 1;
      csText = (strrchr(FindFileData.cAlternateFileName, '.')
        + 1);
      csText += " File";
      item.pszText = (LPTSTR)(LPCTSTR)csText;
      m_List.SetItem(&item);

      // длина файла
      item.iSubItem = 2;
      csText.Format("%dKB", FindFileData.nFileSizeLow / 1024);
      item.pszText = (LPTSTR)(LPCTSTR)csText;
      m_List.SetItem(&item);

      // дата и время последней записи в файл
      item.iSubItem = 3;
      FileTimeToSystemTime(&FindFileData.ftLastWriteTime,
        &stTime);
      csText = CTime(stTime).Format(" %d/%m/%Y %H:%M:%S");
      item.pszText = (LPTSTR)(LPCTSTR)csText;
      m_List.SetItem(&item);

      item.iItem++;
    }
    while (FindNextFile(hFile, &FindFileData));
  }
  
  return 0;
}

//
// функции смены режима отображения
//

void CListCtrlFrame::OnViewLargeIcons() 
{
  SetStyle(LVS_ICON);
}

void CListCtrlFrame::OnViewSmallIcons() 
{
  SetStyle(LVS_SMALLICON);
}

void CListCtrlFrame::OnViewList() 
{
  SetStyle(LVS_LIST);
}

void CListCtrlFrame::OnViewDetails() 
{
  SetStyle(LVS_ICON | LVS_REPORT);
}

//
// функции переупорядочивания (сортировки) по значениям
// различным атрибутов файла
//

void CListCtrlFrame::OnViewArrangeByName() 
{
  m_List.SortItems(SortFunc, ID_VIEW_ARRANGE_BYNAME);
}

void CListCtrlFrame::OnViewArrangeByType() 
{
  m_List.SortItems(SortFunc, ID_VIEW_ARRANGE_BYTYPE);
}

void CListCtrlFrame::OnViewArrangeBySize() 
{
  m_List.SortItems(SortFunc, ID_VIEW_ARRANGE_BYSIZE);
}

void CListCtrlFrame::OnViewArrangeByDate() 
{
  m_List.SortItems(SortFunc, ID_VIEW_ARRANGE_BYDATE);
}

// функция переупорядочивания - привязки записей списка
// к сетки привязки
void CListCtrlFrame::OnViewArrangeAutoArrange() 
{
  m_List.Arrange(LVA_SNAPTOGRID);
}

//
// функция обраболтки извещений, для поддержки:
//   - редактирования названий записи;
//   - перемещения записей
//

BOOL CListCtrlFrame::OnNotify(
  WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
  NMHDR *nmhdr = (NMHDR *)lParam;

  if (nmhdr->hwndFrom == m_List.m_hWnd)
  {
    LV_DISPINFO *pdi = (LV_DISPINFO *)lParam; 

    // для поддержки перемещения записей,
    // необходимо, как не странно, 
    // работать со структурой NM_LISTVIEW
    NM_LISTVIEW *plv = (NM_LISTVIEW *)lParam;
    CPoint ptItem, ptAction, ptImage;

    switch (nmhdr->code)
    {
    case LVN_ENDLABELEDIT:
      if (pdi->item.pszText != NULL)
        m_List.SetItemText(pdi->item.iItem, 0, pdi->item.pszText);
      break;
    case LVN_BEGINDRAG:
    case LVN_BEGINRDRAG:
      ASSERT(!m_bDragging);
      m_bDragging = TRUE;
      m_iItemDrag = plv->iItem;
      ptAction = plv->ptAction;
      m_List.GetItemPosition(m_iItemDrag, &ptItem);
      m_List.GetOrigin(&m_ptOrigin);
      m_pImageListDrag = 
        m_List.CreateDragImage(m_iItemDrag, &ptImage);
      m_sizeDelta = ptAction - ptImage;
      m_ptHotSpot = ptAction - ptItem + m_ptOrigin;
      m_pImageListDrag->DragShowNolock(TRUE);
      m_pImageListDrag->SetDragCursorImage(0, m_ptHotSpot); 
      m_pImageListDrag->BeginDrag(0, CPoint(0, 0));
      ptAction -= m_sizeDelta;
      m_pImageListDrag->DragEnter(&m_List, ptAction);
      m_pImageListDrag->DragMove(ptAction); 
      SetCapture();
      break;
    }
  }
  
  return CFrameWnd::OnNotify(wParam, lParam, pResult);
}

//
// функции обработки сообщений от мыши
//

void CListCtrlFrame::OnMouseMove(UINT nFlags, CPoint point) 
{
  if (m_bDragging)
    m_pImageListDrag->DragMove(point - m_sizeDelta); 
  
  CFrameWnd::OnMouseMove(nFlags, point);
}

void CListCtrlFrame::OnButtonUp(CPoint point)
{
  if (m_bDragging)
  {
    DWORD  dwStyle;

    dwStyle = GetWindowLong(m_List.m_hWnd, GWL_STYLE) & 
      LVS_TYPEMASK; 
    m_bDragging = FALSE;
    m_pImageListDrag->DragLeave(&m_List);
    m_pImageListDrag->EndDrag();

    if (dwStyle & (LVS_REPORT | LVS_LIST))
      MessageBeep((UINT)-1);
    else if (dwStyle == LVS_ICON || dwStyle == LVS_SMALLICON)
    {
      point -= m_ptHotSpot;
      point += m_ptOrigin;
      m_List.SetItemPosition(m_iItemDrag, point);
    }

    ReleaseCapture();
  }
}

void CListCtrlFrame::OnLButtonUp(UINT nFlags, CPoint point) 
{
  OnButtonUp(point);
  CFrameWnd::OnLButtonUp(nFlags, point);
}

void CListCtrlFrame::OnRButtonUp(UINT nFlags, CPoint point) 
{
  OnButtonUp(point);
  CFrameWnd::OnRButtonUp(nFlags, point);
}

// т.к. было динамическое выделение памяти
// дле реализации хранения информации о файлах,
// при уничтожении списка просмотра
// необходимо освободить эту память
BOOL CListCtrlFrame::DestroyWindow() 
{
  for (int i = 0; i < m_List.GetItemCount(); i++)
    delete (WIN32_FIND_DATA *)m_List.GetItemData(i);
  
  return CFrameWnd::DestroyWindow();
}
