// REditCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "richedit.h"
#include "REditCtrl.h"

#include <afxole.h>
#include <richole.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CREditCtrl

CREditCtrl::CREditCtrl()
{
}

CREditCtrl::~CREditCtrl()
{
}

void CREditCtrl::OnPaste()
{
	HRESULT hr;
	IRichEditOle* piOle = GetIRichEditOle();
	
	if (piOle == NULL)
		return;

	piOle->AddRef();

  LPOLECLIENTSITE lpolesite;
	hr = piOle->GetClientSite(&lpolesite);
  if (hr != S_OK)
    AfxThrowOleException(hr);

  STGMEDIUM StgMedium;
	FORMATETC FormatEtc;

	COleDataObject data;
	if (!data.AttachClipboard())
		return;
	  
	data.BeginEnumFormats();
	while (data.GetNextFormat(&FormatEtc))
	{
		if (data.IsDataAvailable(FormatEtc.cfFormat, &FormatEtc))
			break;
	}
	if (!data.GetData(0, &StgMedium, &FormatEtc))
		return;

	COleClientItem item;
	if (!item.CreateFromClipboard(OLERENDER_DRAW, FormatEtc.cfFormat, &FormatEtc))
		return;

	REOBJECT reobject;
	reobject.cbStruct = sizeof(REOBJECT);
  item.GetClassID(&reobject.clsid);

  if (!(reobject.poleobj = item.m_lpObject))
		return;

  if (!(reobject.pstg = item.m_lpStorage))
		return;

  if (!(reobject.polesite = lpolesite))
		return;
  
	reobject.poleobj->AddRef();
  reobject.pstg->AddRef();
  reobject.polesite->AddRef();

  reobject.sizel.cx = reobject.sizel.cy = 0;
  reobject.dvaspect = item.GetDrawAspect();
  reobject.dwFlags = REO_RESIZABLE;
  reobject.dwUser = 0;

	hr = piOle->InsertObject(&reobject);
  if (hr != S_OK)
    AfxThrowOleException(hr);

	/*
	CHARRANGE chrg = { 0, 0};	
	LPDATAOBJECT lpdataobj;
	hr = piOle->GetClipboardData(&chrg, RECO_PASTE, &lpdataobj);
  if (hr != S_OK)
    AfxThrowOleException(hr);

	hr = piOle->ImportDataObject(lpdataobj,	0, NULL);
  if (hr != S_OK)
    AfxThrowOleException(hr);
	*/

	piOle->Release();
}

BEGIN_MESSAGE_MAP(CREditCtrl, CRichEditCtrl)
	//{{AFX_MSG_MAP(CREditCtrl)
		// NOTE - the ClassWizard will add and remove mapping macros here.
    //    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CREditCtrl message handlers

