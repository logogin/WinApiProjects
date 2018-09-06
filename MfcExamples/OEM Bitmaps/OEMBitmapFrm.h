// OEMBitmapFrm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COEMBitmapFrame frame

class COEMBitmapFrame : public CFrameWnd
{
public:
	COEMBitmapFrame(); 

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COEMBitmapFrame)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~COEMBitmapFrame();

	// Generated message map functions
	//{{AFX_MSG(COEMBitmapFrame)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
