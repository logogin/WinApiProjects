#if !defined(AFX_WWWDB_H__E1C373A2_644D_11D3_BA30_00600864785A__INCLUDED_)
#define AFX_WWWDB_H__E1C373A2_644D_11D3_BA30_00600864785A__INCLUDED_

// WWWDB.H - Header file for your Internet Server
//    wwwdb Extension

#include "resource.h"

class CWwwdb : public CHttpServer
{
public:
	CWwwdb();
	~CWwwdb();

// Overrides
	// ClassWizard generated virtual function overrides
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//{{AFX_VIRTUAL(CWwwdb)
	public:
	virtual BOOL GetExtensionVersion(HSE_VERSION_INFO* pVer);
	//}}AFX_VIRTUAL
	virtual BOOL TerminateExtension(DWORD dwFlags);

	// TODO: Add handlers for your commands here.
  // For example:

	void Default(CHttpServerContext* pCtxt);

protected:
	void SearchProducts(CHttpServerContext *pCtxt);
	void SearchEmployes(CHttpServerContext* pCtxt);

public:
// команды разбора
	void Index(CHttpServerContext* pCtxt);
  void Search(CHttpServerContext* pCtxt, LPCTSTR pszMethod);

// вспомогательные функции
	void WriteSearchHeader(CHttpServerContext* pCtxt);
  void WriteProductHeader(CHttpServerContext* pCtxt);
  BOOL LoadLongResource(CString& str, UINT nID);
	void WritePageTitle(CHttpServerContext* pCtxt, UINT nID);

	DECLARE_PARSE_MAP()

	//{{AFX_MSG(CWwwdb)
	//}}AFX_MSG
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WWWDB_H__E1C373A2_644D_11D3_BA30_00600864785A__INCLUDED)
