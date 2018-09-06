#if !defined(AFX_PRODUCT_H__D7A3EE61_6398_11D3_B578_A19A6A02716F__INCLUDED_)
#define AFX_PRODUCT_H__D7A3EE61_6398_11D3_B578_A19A6A02716F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Product.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProduct recordset

class CProduct : public CRecordset
{
public:
	CProduct(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CProduct)

// Field/Param Data
	//{{AFX_FIELD(CProduct, CRecordset)
	long	m_ProductID;
	CString	m_ProductName;
	CString	m_UnitPrice;
	CString	m_CompanyName;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProduct)
	public:
	virtual CString GetDefaultConnect();    // Default connection string
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRODUCT_H__D7A3EE61_6398_11D3_B578_A19A6A02716F__INCLUDED_)
