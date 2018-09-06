/*************************************************************
Файл ColorBox.h
Copyright (c) 1999 Мешков А., Тихомиров Ю.
*************************************************************/

// ColorBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CColorBox window

class CColorBox : public CCheckListBox
{
// Construction
public:
	CColorBox();

// Attributes
public:

// Operations
public:
	void AddColorItem(COLORREF color);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorBox)
	public:
	virtual int CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CColorBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(CColorBox)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
