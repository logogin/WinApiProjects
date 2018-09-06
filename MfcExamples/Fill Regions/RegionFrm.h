// RegionFrm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRegionFrame frame

class CRegionFrame : public CFrameWnd
{
public:
	CRegionFrame(); 

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRegionFrame)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CRegionFrame();

	// Generated message map functions
	//{{AFX_MSG(CRegionFrame)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
