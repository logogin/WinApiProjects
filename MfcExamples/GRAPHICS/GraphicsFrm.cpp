/*************************************************************
���� GraphicsFrm.cpp
Copyright (c) 1999 ������ �., ��������� �.
*************************************************************/

// GraphicsFrm.cpp : implementation file
//

#include "stdafx.h"
#include "Graphics.h"
#include "GraphicsFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CGraphicsFrame

CGraphicsFrame::CGraphicsFrame()
{
}

CGraphicsFrame::~CGraphicsFrame()
{
}


BEGIN_MESSAGE_MAP(CGraphicsFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CGraphicsFrame)
	ON_WM_PAINT()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphicsFrame message handlers

void CGraphicsFrame::OnPaint() 
{
	CPaintDC dc(this); 

	CRect rect;
	GetClientRect(&rect);

	CBrush brush(::GetSysColor(COLOR_WINDOW));
	dc.FillRect(&rect, &brush);
}

void CGraphicsFrame::OnClose() 
{
  // ��� ����, ����� �������� ���������� � �������
  // ���������� ��������� �������� �����������,
  // ������ ������� ��������� �� ����, ��� ����� 
  // ������� ������� ���� ����������. ���� ������ 
  // ��������� � ������� ExitInstance ������� ����������
  // �������� ��������� �������� ���������, �.�.
  // ���������� ��������� � ���� ������ ����� ��������
  // � ����� ����� ����������� "�����" �� �����
	((CGraphicsApp *)AfxGetApp())->CancelThreads();
	
	CFrameWnd::OnClose();
}
