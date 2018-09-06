// NoteView.cpp : implementation of the CTextView class
//

#include "stdafx.h"
#include "NoteDraw.h"

#include "NoteDoc.h"
#include "NoteView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ND_LEFT   DT_LEFT   | DT_WORDBREAK
#define ND_CENTER DT_CENTER | DT_WORDBREAK
#define ND_RIGHT  DT_RIGHT  | DT_WORDBREAK

/////////////////////////////////////////////////////////////////////////////
// CTextView

// для работы с блоком диалога Find/Replace (Найти/Заменить)
// при регистрации сообщения необходимо использовать
// строковую константу FINDMSGSTRING
static const UINT nNewMsg = ::RegisterWindowMessage(FINDMSGSTRING);

IMPLEMENT_DYNCREATE(CTextView, CEditView)

BEGIN_MESSAGE_MAP(CTextView, CEditView)
  //{{AFX_MSG_MAP(CTextView)
	ON_CONTROL_REFLECT(EN_CHANGE, OnChange)
  ON_COMMAND_RANGE(ID_CENTER, ID_LEFT, OnAlign)
	ON_COMMAND(ID_FONT, OnFont)
	ON_COMMAND(ID_EDIT_FIND, OnEditFind)
	ON_COMMAND(ID_EDIT_REPLACE, OnEditReplace)
	//}}AFX_MSG_MAP
  ON_REGISTERED_MESSAGE(nNewMsg, OnNewCmd)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTextView construction/destruction

CTextView::CTextView()
{
  bFindOnly = FALSE;
}

CTextView::~CTextView()
{
}

BOOL CTextView::PreCreateWindow(CREATESTRUCT& cs)
{
	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// Enable word-wrapping

	return bPreCreated;
}

/////////////////////////////////////////////////////////////////////////////
// CTextView diagnostics

#ifdef _DEBUG
void CTextView::AssertValid() const
{
	CEditView::AssertValid();
}

