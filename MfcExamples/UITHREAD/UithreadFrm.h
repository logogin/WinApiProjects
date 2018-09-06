/*************************************************************
Файл UIThreadFrm.h
Copyright (c) 1999 Мешков А., Тихомиров Ю.
*************************************************************/

// UIThreadFrm.h : header file
//

#include "EditWnd.h"
#include "LineThread.h"

//////////////////////////////////////////////////////////////
// A CLineWnd дочернее окно главного окна 
// приложения CUIThreadFrame. При этом CUIThreadFrame 
// выполняется в рамках основного потока приложения

//////////////////////////////////////////////////////////////
// CUIThreadFrame frame

class CUIThreadFrame : public CFrameWnd
{
public:
  CUIThreadFrame(); 

// Attributes
public:
  // окно-редактор
  CEditWnd m_wndEdit;
  // указатель на объект-поток
  CLineThread *m_pLineThread;

// Operations
public:

// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CUIThreadFrame)
  public:
  virtual BOOL Create(LPCTSTR lpszClassName, 
    LPCTSTR lpszWindowName, DWORD dwStyle, 
    const RECT& rect, CWnd* pParentWnd, UINT nID, 
    CCreateContext* pContext = NULL);
  virtual BOOL DestroyWindow();
  //}}AFX_VIRTUAL

// Implementation
protected:
  // обработка командных сообщений
  virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra,
    AFX_CMDHANDLERINFO* pHandlerInfo);

  // message handlers
  //{{AFX_MSG(CUIThreadFrame)
  afx_msg void OnSize(UINT nType, int cx, int cy);
  //}}AFX_MSG
  afx_msg LRESULT OnPrepareToClose(WPARAM wParam = 0, 
    LPARAM lParam = 0);

  DECLARE_MESSAGE_MAP()
};
