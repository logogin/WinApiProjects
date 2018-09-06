// ImageDragFrm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CImageDragFrame frame

class CImageDragFrame : public CFrameWnd
{
public:
	CImageDragFrame(); 

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageDragFrame)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CImageDragFrame();

	// Generated message map functions
	//{{AFX_MSG(CImageDragFrame)
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
  CImageList m_List;
  CPoint m_pt;
  BOOL m_Drag;
};

/////////////////////////////////////////////////////////////////////////////