void CTextView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CNoteDoc* CTextView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CNoteDoc)));
	return (CNoteDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTextView message handlers

void CTextView::OnAlign(UINT nID)
{
  UINT id = nID - ID_CENTER;
  CNoteDoc* pDoc = (CNoteDoc*)GetDocument();
  CParagraph *pPar = FindParagraph(pDoc);
  
  switch(id)
  {
    case 0: pPar->m_align = ND_CENTER; break;
    case 1: pPar->m_align = ND_RIGHT; break;
    case 2: pPar->m_align = ND_LEFT; break;
  }

  pDoc->UpdateAllViews(this);
}

/////////////////////////////////////////////////////////////////////////////
// CNoteView

IMPLEMENT_DYNCREATE(CNoteView, CScrollView)

CNoteView::CNoteView()
{
}

CNoteView::~CNoteView()
{
}


BEGIN_MESSAGE_MAP(CNoteView, CScrollView)
	//{{AFX_MSG_MAP(CNoteView)
	ON_COMMAND(ID_PAGE_SETUP, OnPageSetup)
	ON_COMMAND(ID_ZOOM, OnZoom)
	//}}AFX_MSG_MAP
  ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
  ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
  ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNoteView diagnostics

#ifdef _DEBUG
void CNoteView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CNoteView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CNoteView message handlers


void CTextView::OnChange() 
{
	int len;
  CParagraph *pPar;
  CString str, tmp;
  GetWindowText(str);
	
  CNoteDoc *pDoc = (CNoteDoc *)GetDocument();

  if(!str.IsEmpty())
  {
    pDoc->DeleteContents();
    str += "\n";
    do
    {
      len = str.Find("\n");
      pPar = pDoc->OnNewPar(ND_LEFT);
      pPar->m_words = str.Left(len);
      pDoc->m_listPar.AddTail(pPar);
      str = str.Mid(len + 1);
    }while(str != "");
    
  }
  pDoc->SetModifiedFlag();
  pDoc->UpdateAllViews(this);
}

void CTextView::OnFont() 
{
  LOGFONT lf;
	CNoteDoc* pDoc = (CNoteDoc*)GetDocument();
  
  CParagraph *pPar = FindParagraph(pDoc);
  pPar->m_font.GetLogFont(&lf);
 
  CFontDialog dlg(&lf);
  dlg.m_cf.Flags &= ~CF_SCREENFONTS;
  dlg.m_cf.Flags |= CF_BOTH | CF_TTONLY;

  dlg.m_cf.rgbColors = pPar->m_color;
  dlg.m_cf.lpLogFont->lfHeight =
                 (long)(dlg.m_cf.lpLogFont->lfHeight/2.3);
  
  if(dlg.DoModal() == IDOK)
  {
    pPar->m_color = dlg.GetColor();
    dlg.m_cf.lpLogFont->lfHeight =
                 (long)(dlg.m_cf.lpLogFont->lfHeight*17.55);
    pPar->m_font.DeleteObject();
    pPar->m_font.CreatePointFontIndirect(dlg.m_cf.lpLogFont);
  }
  pDoc->UpdateAllViews(this);
}

CParagraph* CTextView::FindParagraph(CNoteDoc *pDoc)
{
  CString str, tmp;
  GetWindowText(str);

 	int len, end, lensum = 0;
  CParagraph *pPar;
  POSITION pos = pDoc->m_listPar.GetHeadPosition();

  GetEditCtrl().GetSel(end, end);
  str += "\n";
  do
  {
    len = str.Find("\n");
    tmp = str.Left(len);

    pPar = pDoc->m_listPar.GetNext(pos);
    if(end >= lensum && end <= lensum + len)
      break;
    lensum += len + 1;
    str = str.Mid(len + 1);
  }while(str != "");
  return pPar;
}

void CNoteView::OnPageSetup() 
{
	CNDApp *pApp = (CNDApp*)AfxGetApp();
  // создаем объект блока диалога Page Setup (Параметры страницы)
  CPageSetupDialog dlg;
  // Настройка внешнего вида осуществляется с помощью структуры
  PAGESETUPDLG& psd = dlg.m_psd;
  // будем настраивать значения полей, а размеры задаются
  // в сотых долях миллиметра
  psd.Flags |= PSD_MARGINS | PSD_INHUNDREDTHSOFMILLIMETERS;
  // устанавливаем необходимые значения  
  psd.rtMargin.left   = pApp->m_rtMargin.left*10;
  psd.rtMargin.right  = pApp->m_rtMargin.right*10;
  psd.rtMargin.top    = pApp->m_rtMargin.top*10;
  psd.rtMargin.bottom = pApp->m_rtMargin.bottom*10;
   	
  // для фиксации значений получаем параметры принтера  
  PRINTDLG pd;
	pd.hDevNames = NULL;
	pd.hDevMode = NULL;
	pApp->GetPrinterDeviceDefaults(&pd);
  psd.hDevNames = pd.hDevNames;
	psd.hDevMode  = pd.hDevMode;

  // выводим блок диалога на экран
  if(dlg.DoModal() == IDOK)
  {
    // если пользователь нажал OK, фиксируем его установки
    pApp->m_rtMargin.left   = psd.rtMargin.left/10;
    pApp->m_rtMargin.right  = psd.rtMargin.right/10;
    pApp->m_rtMargin.top    = psd.rtMargin.top/10;
    pApp->m_rtMargin.bottom = psd.rtMargin.bottom/10;
    // при необходимости изменяем принтер,
    // используемый по умолчанию
    pApp->SelectPrinter(psd.hDevNames, psd.hDevMode, FALSE);
    CDC dc;
    pApp->CreatePrinterDC(dc);

    // получаем размеры бумаги
    pApp->m_sizePaper = CSize(dc.GetDeviceCaps(HORZSIZE)*10,
                              dc.GetDeviceCaps(VERTSIZE)*10);
    
    // после того, как были изменены параметры страницы необходимо
    // произвести обновление изображения данных на экране
    CNoteDoc* pDoc = (CNoteDoc*)GetDocument();
    // сообщение об обновлении передается всем представлениям,
    // ассоциированным с документом, но реально предназначается
    // только объекту класса, на который указывает this
    pDoc->UpdateAllViews(NULL, 0, this);
  }
	
}

/////////////////////////////////////////////////////////////////////////////
// CNoteView drawing

void CNoteView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo *pInfo)
{
}

