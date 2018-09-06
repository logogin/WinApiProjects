/////////////////////////////////////////////////////////
// Файл First.h
// Copyright (c) 1999 Мешков А., Тихомиров Ю.
/////////////////////////////////////////////////////////

#ifndef __AFXWIN_H__
  #error сначала надо включить 'stdafx.h' для поддержки PCH
#endif

#include "resource.h"

class CFirstApp : public CWinApp
{
public:
  CFirstApp();

// Переопределяемые функции
// ClassWizard описывает здесь виртуальные функции
  //{{AFX_VIRTUAL(CFirstApp)
  public:
  virtual BOOL InitInstance();
  //}}AFX_VIRTUAL
};
