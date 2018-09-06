/////////////////////////////////////////////////////////
// Файл TempDlg.cpp
// Copyright (c) 1999 Мешков А., Тихомиров Ю.
/////////////////////////////////////////////////////////

// Реализация классов CItem, CMemory и CTemplateDlg
//

#include "stdafx.h"
#include "Template.h"
#include "TempDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CItem - элементы управления шаблона в памяти

CItem::CItem(enum ctrtype cType)
{
 m_ctrtype = cType;
}

void CItem::Initialize(enum ctrtype cType, UINT nID,
                  CRect* prect, LPCTSTR pszCaption)
{
 m_ctrtype = cType;
 // заполняем поля структуры DLGITEMTEMPLATE
 if(prect != NULL){
  m_ctrItem.x  = (short)prect->left;
  m_ctrItem.y  = (short)prect->top;
  m_ctrItem.cx = (short)prect->Width();
  m_ctrItem.cy = (short)prect->Height();
 }
 else{
  m_ctrItem.x  = 0;
  m_ctrItem.y  = 0;
  m_ctrItem.cx = 20;
  m_ctrItem.cy = 20;
 }
 m_ctrItem.dwExtendedStyle = 0;
 m_ctrItem.id = nID;

 switch(m_ctrtype){
  case STATICTEXT:
   m_ctrItem.style = WS_CHILD | WS_VISIBLE | SS_CENTER;
   break;
  case EDITTEXT:
   m_ctrItem.style = WS_CHILD | WS_VISIBLE | ES_MULTILINE | ES_LEFT |
                     WS_EX_CLIENTEDGE | WS_BORDER;
   break;
  default:
   ASSERT(FALSE);
 }
 m_strTitle = (pszCaption != NULL) ? pszCaption : _T("");
}

/////////////////////////////////////////////////////////////////////////////
// CMemory - шаблон в памяти

#define SETRECT(rect, l, t, r, b) \
 rect.left   = l; \
 rect.top    = t; \
 rect.right  = r; \
 rect.bottom = b;

CMemory::CMemory(){
 // инициализация элементов шаблона диалога
 CRect rect(40, 10, 200, 35);
 m_dlgItem[0].Initialize(CItem::STATICTEXT, IDC_TEXTSTATIC,
                         &rect, _T("Статический текст"));
 SETRECT(rect, 40, 32, 200, 96);
 m_dlgItem[1].Initialize(CItem::EDITTEXT, IDC_TEXTEDIT,
                         &rect, _T("Редактируемый текст"));
 
 // инициализация структуры DLGTEMPLATE
 m_dlgMemory.cx = 240;
 m_dlgMemory.cy = 104;
 m_dlgMemory.style = WS_CAPTION | WS_VISIBLE |WS_DLGFRAME |
                     WS_POPUP | DS_MODALFRAME | DS_SETFONT;
 m_dlgMemory.dwExtendedStyle = 0;
 m_dlgMemory.x = 0;
 m_dlgMemory.y = 0;
 m_dlgMemory.cdit = 2;
}

void CMemory::Show(){
// Прежде всего необходимо распределить память под шаблон

 WCHAR szBoxTitle[] = L"Шаблон блока диалога в памяти: Выход - <ESC>";
 WCHAR szFontName[] = L"Courier New Cyr";
 // Размер структуры DLGTEMPLATE и заголовка блока диалога
 int nBufferSize = sizeof(DLGTEMPLATE) + // структура
                   (2*sizeof(WORD)) +    // меню и класс
                   sizeof(szBoxTitle);   // заголовок
 nBufferSize += sizeof(WORD) + sizeof(szFontName); // шрифт
 nBufferSize = (nBufferSize + 3) & ~3;
 
 // Добавляем размеры структуры DLGITEMTEMPLATE
 // и заголовков элементов
 for(int i = 0; i < 2; i++){
  int nItemLength = (sizeof(DLGITEMTEMPLATE) + 3*sizeof(WORD) +
       (m_dlgItem[i].m_strTitle.GetLength() + 1)*sizeof(WCHAR));
		if (i != 1 )
				nItemLength = (nItemLength + 3) & ~3;
  nBufferSize += nItemLength;
 }
 
 // Выделяем память
 HLOCAL hLocal = LocalAlloc(LHND, nBufferSize);
 if(hLocal == NULL){
  // Обработка ошибки распределения памяти
 }
 BYTE *pBuffer = (BYTE*)LocalLock(hLocal);
 if(pBuffer == NULL){
  LocalFree(hLocal);
 }

 BYTE *pDest = pBuffer;

 // Переписываем структуру DLGTEMPLATE в буфер
 memcpy(pDest, &m_dlgMemory, sizeof(DLGTEMPLATE));
 pDest += sizeof(DLGTEMPLATE);
 *(WORD*)pDest = 0; // меню нет
 *(WORD*)pDest = 0; // используем класс по умолчанию
 pDest += 2*sizeof(WORD);
 memcpy(pDest, szBoxTitle, sizeof(szBoxTitle));
 pDest += sizeof(szBoxTitle);
 *(WORD*)pDest = 10; // размер шрифта
 pDest += sizeof(WORD);
 memcpy(pDest, szFontName, sizeof(szFontName));
 pDest += sizeof(szFontName);

 // Переписываем информацию о каждом элементе шаблона
 for(i = 0; i < 2; i++){
 	pDest = (BYTE*)(((DWORD)pDest + 3) & ~3);
  memcpy(pDest, (void*)&m_dlgItem[i].m_ctrItem,
         sizeof(DLGITEMTEMPLATE));
  pDest += sizeof(DLGITEMTEMPLATE);
  
  *(WORD*)pDest = 0xFFFF; // имеется идентификатор ресурса
  pDest += sizeof(WORD);
  *(WORD*)pDest = m_dlgItem[i].m_ctrtype;
  pDest += sizeof(WORD);
  
  // Переписываем заголовок, предварительно преобразовав его
  // в Unicode строку
  WCHAR *pchCaption;
  int nChar;

  nChar = m_dlgItem[i].m_strTitle.GetLength() + 1;
  pchCaption = new WCHAR[nChar];
  nChar = MultiByteToWideChar(CP_ACP, 0, m_dlgItem[i].m_strTitle,
                                 -1, pchCaption, nChar);
  ASSERT(nChar > 0);
  memcpy(pDest, pchCaption, nChar*sizeof(WCHAR));
  pDest += nChar*sizeof(WCHAR);
  delete pchCaption;

  *(WORD*)pDest = 0;
  pDest += sizeof(WORD);
 }
 ASSERT(pDest - pBuffer == nBufferSize);

 CDialog dlg;
 dlg.InitModalIndirect((DLGTEMPLATE*)pBuffer);
 dlg.DoModal();

 LocalUnlock(hLocal);
 LocalFree(hLocal);
}

