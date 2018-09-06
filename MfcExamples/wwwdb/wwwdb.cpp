// WWWDB.CPP - Implementation file for your Internet Server
//    wwwdb Extension

#include "stdafx.h"
#include "wwwdb.h"
#include "product.h"
#include "employees.h"

///////////////////////////////////////////////////////////////////////
// The one and only CWinApp object
// NOTE: You may remove this object if you alter your project to no
// longer use MFC in a DLL.

static const TCHAR szHTMLType[] = _T("CustomHTML");

CWinApp theApp;

///////////////////////////////////////////////////////////////////////
// command-parsing map

BEGIN_PARSE_MAP(CWwwdb, CHttpServer)
	DEFAULT_PARSE_COMMAND(Index, CWwwdb)
	ON_PARSE_COMMAND(Index, CWwwdb, ITS_EMPTY)
	ON_PARSE_COMMAND(Search, CWwwdb, ITS_PSTR)
	ON_PARSE_COMMAND_PARAMS("Method")
END_PARSE_MAP(CWwwdb)


///////////////////////////////////////////////////////////////////////
// The one and only CWwwdb object

CWwwdb theExtension;


///////////////////////////////////////////////////////////////////////
// CWwwdb implementation

CWwwdb::CWwwdb()
{
}

CWwwdb::~CWwwdb()
{
}

BOOL CWwwdb::GetExtensionVersion(HSE_VERSION_INFO* pVer)
{
	// Call default implementation for initialization
	CHttpServer::GetExtensionVersion(pVer);

	// Load description string
	TCHAR sz[HSE_MAX_EXT_DLL_NAME_LEN+1];
	ISAPIVERIFY(::LoadString(AfxGetResourceHandle(),
			IDS_SERVER, sz, HSE_MAX_EXT_DLL_NAME_LEN));
	_tcscpy(pVer->lpszExtensionDesc, sz);
	return TRUE;
}

BOOL CWwwdb::TerminateExtension(DWORD dwFlags)
{
	// extension is being terminated
	//TODO: Clean up any per-instance resources
	return TRUE;
}

///////////////////////////////////////////////////////////////////////
// CWwwdb command handlers

void CWwwdb::Default(CHttpServerContext* pCtxt)
{
	StartContent(pCtxt);
	WriteTitle(pCtxt);

	*pCtxt << _T("This default message was produced by the Internet");
	*pCtxt << _T(" Server DLL Wizard. Edit your CWwwdb::Default()");
	*pCtxt << _T(" implementation to change it.\r\n");

	EndContent(pCtxt);
}

// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CWwwdb, CHttpServer)
	//{{AFX_MSG_MAP(CWwwdb)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

BOOL CWwwdb::LoadLongResource(CString& str, UINT nID)
{
	HRSRC hRes;
	HINSTANCE hInst = AfxGetResourceHandle();
	BOOL bResult = FALSE;

	hRes = FindResource(hInst, MAKEINTRESOURCE(nID), szHTMLType);
	if (hRes == NULL)
		ISAPITRACE1("Error: Resource %d could not be found\r\n", nID);
	else
	{
		DWORD dwSize = SizeofResource(hInst, hRes);
		if (dwSize == 0)
		{
			str.Empty();
			bResult = TRUE;
		}
		else
		{
			LPTSTR pszStorage = str.GetBufferSetLength(dwSize);

			HGLOBAL hGlob = LoadResource(hInst, hRes);
			if (hGlob != NULL)
			{
				LPVOID lpData = LockResource(hGlob);

				if (lpData != NULL)
				{
					memcpy(pszStorage, lpData, dwSize);
					bResult = TRUE;
				}

				FreeResource(hGlob);
			}
		}
	}

#ifdef _DEBUG
	if (!bResult)
		str.Format(_T("<b>Could not find string %d</b>"), nID);
#endif

	return bResult;
}

void CWwwdb::WritePageTitle(CHttpServerContext* pCtxt, UINT nID)
{
	CString strTitle;
	CString strAddOn;

	strTitle.LoadString(IDS_INDEX_TITLE);

	if (strAddOn.LoadString(nID))
	{
		strTitle += ": ";
		strTitle += strAddOn;
	}

	*pCtxt << "<title>";
	*pCtxt << strTitle;
	*pCtxt << "</title>";
}

void CWwwdb::WriteSearchHeader(CHttpServerContext* pCtxt)
{
	CString strOutput;
	LoadLongResource(strOutput, IDS_SEARCH_HEADER);
	*pCtxt << strOutput;
}

void CWwwdb::WriteProductHeader(CHttpServerContext* pCtxt)
{
	CString strOutput;
	LoadLongResource(strOutput, IDS_PRODUCT_HEADER);
	*pCtxt << strOutput;
}

///////////////////////////////////////////////////////////////////////
// CInternetDb command handlers

void CWwwdb::Index(CHttpServerContext* pCtxt)
{
	StartContent(pCtxt);
	WritePageTitle(pCtxt, IDS_INDEX_TITLE);

	CString strOutput;
	LoadLongResource(strOutput, IDS_HTML_INDEX);
	*pCtxt << strOutput;

	EndContent(pCtxt);
}