void CNoteView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

BOOL CNoteView::OnPreparePrinting(CPrintInfo* pInfo)
{
  if (pInfo != NULL && !pInfo->m_bPreview)
  {
    // документ не будет иметь больше одной страницы
    pInfo->SetMaxPage(1);
  
    // получаем указатель на документ, с которым
    // ассоциировано текущее представление
    CNoteDoc* pDoc = (CNoteDoc*)GetDocument();
    // получаем позицию первого представления, хранящегося в
    // списке представлений ассоциированных с документом
    POSITION pos = pDoc->GetFirstViewPosition();
    // получаем указатель на первое представление в списке
    pDoc->GetNextView(pos);
    // получаем указатель на второе представление в списке
    CTextView *pText = (CTextView *)pDoc->GetNextView(pos);

    CString str;
    // читаем данные представления
    pText->GetSelectedText(str);
    if(!str.IsEmpty())
    {
      // если есть выделенный фрагмент, то переключатель
      // Print range (Печатать) устанавливаем в положение
      // Selection (Выделенный фрагмент)
      CPrintDialog *pPD = pInfo->m_pPD;
      pPD->m_pd.Flags &= ~PD_NOSELECTION;
      pPD->m_pd.Flags |= PD_SELECTION;
    }
  }

  // если же выделенного фрагмента нет, то используем
  // установки по умолчанию

  // не забываем вызвать функцию базового класса
  // для проведения корректной инициализации
  return DoPreparePrinting(pInfo);
}

void CNoteView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
  CNDApp *pApp = (CNDApp*)AfxGetApp();

  // создаем контекст устройства для принтера
  CDC dc;
  pApp->CreatePrinterDC(dc);

  // Определяем размеры бумаги исходя из установок принтера  
  CSize sizePaper = CSize(dc.GetDeviceCaps(HORZSIZE)*10,
                          dc.GetDeviceCaps(VERTSIZE)*10);

  CRect rect(0, 0, sizePaper.cx, sizePaper.cy);//pApp->m_sizePaper.cx, pApp->m_sizePaper.cy);

  // в режиме предварительного просмотра рисуем рамку вокруг текста
  if (pInfo != NULL && pInfo->m_bPreview)
		DrawMargins(pDC, rect);

  // учитываем величины полей
  rect.left   += pApp->m_rtMargin.left;
  rect.right  -= pApp->m_rtMargin.right;
  rect.top    -= pApp->m_rtMargin.top;
  rect.bottom += pApp->m_rtMargin.bottom;
  
  // преобразуем логические координаты в физические
  pDC->LPtoDP(&rect);

  // изменяем параметры прямоугольника рисования
  pInfo->m_rectDraw.left   = rect.left;
  pInfo->m_rectDraw.right  = rect.right;
  pInfo->m_rectDraw.top    = rect.top;
  pInfo->m_rectDraw.bottom = rect.bottom;

  // устанавливаем новые координаты области вывода  
  pDC->SetViewportOrg(rect.left, rect.top);
  
  CString strHeader = GetDocument()->GetTitle();
  // печатаем заголовок
  PrintHeader(pDC, pInfo, strHeader);

  // рисуем данные документа  
  OnDraw(pDC);
}

void CNoteView::DrawMargins(CDC* pDC, CRect &rt)
{
  CNDApp *pApp = (CNDApp*)AfxGetApp();
  if (pDC->m_hAttribDC != NULL)
	{
		CRect rect, rectMargin = pApp->m_rtMargin;
    // устанавливаем границы для рамки
    rect.left   =  pApp->m_rtMargin.left - 5;
		rect.right  =  rt.right - pApp->m_rtMargin.right + 10;
		rect.top    = -pApp->m_rtMargin.top;
		rect.bottom = -rt.bottom + pApp->m_rtMargin.bottom;

    // создаем карандаш    
    CPen pen(PS_DOT, 0, pDC->GetTextColor());
    // выбираем его в контекст устройства		
    CPen* ppen = pDC->SelectObject(&pen);
    // рисуем рамку		
    pDC->MoveTo(0, rect.top);
		pDC->LineTo(10000, rect.top);
		pDC->MoveTo(rect.left, 0);
		pDC->LineTo(rect.left, -10000);
		pDC->MoveTo(0, rect.bottom);
		pDC->LineTo(10000, rect.bottom);
		pDC->MoveTo(rect.right, 0);
		pDC->LineTo(rect.right, -10000);
    // удаляем карандаш из контекста устройства		
    pDC->SelectObject(ppen);
	}
}

