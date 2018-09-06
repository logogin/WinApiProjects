// ListCtrlFrm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CListCtrlFrame frame

class CListCtrlFrame : public CFrameWnd
{
public:
	CListCtrlFrame(); 

// Attributes
public:

// Operations
private:
  	void SetStyle(DWORD dwViewStyle);
    void OnButtonUp(CPoint point);

public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListCtrlFrame)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CListCtrlFrame();

	// Generated message map functions
	//{{AFX_MSG(CListCtrlFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewLargeIcons();
	afx_msg void OnViewSmallIcons();
	afx_msg void OnViewList();
	afx_msg void OnViewDetails();
	afx_msg void OnViewArrangeByName();
	afx_msg void OnViewArrangeByType();
	afx_msg void OnViewArrangeBySize();
	afx_msg void OnViewArrangeByDate();
	afx_msg void OnViewArrangeAutoArrange();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CListCtrl m_List;
	CImageList m_ImageNormal;
  CImageList m_ImageSmall;

	BOOL m_bDragging;
	int	m_iItemDrag;
	CPoint m_ptHotSpot;
	CPoint m_ptOrigin;
	CSize m_sizeDelta;
	CImageList *m_pImageListDrag;
};

/////////////////////////////////////////////////////////////////////////////
