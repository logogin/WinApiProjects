// REditCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CREditCtrl window

class CREditCtrl : public CRichEditCtrl
{
// Construction
public:
	CREditCtrl();

// Attributes
public:

// Operations
public:
	void OnPaste();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CREditCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CREditCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CREditCtrl)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
