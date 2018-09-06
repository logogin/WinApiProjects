// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "DispBMP.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView,CWnd )
	//{{AFX_MSG_MAP(CChildView)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), HBRUSH(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CWnd::OnPaint() for painting messages
	CFile file;
	file.Open(_T("rmat23.bmp"),CFile::modeRead);

	BITMAPFILEHEADER bmfh;

	file.Read(&bmfh,sizeof(BITMAPFILEHEADER));
	
	BITMAPINFOHEADER bmih;

	file.Read(&bmih, sizeof(BITMAPINFOHEADER));

	/*HGLOBAL hmem1 = GlobalAlloc(GHND, sizeof(BITMAPINFOHEADER) + 
		((1<<bmih.biBitCount) * sizeof(RGBQUAD))); */
 
	BITMAPINFO bmi;

	bmi.bmiHeader.biSize = bmih.biSize; 
	bmi.bmiHeader.biWidth = bmih.biWidth; 
	bmi.bmiHeader.biHeight = bmih.biHeight; 
	bmi.bmiHeader.biPlanes = bmih.biPlanes; 
	bmi.bmiHeader.biBitCount = bmih.biBitCount; 
	bmi.bmiHeader.biCompression = bmih.biCompression; 
	bmi.bmiHeader.biSizeImage = bmih.biSizeImage; 
	bmi.bmiHeader.biXPelsPerMeter = bmih.biXPelsPerMeter; 
	bmi.bmiHeader.biYPelsPerMeter = bmih.biYPelsPerMeter; 
	bmi.bmiHeader.biClrUsed = bmih.biClrUsed; 
	bmi.bmiHeader.biClrImportant = bmih.biClrImportant;

/*	file.Read(&bmi.bmiColors,((1<<bmih.biBitCount) * sizeof(RGBQUAD)));*/

	//HGLOBAL hmem2 = GlobalAlloc(GHND, (bmfh.bfSize - bmfh.bfOffBits)); 

	char *lpvBits =new char[bmfh.bfSize - bmfh.bfOffBits];

	file.ReadHuge(lpvBits,(bmfh.bfSize - bmfh.bfOffBits));
	file.Close();

//	GlobalUnlock(hmem2); 

	HBITMAP hBitmap = ::CreateDIBitmap(
    dc.GetSafeHdc(), &bmih, CBM_INIT,
    lpvBits, &bmi, DIB_RGB_COLORS);

	CBitmap bitmap;
	BITMAP bm;
	bitmap.Attach(hBitmap);
	bitmap.GetBitmap(&bm);
	
	dc.DrawState(CPoint(0, 0), CSize(bmih.biWidth,bmih.biHeight), &bitmap, DST_BITMAP);
	bitmap.DeleteObject();
	delete []lpvBits;	
}

