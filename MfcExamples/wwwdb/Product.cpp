// Product.cpp : implementation file
//

#include "stdafx.h"
#include "wwwdb.h"
#include "product.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProduct

IMPLEMENT_DYNAMIC(CProduct, CRecordset)

CProduct::CProduct(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CProduct)
	m_ProductID = 0;
	m_ProductName = _T("");
	m_UnitPrice = _T("");
	m_CompanyName = _T("");
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CProduct::GetDefaultConnect()
{
	return _T("ODBC;DSN=Sample InternetDB");
}

CString CProduct::GetDefaultSQL()
{
	CString strQuery;

	strQuery.Format("SELECT DISTINCT ProductID, ProductName, UnitPrice, CompanyName"
        					"  FROM Products, Suppliers"
				          " WHERE Suppliers.SupplierID = Products.SupplierID"
					        " ORDER BY ProductID");

	return strQuery;
}

void CProduct::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CProduct)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ProductID]"), m_ProductID);
	RFX_Text(pFX, _T("[ProductName]"), m_ProductName);
	RFX_Text(pFX, _T("[UnitPrice]"), m_UnitPrice);
	RFX_Text(pFX, _T("[CompanyName]"), m_CompanyName);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CProduct diagnostics

#ifdef _DEBUG
void CProduct::AssertValid() const
{
	CRecordset::AssertValid();
}

void CProduct::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
