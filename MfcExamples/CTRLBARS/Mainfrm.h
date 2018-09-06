//////////////////////////////////////////////////////////////
// Модуль MainFrm.h
// Copyright (c) 1999 Мешков А., Тихомиров Ю.
//////////////////////////////////////////////////////////////

#ifndef __AFXEXT_H__
#include <afxext.h>         // для включения объявлений классов 
#endif                      // CToolBar и CStatusBar

class CMainFrame : public CFrameWnd
{
// конструктор
public:
  CMainFrame();

// операции
public:
  void SetColumns(UINT nColumns); // изменение кол-ва столбцов панели 
                                  // инструментов рисования

public:
  virtual ~CMainFrame();
  virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

  // названия функций говорят сами за себя
  BOOL CreateToolBar();
  BOOL CreatePaneBar();
  BOOL CreateStatusBar();

protected:  
  // встроенные объекты панелей управления
  CStatusBar m_wndStatusBar;  // строка состояния
  CToolBar   m_wndToolBar;    // панель инструментов (команд)
  CToolBar   m_wndPaneBar;    // панель инструментов рисования
  CDialogBar m_wndDlgBar;     // панель диалога
  // дополнительные члены класса
  UINT       m_nPaneCol;      // кол-во столбцов панели инструментов рисования
  CComboBox  m_comboBox;      // комбинированный список для панели 
                              // инструментов (команд)
  CFont      m_font;          // шрифт для комбинированного списка

// обработчики сообщений
protected:
  //{{AFX_MSG(CMainFrame)
  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct); // создание окна
  afx_msg void OnViewPane(); // команда отображения панели 
                             // инструментов рисования
  afx_msg void OnUpdateViewPane(CCmdUI* pCmdUI);
  afx_msg void OnSelChangePane(); // обработчик изменения выбора 
                                  // инструмента рисования
  afx_msg void OnPane2column(); // обработчики команд смены количества
  afx_msg void OnPane3column(); // столбцов панели инструментов рисования
  afx_msg void OnUpdatePane2column(CCmdUI* pCmdUI);
  afx_msg void OnUpdatePane3column(CCmdUI* pCmdUI);
  afx_msg void OnUpdateIndicatorIdle(CCmdUI* pCmdUI); // для обновления 
                                             // области строки состояния
  afx_msg void OnTimer(UINT nIDEvent); // обработчик таймера
  //}}AFX_MSG

  // обработчики смены выбора для комбинированных списков
  afx_msg void OnStyle(UINT nID); // список стилей выравнивания
  afx_msg void OnUpdateStyle(CCmdUI* pCmdUI);
  afx_msg void OnPane(UINT nID); // список инструментов рисования
  afx_msg void OnUpdatePane(CCmdUI* pCmdUI);

  DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
