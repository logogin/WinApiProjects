// Employees.cpp : implementation file
//

#include "stdafx.h"
#include "wwwdb.h"
#include "Employees.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEmployees

IMPLEMENT_DYNAMIC(CEmployees, CRecordset)

CEmployees::CEmployees(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CEmployees)
	m_EmployeeID = 0;
	m_LastName = _T("");
	m_FirstName = _T("");
	m_Title = _T("");
	m_Address = _T("");
	m_City = _T("");
	m_Country = _T("");
	m_HomePhone = _T("");
	m_nFields = 8;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CEmployees::GetDefaultConnect()
{
	return _T("ODBC;DSN=Sample InternetDB");
}

CString CEmployees::GetDefaultSQL()
{
	CString strQuery;

	strQuery.Format("SELECT DISTINCT EmployeeID, LastName, FirstName, Title, Address, City, Country, HomePhone"
        					" FROM Employees");

	return strQuery;
}

void CEmployees::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CEmployees)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[EmployeeID]"), m_EmployeeID);
	RFX_Text(pFX, _T("[LastName]"), m_LastName);
	RFX_Text(pFX, _T("[FirstName]"), m_FirstName);
	RFX_Text(pFX, _T("[Title]"), m_Title);
	RFX_Text(pFX, _T("[Address]"), m_Address);
	RFX_Text(pFX, _T("[City]"), m_City);
	RFX_Text(pFX, _T("[Country]"), m_Country);
	RFX_Text(pFX, _T("[HomePhone]"), m_HomePhone);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CEmployees diagnostics

#ifdef _DEBUG
void CEmployees::AssertValid() const
{
	CRecordset::AssertValid();
}

void CEmployees::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
