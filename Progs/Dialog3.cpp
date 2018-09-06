#include <windows.h>
#include <commctrl.h>
#include <prsht.h>
#include "Dialog.h"

#pragma comment(lib,"comctl32.lib")

#define ID_STATIC0 1000
#define ID_BUTTON1 1001
#define ID_BUTTON2 1002
#define ID_BUTTON3 1003
#define ID_HELP 1004
#define ID_STATIC1 2001
#define ID_LISTBOX 2002
#define ID_CREATEDLG 100
#define CM_FILE_OPEN 3001
#define CM_FILE_SAVE 3002
#define CM_FILE_QUIT 3003

HINSTANCE hInstance;

char szClassName[]="WindowAppClass";
char szForDlg[]="PopupWindow";
int wScreen;
int hScreen;
HWND hForDlg;

LRESULT CALLBACK DlgProc(HWND,UINT,WPARAM,LPARAM);
int CALLBACK PSCallback(HWND,UINT,LPARAM);

BOOL RegClass(WNDPROC Proc,LPCTSTR szName,UINT brBackGround)
{
	WNDCLASS wc;
	wc.style=wc.cbClsExtra=wc.cbWndExtra=0;
	wc.lpfnWndProc=Proc;
	wc.hInstance=hInstance;
	wc.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	wc.hCursor=LoadCursor(NULL,IDC_ARROW);
	wc.hbrBackground=(HBRUSH)(brBackGround+1);
	wc.lpszMenuName=NULL;
	wc.lpszClassName=szName;
	return (RegisterClass(&wc)!=0);
}

WORD *CreateDlg0(HWND hwnd)
{
	const char caption[]="Changing Program Mode";
	const char stattxt[]="You have to:";
	const char modeoff[]="close application";
	const char modedat[]="reload data";
	const char modepsw[]="change user name";
	WORD *ptr,*ptrdlg;

	int cx,cy;
	DWORD dlgunit=GetDialogBaseUnits();
	int dlgwunit=LOWORD(dlgunit);
	int dlghunit=HIWORD(dlgunit);

	int wDlg,hDlg,wItem,hItem,left,top;
	DWORD style=DS_CENTER|DS_MODALFRAME|WS_POPUPWINDOW|WS_CAPTION;
	ptr=ptrdlg=(WORD *)LocalAlloc(LPTR,2000);
	
	cx=dlgwunit;
	cy=dlghunit;

	wDlg=lstrlen(caption)*cx;
	hDlg=cy*5;

	DlgTemplate(ptr,style,7,0,0,wDlg,hDlg,(LPSTR)caption);

	hItem=cx;
	top=left=hItem/2;
	hItem+=left;

	wItem=(wDlg-2*left);
	style=WS_CHILD|WS_VISIBLE|BS_GROUPBOX|WS_TABSTOP;
	DlgItemTemplate(ptr,style,left,top,wItem,4*hItem+left,ID_STATIC0,(LPSTR)"button",(LPSTR)stattxt);

	wItem=lstrlen(modeoff)*cx+10;
	top+=hItem;
	style=BS_AUTORADIOBUTTON|WS_CHILD|WS_VISIBLE|WS_TABSTOP;
	DlgItemTemplate(ptr,style,hItem,top,wItem,hItem,ID_BUTTON1,(LPSTR)"button",(LPSTR)modeoff);

	wItem=lstrlen(modedat)*cx+10;
	top+=hItem;
	style=BS_AUTORADIOBUTTON|WS_CHILD|WS_VISIBLE;
	DlgItemTemplate(ptr,style,hItem,top,wItem,hItem,ID_BUTTON2,(LPSTR)"button",(LPSTR)modedat);

	wItem=lstrlen(modepsw)*cx+10;
	top+=hItem;
	style=BS_AUTORADIOBUTTON|WS_CHILD|WS_VISIBLE;
	DlgItemTemplate(ptr,style,hItem,top,wItem,hItem,ID_BUTTON3,(LPSTR)"button",(LPSTR)modepsw);

	wItem=(wDlg-2*(left+hItem))/3;
	top+=hItem+hItem/2+left;
	style=BS_DEFPUSHBUTTON|WS_VISIBLE|WS_CHILD|WS_TABSTOP;
	DlgItemTemplate(ptr,style,left,top,wItem,hItem,IDOK,(LPSTR)"button",(LPSTR)"Ok");

	style=BS_DEFPUSHBUTTON|WS_VISIBLE|WS_CHILD|WS_TABSTOP;
	DlgItemTemplate(ptr,style,left+wItem+hItem,top,wItem,hItem,IDCANCEL,
		(LPSTR)"button",(LPSTR)"Cancel");

	DlgItemTemplate(ptr,style,left+2*(wItem+hItem),top,wItem,hItem,ID_HELP,
		(LPSTR)"button",(LPSTR)"Help");

	return ptrdlg;
}