void CNoteView::OnUpdate(CView* , LPARAM , CObject *pHint) 
{
  // если определено представление требующее перерисовки
  if(pHint != NULL)
    // и оно является объектом класса CNoteView ...
    if(pHint->IsKindOf(RUNTIME_CLASS(CNoteView)))
    {
      // ... изменяем размеры этого представления
      CNDApp *pApp = (CNDApp*)AfxGetApp();
      // параметры размера бумаги хранятся у приложения и
      // надо получить к ним доступ
      CSize sizeTotal;
      // формируем размеры области вывода, учитывая
      // как размер бумаги, так и поля
      sizeTotal.cx = (pApp->m_sizePaper.cx   -
                      pApp->m_rtMargin.right -
                      pApp->m_rtMargin.left - 120);
      sizeTotal.cy = (pApp->m_sizePaper.cy -
                      pApp->m_rtMargin.bottom -
                      pApp->m_rtMargin.top - 120);

      // в соответствии с текущими размерами бумаги и полей
      // устанавливаем новые параметры прокрутки
      SetScrollSizes(MM_LOMETRIC, sizeTotal);
     }
  // Обновляем все, хотя можно и ограничить размеры области 
  Invalidate(TRUE);
}

void CNoteView::OnInitialUpdate()
{
  // Пусть библиотека MFC выполнит за нас всю
  // необходимую предварительную работу
  CScrollView::OnInitialUpdate();
  
  // Создаем новый (пустой) абзац
  CNoteDoc* pDoc = (CNoteDoc*)GetDocument();
  CParagraph *pPar = pDoc->OnNewPar(ND_LEFT);
  // Добавляем его в общий список абзацев
  pDoc->m_listPar.AddTail(pPar);
  
  // Обновляем все изображения данных документа
  pDoc->UpdateAllViews(NULL, 0, this);
}

void CNoteView::OnDraw(CDC* pDC)
{
  CNDApp *pApp = (CNDApp*)AfxGetApp();
  CSize wordLen, size = GetTotalSize();
  CRect rect(0, 0, 0, 0);
  
  if(pDC->IsPrinting())
    size += CSize(130, 120);
  rect.right  =  size.cx;
  rect.bottom = -size.cy;
      
  CString str;
  CFont *oldFont;
  CParagraph *pPar;
  TEXTMETRIC tm;
  CNoteDoc *pDoc = (CNoteDoc *)GetDocument();
    
  pDC->SetBkMode(TRANSPARENT);
  POSITION pos = pDoc->m_listPar.GetHeadPosition();
  for(int i = 0; pos != NULL; i++)
  {
    pPar = pDoc->m_listPar.GetNext(pos);
    pDC->SetTextColor(pPar->m_color);
    int nHeight = 0;
    
    if(!pPar->m_words.IsEmpty())
    {
      oldFont = pDC->SelectObject(&pPar->m_font);
   
      nHeight = pDC->DrawText(pPar->m_words, &rect, pPar->m_align);
      pDC->GetTextMetrics(&tm);
      pDC->SelectObject(oldFont);
    }
    rect.top += nHeight + tm.tmHeight;
  }
}

void CTextView::OnInitialUpdate() 
{
	CEditView::OnInitialUpdate();
  CNoteDoc* pDoc = (CNoteDoc*)GetDocument();
  CString str("");
  CParagraph *pPar;
  
  POSITION pos = pDoc->m_listPar.GetHeadPosition();
  while(pos != NULL)
  {
    pPar = pDoc->m_listPar.GetNext(pos);
    str += pPar->m_words;
    str += "\n";
  }
  SetWindowText(str.Left(str.GetLength() - 2));
}