void CWwwdb::Search(CHttpServerContext* pCtxt, LPCTSTR pszMethod)
{
	StartContent(pCtxt);
	WritePageTitle(pCtxt, IDS_SEARCH_TITLE);

	if (_tcscmp(pszMethod, _T("ByEmployees")) == 0)
		SearchEmployes(pCtxt);
	else if (_tcscmp(pszMethod, _T("ByProducts")) == 0)
		SearchProducts(pCtxt);
	else
	{
		//LoadLongResource(strOutput, IDS_HTML_LOOKUPMETHOD);
		//*pCtxt << strOutput;
		//EndContent(pCtxt);
		//return;
	}

  // и заканчиваем страницу
	EndContent(pCtxt);
}

void CWwwdb::SearchEmployes(CHttpServerContext *pCtxt)
{
  CString strOutput;

	CString strConnect(_T("DSN=Sample InternetDB;UID=sa;PWD=;"));

	try
  {
		CDatabase db;

		if (!db.OpenEx(strConnect,
			             CDatabase::openReadOnly | CDatabase::noOdbcDialog))
		{
			*pCtxt << _T("ODBC Datasource 'Sample InternetDB' could not be opened<br>\r\n");
			*pCtxt << _T("Did you set it up as a <i>system</i> data source?<br>\r\n");
		}
		else
		{
			CEmployees employees(&db);

			if (employees.Open())
			{
				if (employees.IsBOF())
					*pCtxt << _T("Sorry, no employees are available at this time.<br>\r\n");
				else
				{
					BOOL bFirstRow = TRUE;

					while (!employees.IsEOF())
					{
						if (bFirstRow == TRUE)
						{
							WriteSearchHeader(pCtxt);
							bFirstRow = FALSE;
						}

            // формируем строку в формате HTML
						strOutput.Format(IDS_EMPLROW,
								             employees.m_EmployeeID,
								             (LPCTSTR) employees.m_LastName,
								             (LPCTSTR) employees.m_FirstName,
                             (LPCTSTR) employees.m_Title,
                             (LPCTSTR) employees.m_Address,
								             (LPCTSTR) employees.m_City,
                             (LPCTSTR) employees.m_Country,
                             (LPCTSTR) employees.m_HomePhone);

            // и выводим ее на страницу
					  *pCtxt << strOutput;

						employees.MoveNext();
					}
				}
				employees.Close();
			}
			else
				*pCtxt << _T("Couldn't open record set<br>\r\n");

			db.Close();
		}
	}
	catch (CDBException* pEx)
	{
		*pCtxt << _T("InternetDB Failed: Couldn't open data source\r\n");
    
    *pCtxt << strConnect;
    *pCtxt << _T("\r\n");

		TCHAR szError[1024];
		if (pEx->GetErrorMessage(szError, sizeof(szError)))
		{
			*pCtxt << szError;
			*pCtxt << _T("\r\n");
		}
	}

  // после вывода всех записей корректно закрываем таблицу
	*pCtxt << _T("</TABLE>");
}

void CWwwdb::SearchProducts(CHttpServerContext *pCtxt)
{
  CString strOutput;

	CString strConnect(_T("DSN=Sample InternetDB;UID=sa;PWD=;"));

	try
  {
		CDatabase db;

		if (!db.OpenEx(strConnect,
			             CDatabase::openReadOnly | CDatabase::noOdbcDialog))
		{
			*pCtxt << _T("ODBC Datasource 'Sample InternetDB' could not be opened<br>\r\n");
			*pCtxt << _T("Did you set it up as a <i>system</i> data source?<br>\r\n");
		}
		else
		{
			CProduct product(&db);

			if (product.Open())
			{
				if (product.IsBOF())
					*pCtxt << _T("Sorry, no products are available at this time.<br>\r\n");
				else
				{
					BOOL bFirstRow = TRUE;

					while (!product.IsEOF())
					{
						if (bFirstRow == TRUE)
						{
							WriteProductHeader(pCtxt);
							bFirstRow = FALSE;
						}

            // формируем строку в формате HTML
						strOutput.Format(IDS_PRODROW,
								             product.m_ProductID,
								             (LPCTSTR) product.m_ProductName,
								             (LPCTSTR) product.m_UnitPrice,
								             (LPCTSTR) product.m_CompanyName);

            // и выводим ее на страницу
					  *pCtxt << strOutput;

            product.MoveNext();
					}
				}
				product.Close();
			}
			else
				*pCtxt << _T("Couldn't open record set<br>\r\n");

			db.Close();
		}
	}
	catch (CDBException* pEx)
	{
		*pCtxt << _T("InternetDB Failed: Couldn't open data source\r\n");
    
    *pCtxt << strConnect;
    *pCtxt << _T("\r\n");

		TCHAR szError[1024];
		if (pEx->GetErrorMessage(szError, sizeof(szError)))
		{
			*pCtxt << szError;
			*pCtxt << _T("\r\n");
		}
	}

  // после вывода всех записей корректно закрываем таблицу
	*pCtxt << _T("</TABLE>");
}


///////////////////////////////////////////////////////////////////////
// If your extension will not use MFC, you'll need this code to make
// sure the extension objects can find the resource handle for the
// module.  If you convert your extension to not be dependent on MFC,
// remove the comments arounn the following AfxGetResourceHandle()
// and DllMain() functions, as well as the g_hInstance global.

/****

static HINSTANCE g_hInstance;

HINSTANCE AFXISAPI AfxGetResourceHandle()
{
	return g_hInstance;
}

BOOL WINAPI DllMain(HINSTANCE hInst, ULONG ulReason,
					LPVOID lpReserved)
{
	if (ulReason == DLL_PROCESS_ATTACH)
	{
		g_hInstance = hInst;
	}

	return TRUE;
}

****/