WORD *CreateDlg1(HWND hwnd)
{
	const char caption[]="Changing Program Mode";
	const char stattxt[]="You have to:";
	const char modeoff[]="close application";
	const char modedat[]="reload data";
	const char modepsw[]="change user name";
	WORD *ptr,*ptrdlg;

	int cx,cy;
	DWORD dlgunit=GetDialogBaseUnits();
	int dlgwunit=LOWORD(dlgunit);
	int dlghunit=HIWORD(dlgunit);

	int wDlg,hDlg,wItem,hItem,left,top;
	DWORD style=DS_CENTER|DS_MODALFRAME|WS_POPUPWINDOW|WS_CAPTION;
	ptr=ptrdlg=(WORD *)LocalAlloc(LPTR,2000);
	
	cx=dlgwunit;
	cy=dlghunit;

	wDlg=lstrlen(caption)*cx;
	hDlg=cy*5;

	DlgTemplate(ptr,style,7,0,0,wDlg,hDlg,(LPSTR)caption);

	hItem=cx;
	top=left=hItem/2;
	hItem+=left;

	wItem=(wDlg-2*left);
	style=WS_CHILD|WS_VISIBLE|BS_GROUPBOX|WS_TABSTOP;
	DlgItemTemplate(ptr,style,left,top,wItem,4*hItem+left,ID_STATIC1,(LPSTR)"button",(LPSTR)stattxt);

	wItem=lstrlen(modeoff)*cx+10;
	top+=hItem;
	style=BS_AUTORADIOBUTTON|WS_CHILD|WS_VISIBLE|WS_TABSTOP;
	DlgItemTemplate(ptr,style,hItem,top,wItem,hItem,ID_BUTTON1,(LPSTR)"button",(LPSTR)modeoff);

	wItem=lstrlen(modedat)*cx+10;
	top+=hItem;
	style=BS_AUTORADIOBUTTON|WS_CHILD|WS_VISIBLE;
	DlgItemTemplate(ptr,style,hItem,top,wItem,hItem,ID_BUTTON2,(LPSTR)"button",(LPSTR)modedat);

	wItem=lstrlen(modepsw)*cx+10;
	top+=hItem;
	style=BS_AUTORADIOBUTTON|WS_CHILD|WS_VISIBLE;
	DlgItemTemplate(ptr,style,hItem,top,wItem,hItem,ID_BUTTON3,(LPSTR)"button",(LPSTR)modepsw);

	wItem=(wDlg-2*(left+hItem))/3;
	top+=hItem+hItem/2+left;
	style=BS_DEFPUSHBUTTON|WS_VISIBLE|WS_CHILD|WS_TABSTOP;
	DlgItemTemplate(ptr,style,left,top,wItem,hItem,IDOK,(LPSTR)"button",(LPSTR)"Ok");

	style=BS_DEFPUSHBUTTON|WS_VISIBLE|WS_CHILD|WS_TABSTOP;
	DlgItemTemplate(ptr,style,left+wItem+hItem,top,wItem,hItem,IDCANCEL,
		(LPSTR)"button",(LPSTR)"Cancel");

	DlgItemTemplate(ptr,style,left+2*(wItem+hItem),top,wItem,hItem,ID_HELP,
		(LPSTR)"button",(LPSTR)"Help");

	return ptrdlg;
}

LRESULT CALLBACK DlgProc0(HWND hdlg,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch (msg)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		case IDCANCEL:
			return TRUE;
		return FALSE;
		}
	}
	return FALSE;
}

