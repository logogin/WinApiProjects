// ClipPathFrm.cpp : implementation file
//

#include "stdafx.h"
#include "ClipPath.h"
#include "ClipPathFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClipPathFrame

CClipPathFrame::CClipPathFrame()
{
}

CClipPathFrame::~CClipPathFrame()
{
}


BEGIN_MESSAGE_MAP(CClipPathFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CClipPathFrame)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClipPathFrame message handlers

void CClipPathFrame::OnPaint() 
{
	CPaintDC dc(this); 

	CFont font;
	font.CreateFont(80, 30, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY,
		VARIABLE_PITCH | FF_DONTCARE, "Arial");

  // ��������� ������� ����� �������������� �����
  CFont *pFont = dc.SelectObject(&font);

  // �.�. ������ ��� ������������ ��������� ��� 
  // �������� ������ ���� CString, ��� ��������,
  // ����� ����� �������, ������������ ������
  // ������� � ������� ����������� ����������
  CString csText = _T("SelectClipPath");

  // ������ ������� ����� ������, ������� ����� 
  // �������� � �������������� ������ ������
  CSize sz = dc.GetTextExtent(csText); 

  // �������� ������� � �������� �������
  dc.BeginPath();

  // ������ �� ����� �������� �� ����� -
  // �� ������ �� ���������� ����� ������ ������ 
  dc.TextOut(10, 10, csText);

  // ��������� �������� �������
  dc.EndPath();

  // �� ������ ������� ������� � ������������� 
  // ������� ���������
  dc.SelectClipPath(RGN_XOR);

  // ������� �������������� ����� � ���������� 
  // ����������� ����� ����
  double delta = 2.0;
  for (int i = 0; i < sz.cy; i += (int)delta)
  {
    dc.MoveTo(10, 10+i);
    dc.LineTo(10+sz.cx, 10+i);

    delta *= 1.025;
  }
  
  // ������������� ����� ������������ �����
  dc.SelectObject(pFont);

  // �������� ������� � ���, ��� ����� ��������
  // ��������� ����� ��� ���������� ������� ����
  dc.SelectClipRgn(NULL);
}

