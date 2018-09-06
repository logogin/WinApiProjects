#if !defined(AFX_EMPLOYEES_H__1C15B272_652A_11D3_BA49_00600864785A__INCLUDED_)
#define AFX_EMPLOYEES_H__1C15B272_652A_11D3_BA49_00600864785A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Employees.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEmployees recordset

class CEmployees : public CRecordset
{
public:
	CEmployees(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CEmployees)

// Field/Param Data
	//{{AFX_FIELD(CEmployees, CRecordset)
	long	m_EmployeeID;
	CString	m_LastName;
	CString	m_FirstName;
	CString	m_Title;
	CString	m_Address;
	CString	m_City;
	CString	m_Country;
	CString	m_HomePhone;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEmployees)
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

#endif // !defined(AFX_EMPLOYEES_H__1C15B272_652A_11D3_BA49_00600864785A__INCLUDED_)
