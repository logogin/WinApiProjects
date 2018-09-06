/*************************************************************
Файл DragBox.h
Copyright (c) 1999 Мешков А., Тихомиров Ю.
*************************************************************/

// DragBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDragBox window

class CDragBox : public CDragListBox
{
// Construction
public:
	CDragBox();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDragBox)
	//}}AFX_VIRTUAL
  virtual void DrawInsert(int nItem);
  virtual UINT Dragging(CPoint pt);
  virtual void Dropped(int nSrcIndex, CPoint pt);

// Implementation
public:
	virtual ~CDragBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDragBox)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