LRESULT CALLBACK DlgProc1(HWND hdlg,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
	{
		DrawMenuBar(hdlg);
		HWND hListBox=GetDlgItem(hdlg,ID_LISTBOX);
		SendMessage(hListBox,WM_SETREDRAW,FALSE,0L);
		SendMessage(hListBox,LB_ADDSTRING,0,(LPARAM)(LPSTR)"Green");
		SendMessage(hListBox,LB_ADDSTRING,0,(LPARAM)(LPSTR)"Red");
		SendMessage(hListBox,LB_ADDSTRING,0,(LPARAM)(LPSTR)"Pink");
		SendMessage(hListBox,LB_ADDSTRING,0,(LPARAM)(LPSTR)"Purpul");
		SendMessage(hListBox,LB_ADDSTRING,0,(LPARAM)(LPSTR)"Blue");
		SendMessage(hListBox,LB_ADDSTRING,0,(LPARAM)(LPSTR)"Yellow");
		SendMessage(hListBox,LB_ADDSTRING,0,(LPARAM)(LPSTR)"Fiolet");
		SendMessage(hListBox,LB_ADDSTRING,0,(LPARAM)(LPSTR)"Black");
		SendMessage(hListBox,LB_ADDSTRING,0,(LPARAM)(LPSTR)"White");
		SendMessage(hListBox,WM_SETREDRAW,TRUE,0L);
		InvalidateRect(hListBox,NULL,TRUE);
		return TRUE;
	}
	case WM_NOTIFY:
	{
		LPNMHDR pn=(LPNMHDR)lParam;
		switch(pn->code)
		{
		case PSN_SETACTIVE:
			MessageBox(hdlg,"PSN_SETACTIVE","WM_NOTIFY",MB_OK);
			return FALSE;
		case PSN_APPLY:
			MessageBox(hdlg,"PSN_APPLY","WM_NOTIFY",MB_OK);
			return FALSE;
		case PSN_QUERYCANCEL:
			MessageBox(hdlg,"PSN_QUERYCANCEL","WM_NOTIFY",MB_OK);
			return FALSE;
		case PSN_KILLACTIVE:
			MessageBox(hdlg,"PSN_KILLACTIVE","WM_NOTIFY",MB_OK);
			return FALSE;
		}
		return FALSE;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			int uSelectedItem;
			char buffer[255];
			HWND hListBox=GetDlgItem(hdlg,ID_LISTBOX);
			uSelectedItem=(int)SendMessage(hListBox,LB_GETCURSEL,0,0L);
			if (uSelectedItem!=LB_ERR)
			{
				SendMessage(hListBox,LB_GETTEXT,uSelectedItem,(LPARAM)buffer);
				SetWindowText(GetDlgItem(hdlg,ID_STATIC0),(LPCTSTR)buffer);
			}
			SendMessage(GetParent(hdlg),PSM_CHANGED,(WPARAM)(HWND)hdlg,0L);
			return TRUE;
		}
		}
	}
	}
	return FALSE;
}
LRESULT CALLBACK WndForDlg(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case ID_CREATEDLG:
		{
			static PROPSHEETPAGE pPage[2];
			static PROPSHEETHEADER pHeader;

			pPage[0].dwSize=sizeof(PROPSHEETPAGE);
			pPage[0].dwFlags=PSP_USETITLE|PSP_DLGINDIRECT;
			pPage[0].pResource=(DLGTEMPLATE *)CreateDlg0(hwnd);
			pPage[0].pfnDlgProc=(DLGPROC)DlgProc0;
			pPage[0].pszTitle="Modes";

			pPage[1].dwSize=sizeof(PROPSHEETPAGE);
			pPage[1].dwFlags=PSP_USETITLE|PSP_DLGINDIRECT;
			pPage[1].pResource=(DLGTEMPLATE *)CreateDlg1(hwnd);
			pPage[1].pfnDlgProc=(DLGPROC)DlgProc1;
			pPage[1].pszTitle="List";

			pHeader.dwSize=sizeof(PROPSHEETHEADER);
			pHeader.dwFlags=PSH_PROPSHEETPAGE|PSH_USECALLBACK;
			pHeader.hwndParent=hwnd;
			pHeader.pszCaption="Changing of Application properties";
			pHeader.nPages=sizeof(pPage)/sizeof(PROPSHEETPAGE);
			pHeader.ppsp=(LPCPROPSHEETPAGE)pPage;
			pHeader.pfnCallback=(PFNPROPSHEETCALLBACK)PSCallback;

			PropertySheet(&pHeader);
			LocalFree(LocalHandle(pPage[0].pResource));
			LocalFree(LocalHandle(pPage[1].pResource));

			return 0;

		}
		}
		return 0;
	}
	return DefWindowProc(hwnd,msg,wParam,lParam);
}

int CALLBACK PSCallback(HWND hdlg,UINT uMsg,LPARAM lParam)
{
	if (uMsg==PSCB_INITIALIZED)
	{
		RECT rc;
		GetWindowRect(hdlg,&rc);
		int l=rc.left;
		int t=rc.top;
		int w=rc.right-l;
		int h=rc.bottom-t;
		MoveWindow(hForDlg,(wScreen-w)/2,(hScreen-h)/2,w,h,TRUE);
	}
	return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	static WORD *ptr;
	static HMENU hMainMenu,hFileMenu;
	
	switch (msg)
	{
	case WM_LBUTTONDOWN:
		SendMessage(hForDlg,WM_COMMAND,ID_CREATEDLG,0L);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd,msg,wParam,lParam);
}

int WINAPI WinMain(HINSTANCE hInst,HINSTANCE hPervInstance,LPSTR lpCmdLine,int nCmdShow)
{
	MSG msg;
	HWND hwnd;
	hInstance=hInst;
	if (!RegClass(WndProc,szClassName,COLOR_WINDOW))
		return false;
	hwnd=CreateWindow(szClassName,"My Application",
		WS_OVERLAPPEDWINDOW|WS_VISIBLE,
		CW_USEDEFAULT,CW_USEDEFAULT,
		CW_USEDEFAULT,CW_USEDEFAULT,
		0,0,hInstance,NULL);
	if (!hwnd)
		return false;
	ShowWindow(hwnd,SW_SHOWDEFAULT);
	UpdateWindow(hwnd);
	if (!RegClass(WndForDlg,szForDlg,0))
		return FALSE;
	wScreen=GetSystemMetrics(SM_CXSCREEN);
	hScreen=GetSystemMetrics(SM_CYSCREEN);
	hForDlg=CreateWindow(szForDlg,NULL,WS_POPUP,0,0,10,10,hwnd,0,hInstance,NULL);
	while (GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}