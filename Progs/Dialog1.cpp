#include <windows.h>
#include "Dialog.h"

#define ID_STATIC 2000
#define ID_BUTTON1 2001
#define ID_BUTTON2 2002
#define ID_BUTTON3 2003
#define ID_HELP 2004

HINSTANCE hInstance;
char szClass[]="WindowAppClass";

LRESULT CALLBACK DlgProc(HWND,UINT,WPARAM,LPARAM);

BOOL RegClass(WNDPROC Proc,LPCTSTR szName,UINT brBackground)
{
	WNDCLASS wc;
	wc.style=wc.cbClsExtra=wc.cbWndExtra=0;
	wc.lpfnWndProc=Proc;
	wc.hInstance=hInstance;
	wc.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	wc.hCursor=LoadCursor(NULL,IDC_ARROW);
	wc.hbrBackground=(HBRUSH)(brBackground+1);
	wc.lpszClassName=szClass;
	wc.lpszMenuName=(LPCTSTR)NULL;
	return (RegisterClass(&wc)!=0);
}

int CreateDlg(HWND hwnd)
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
	DlgItemTemplate(ptr,style,left,top,wItem,4*hItem+left,ID_STATIC,(LPSTR)"button",(LPSTR)stattxt);

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

	DialogBoxIndirect(hInstance,(LPDLGTEMPLATE)ptrdlg,hwnd,(DLGPROC)DlgProc);
	LocalFree(LocalHandle(ptrdlg));
	return 0;
}

LRESULT CALLBACK DlgProc(HWND hdlg,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch (msg)
	{
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDOK:
		case IDCANCEL:
		{
			EndDialog(hdlg,TRUE);
			return TRUE;
		}
		}
	}
	}
	return FALSE;
}

LRESULT CALLBACK WndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch (msg)
	{
	case WM_LBUTTONDOWN:
		CreateDlg(hwnd);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd,msg,wParam,lParam);
}

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInst,LPSTR lpszCmdLine,int CmdShow)
{
	MSG msg;
	HWND hwnd;
	::hInstance=hInstance;
	if (!RegClass(WndProc,szClass,COLOR_DESKTOP))
		return FALSE;
	int wScreen=GetSystemMetrics(SM_CXSCREEN);
	int hScreen=GetSystemMetrics(SM_CYSCREEN);
	hwnd=CreateWindow(szClass,"Dialog Panel",WS_OVERLAPPEDWINDOW|WS_VISIBLE,0,0,wScreen,hScreen,		
		0,0,hInstance,NULL);
	if (!hwnd)
		return FALSE;
	while (GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}