/////////////////////////////////////////////////////////////////////////////
// Блок диалога CTemplateDlg

CTemplateDlg::CTemplateDlg(CWnd* pParent)
	: CDialog(CTemplateDlg::IDD, pParent){
 m_nActiveItem = -1;
	//{{AFX_DATA_INIT(CTemplateDlg)
	 m_strTitle = _T("");
	 m_x = 0;
	 m_y = 0;
	 m_nWidth = 0;
	 m_nHeight = 0;
 	m_nItem = -1;
  m_strItem = _T("");
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTemplateDlg::DoDataExchange(CDataExchange* pDX){
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTemplateDlg)
	 DDX_Text(pDX, IDC_TITLE, m_strTitle);
	 DDX_Text(pDX, IDC_XPOS, m_x);
	 DDX_Text(pDX, IDC_YPOS, m_y);
	 DDX_Text(pDX, IDC_WIDTH, m_nWidth);
	 DDX_Text(pDX, IDC_HEIGHT, m_nHeight);
 	DDX_Radio(pDX, IDC_STATICTEXT, m_nItem);
  DDX_Text(pDX, IDC_CAPTION, m_strItem);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTemplateDlg, CDialog)
	//{{AFX_MSG_MAP(CTemplateDlg)
 ON_BN_CLICKED(ID_SHOW, OnShow)
 ON_BN_CLICKED(IDC_EDITTEXT, OnEdit)
 ON_BN_CLICKED(IDC_STATICTEXT, OnStatic)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Обработчики сообщений класса CTemplateDlg

BOOL CTemplateDlg::OnInitDialog(){
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);
		
	m_nItem = 0;
  OnStatic();
	return TRUE;
}

void CTemplateDlg::OnShow(){
 InfoToDialog(m_nActiveItem, NULL);
 m_dlgTemplate.Show();
}

void CTemplateDlg::OnEdit(){
 InfoToDialog(1, _T("Поле ввода текста"));
}

void CTemplateDlg::OnStatic(){
 InfoToDialog(0, _T("Статический текст"));
}

void CTemplateDlg::InfoToDialog(int nItem, LPCTSTR lpszItem){
 if(m_nActiveItem != -1){
  UpdateData(TRUE);
  m_dlgTemplate.m_dlgItem[m_nActiveItem].m_ctrItem.x  = m_x;
  m_dlgTemplate.m_dlgItem[m_nActiveItem].m_ctrItem.y  = m_y;
  m_dlgTemplate.m_dlgItem[m_nActiveItem].m_ctrItem.cx = m_nWidth;
  m_dlgTemplate.m_dlgItem[m_nActiveItem].m_ctrItem.cy = m_nHeight;
  m_dlgTemplate.m_dlgItem[m_nActiveItem].m_strTitle   = m_strTitle;
 }

 if(m_nActiveItem != nItem){
  m_x        = m_dlgTemplate.m_dlgItem[nItem].m_ctrItem.x;
  m_y        = m_dlgTemplate.m_dlgItem[nItem].m_ctrItem.y;
  m_nWidth   = m_dlgTemplate.m_dlgItem[nItem].m_ctrItem.cx;
  m_nHeight  = m_dlgTemplate.m_dlgItem[nItem].m_ctrItem.cy;
  m_strTitle = m_dlgTemplate.m_dlgItem[nItem].m_strTitle;
  ASSERT(lpszItem != NULL);
  m_strItem = lpszItem;
  m_nItem = nItem;
  m_nActiveItem = nItem;
  UpdateData(FALSE);
 }
}
