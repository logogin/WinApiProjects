//////////////////////////////////////////////////////////////
// ������ MainFrm.h
// Copyright (c) 1999 ������ �., ��������� �.
//////////////////////////////////////////////////////////////

#ifndef __AFXEXT_H__
#include <afxext.h>         // ��� ��������� ���������� ������� 
#endif                      // CToolBar � CStatusBar

class CMainFrame : public CFrameWnd
{
// �����������
public:
  CMainFrame();

// ��������
public:
  void SetColumns(UINT nColumns); // ��������� ���-�� �������� ������ 
                                  // ������������ ���������

public:
  virtual ~CMainFrame();
  virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

  // �������� ������� ������� ���� �� ����
  BOOL CreateToolBar();
  BOOL CreatePaneBar();
  BOOL CreateStatusBar();

protected:  
  // ���������� ������� ������� ����������
  CStatusBar m_wndStatusBar;  // ������ ���������
  CToolBar   m_wndToolBar;    // ������ ������������ (������)
  CToolBar   m_wndPaneBar;    // ������ ������������ ���������
  CDialogBar m_wndDlgBar;     // ������ �������
  // �������������� ����� ������
  UINT       m_nPaneCol;      // ���-�� �������� ������ ������������ ���������
  CComboBox  m_comboBox;      // ��������������� ������ ��� ������ 
                              // ������������ (������)
  CFont      m_font;          // ����� ��� ���������������� ������

// ����������� ���������
protected:
  //{{AFX_MSG(CMainFrame)
  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct); // �������� ����
  afx_msg void OnViewPane(); // ������� ����������� ������ 
                             // ������������ ���������
  afx_msg void OnUpdateViewPane(CCmdUI* pCmdUI);
  afx_msg void OnSelChangePane(); // ���������� ��������� ������ 
                                  // ����������� ���������
  afx_msg void OnPane2column(); // ����������� ������ ����� ����������
  afx_msg void OnPane3column(); // �������� ������ ������������ ���������
  afx_msg void OnUpdatePane2column(CCmdUI* pCmdUI);
  afx_msg void OnUpdatePane3column(CCmdUI* pCmdUI);
  afx_msg void OnUpdateIndicatorIdle(CCmdUI* pCmdUI); // ��� ���������� 
                                             // ������� ������ ���������
  afx_msg void OnTimer(UINT nIDEvent); // ���������� �������
  //}}AFX_MSG

  // ����������� ����� ������ ��� ��������������� �������
  afx_msg void OnStyle(UINT nID); // ������ ������ ������������
  afx_msg void OnUpdateStyle(CCmdUI* pCmdUI);
  afx_msg void OnPane(UINT nID); // ������ ������������ ���������
  afx_msg void OnUpdatePane(CCmdUI* pCmdUI);

  DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