void CTextView::OnEditFind() 
{
  // создаем объект блока диалога
  CFindReplaceDialog *pDlg = new CFindReplaceDialog;
  bFindOnly = TRUE;
	// создаем объект Windows блока диалога Find (Поиск)
  pDlg->Create(TRUE, NULL, NULL, FR_HIDEWHOLEWORD | FR_DOWN, this);
}

void CTextView::OnEditReplace() 
{
  CFindReplaceDialog *pDlg = new CFindReplaceDialog;
  bFindOnly = FALSE;
	pDlg->Create(FALSE, NULL, NULL, FR_NOWHOLEWORD | FR_DOWN, this);
}

LRESULT CTextView::OnNewCmd(WPARAM, LPARAM lParam)
{
  // получаем указатель на объект стандартного блока диалога
  // Find/Replace (Найти/Заменить)
  CFindReplaceDialog* pDialog = CFindReplaceDialog::GetNotifier(lParam);
  
  if (pDialog->IsTerminating())
	{
    // если пользователь завершил работу по поиску/замене, то
    // сообщаем библиотеке, что объект блока диалога
    // больше не нужен
		pDialog = NULL;
	}
	else if (pDialog->FindNext())
	{
    // получаем строку, которую требуется найти
		CString strFind = pDialog->GetFindString();
    // осуществляем поиск
    // параметры поиска получаем прямо из блока диалога
    OnFindNext(strFind,
			         pDialog->SearchDown(), pDialog->MatchCase());
	}
  else if (pDialog->ReplaceCurrent())
	{
    // сюда вход разрешен только для режима замены
		ASSERT(!bFindOnly);
    // пользователь нажал кнопку Replace (Заменить): требуется
    // найти определенную строку и заменить ее на заданную
    // параметры получаем прямо из блока диалога
		OnReplaceSel(pDialog->GetFindString(),
                 pDialog->SearchDown(), pDialog->MatchCase(),
                 pDialog->GetReplaceString());
	}
	else if (pDialog->ReplaceAll())
	{
		ASSERT(!bFindOnly);
    // пользователь нажал кнопку Replace All (Заменить все):
    // требуется найти все вхождения определенной строки
    // и заменить их на заданную
    // параметры получаем прямо из блока диалога
    OnReplaceAll(pDialog->GetFindString(),
                 pDialog->GetReplaceString(),
                 pDialog->MatchCase());
	}
		
  return 0;
}

void CTextView::OnTextNotFound(LPCTSTR lpszFind)
{
  // если искомая строка не найдена, то выводим об этом
  // информационное сообщение 
  AfxMessageBox("Текст не найден");
}

void CNoteView::PrintHeader(CDC *pDC, CPrintInfo *pInfo, CString strHeader)
{
  // устанавливаем выравнивание влево
  pDC->SetTextAlign(TA_LEFT);
  // для учета величины смещения получаем
  // характеристики шрифта
  TEXTMETRIC tm;
  pDC->GetTextMetrics(&tm);
  int y = tm.tmHeight + 15;
  // выводим заголовок
  pDC->TextOut(25, y, strHeader);
  // формируем смещение для линии
  y -= tm.tmHeight + 5;
  // определяем длину текста
  CSize len = pDC->GetTextExtent(strHeader);
  // рисуем разделительную линию  
  pDC->MoveTo(0, y);
  pDC->LineTo(len.cx + 250, y);

  // устанавливаем выравнивание вправо
  pDC->SetTextAlign(TA_RIGHT);
  TCHAR szBuf[32];

  // формируем строку с номером страницы
  wsprintf(szBuf, "%d", pInfo->m_nCurPage);

  // выводим номер страницы в правом нижнем углу
  pDC->TextOut(pInfo->m_rectDraw.right - 525,
	           pInfo->m_rectDraw.bottom - 1250, szBuf);
}


void CNoteView::OnZoom() 
{
	ResizeParentToFit(TRUE);
}
