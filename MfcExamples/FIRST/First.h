/////////////////////////////////////////////////////////
// ���� First.h
// Copyright (c) 1999 ������ �., ��������� �.
/////////////////////////////////////////////////////////

#ifndef __AFXWIN_H__
  #error ������� ���� �������� 'stdafx.h' ��� ��������� PCH
#endif

#include "resource.h"

class CFirstApp : public CWinApp
{
public:
  CFirstApp();

// ���������������� �������
// ClassWizard ��������� ����� ����������� �������
  //{{AFX_VIRTUAL(CFirstApp)
  public:
  virtual BOOL InitInstance();
  //}}AFX_VIRTUAL
};
