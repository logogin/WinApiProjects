#include <windows.h>
#include <commctrl.h>

#pragma comment(lib,"comctl32.lib")

#define ID_TOOLBAR 100

#define CM_FILE_NEW 1000
#define CM_FILE_OPEN 1001
#define CM_FILE_SAVE 1002
#define CM_FILE_QUIT 1003
#define CM_EDIT_CUT 2000
#define CM_EDIT_COPY 2001
#define CM_EDIT_PASTE 2002
#define CM_EDIT_DEL 2003
#define CM_EDIT_FIND 2004
#define CM_EDIT_REPLC 2005
#define CM_EDIT_MENU 2006 
#define CM_HELP_HELP 3000
#define CM_HELP_ABOUT 3001

HINSTANCE hInstance;

char szClassName[]="WindowAppClass";

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

BOOL CreateMenuItem(HMENU hMenu,char *str,UINT uIns,UINT uCom,
					HMENU hSubMenu,BOOL flag,UINT fType)
{
	MENUITEMINFO mii;
	mii.cbSize=sizeof(MENUITEMINFO);
	mii.fMask=MIIM_STATE|MIIM_TYPE|MIIM_SUBMENU|MIIM_ID;
	mii.fType=fType;
	mii.fState=MFS_ENABLED;
	mii.dwTypeData=str;
	mii.cch=sizeof(str);
	mii.wID=uCom;
	mii.hSubMenu=hSubMenu;
	return InsertMenuItem(hMenu,uIns,flag,&mii);
}

BOOL SetMenuItem(HMENU hMenu,UINT uIns,UINT fState,BOOL flag)
{
	MENUITEMINFO mii;
	mii.cbSize=sizeof(MENUITEMINFO);
	mii.fMask=MIIM_STATE|MIIM_ID;
	mii.fState=fState;
	mii.wID=uIns;
	return SetMenuItemInfo(hMenu,uIns,flag,&mii);
}

UINT GetMenuItem(HMENU hMenu,UINT uIns,BOOL flag)
{
	MENUITEMINFO mii;
	mii.cbSize=sizeof(MENUITEMINFO);
	mii.fMask=MIIM_STATE;
	GetMenuItemInfo(hMenu,uIns,flag,&mii);
	return mii.fState;
}

HWND CreateToolBar(HWND hwnd,DWORD dwStyle,UINT uCom)
{
	static TBBUTTON but[6];
	but[0].fsStyle=TBSTYLE_SEP;

	but[1].iBitmap=STD_FILEOPEN;
	but[1].idCommand=CM_FILE_OPEN;
	but[1].fsState=TBSTATE_ENABLED;
	but[1].fsStyle=TBSTYLE_GROUP;

	but[2].iBitmap=STD_FILESAVE;
	but[2].idCommand=CM_FILE_SAVE;
	but[2].fsState=TBSTATE_INDETERMINATE;
	but[2].fsStyle=TBSTYLE_GROUP;

	but[3].fsStyle=TBSTYLE_SEP;

	but[4].iBitmap=STD_FIND;
	but[4].idCommand=CM_EDIT_FIND;
	but[4].fsState=TBSTATE_HIDDEN;
	but[4].fsStyle=TBSTYLE_GROUP;

	but[5].iBitmap=STD_REPLACE;
	but[5].idCommand=CM_EDIT_REPLC;
	but[5].fsState=TBSTATE_HIDDEN;
	but[5].fsStyle=TBSTYLE_GROUP;

	return CreateToolbarEx(hwnd,dwStyle,uCom,0,HINST_COMMCTRL,
		IDB_STD_SMALL_COLOR,but,6,0,0,0,0,sizeof(TBBUTTON));
}

HACCEL CreateAccelTable(void)
{
	ACCEL Accel[8];
	Accel[0].fVirt=FVIRTKEY|FCONTROL;
	Accel[0].key=0x4e;
	Accel[0].cmd=CM_FILE_NEW;

	Accel[1].fVirt=FVIRTKEY|FCONTROL;
	Accel[1].key=0x4f;
	Accel[1].cmd=CM_FILE_OPEN;

	Accel[2].fVirt=FVIRTKEY|FCONTROL;
	Accel[2].key=0x53;
	Accel[2].cmd=CM_FILE_SAVE;

	Accel[3].fVirt=FVIRTKEY|FALT;
	Accel[3].key=0x73;
	Accel[3].cmd=CM_FILE_QUIT;

	Accel[4].fVirt=FVIRTKEY|FCONTROL;
	Accel[4].key=0x58;
	Accel[4].cmd=CM_EDIT_CUT;

	Accel[5].fVirt=FVIRTKEY|FCONTROL;
	Accel[5].key=0x56;
	Accel[5].cmd=CM_EDIT_PASTE;

	Accel[6].fVirt=FVIRTKEY|FCONTROL;
	Accel[6].key=0x43;
	Accel[6].cmd=CM_EDIT_COPY;

	Accel[7].fVirt=FVIRTKEY;
	Accel[7].key=0x2e;
	Accel[7].cmd=CM_EDIT_DEL;

	return CreateAcceleratorTable((LPACCEL)Accel,8);
}

LRESULT CALLBACK WndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	static HMENU hMainMenu,hFileMenu,hEditMenu,hHelpMenu;
	static HWND hToolBar;
	switch (msg)
	{
	case WM_SIZE:
	{
		MoveWindow(hToolBar,0,0,0,0,TRUE);
		return 0;
	}
	case WM_CREATE:
	{
		int i=0;
		hMainMenu=CreateMenu();
		SetMenu(hwnd,hMainMenu);
		hFileMenu=CreatePopupMenu();
		CreateMenuItem(hFileMenu,"&New\tCtrl+N",i++,CM_FILE_NEW,NULL,FALSE,MFT_STRING);
		CreateMenuItem(hFileMenu,"&Open\tCtrl+O",i++,CM_FILE_OPEN,NULL,FALSE,MFT_STRING);
		CreateMenuItem(hFileMenu,"&Save\tCtrl+S",i++,CM_FILE_SAVE,NULL,FALSE,MFT_STRING);
		CreateMenuItem(hFileMenu,NULL,i++,NULL,NULL,FALSE,MFT_SEPARATOR);
		CreateMenuItem(hFileMenu,"&Exit\tAlt+F4",i++,CM_FILE_QUIT,NULL,FALSE,MFT_STRING);
		SetMenuItem(hFileMenu,CM_FILE_SAVE,MFS_GRAYED,FALSE);
		hEditMenu=CreatePopupMenu();
		i=0;
		CreateMenuItem(hEditMenu,"C&ut\tCtrl+X",i++,CM_EDIT_CUT,NULL,FALSE,MFT_STRING);
		CreateMenuItem(hEditMenu,"&Paste\tCtrl+V",i++,CM_EDIT_PASTE,NULL,FALSE,MFT_STRING);
		CreateMenuItem(hEditMenu,"&Copy\tCtrl+C",i++,CM_EDIT_COPY,NULL,FALSE,MFT_STRING);
		CreateMenuItem(hEditMenu,"&Delete\tDel",i++,CM_EDIT_DEL,NULL,FALSE,MFT_STRING);
		CreateMenuItem(hEditMenu,NULL,i++,NULL,NULL,FALSE,MFT_SEPARATOR);
		CreateMenuItem(hEditMenu,"&Find",i++,CM_EDIT_FIND,NULL,FALSE,MFT_STRING);
		CreateMenuItem(hEditMenu,"&Replace",i++,CM_EDIT_REPLC,NULL,FALSE,MFT_STRING);
		hHelpMenu=CreatePopupMenu();
		i=0;
		CreateMenuItem(hHelpMenu,"&Help",i++,CM_HELP_HELP,NULL,FALSE,MFT_STRING);
		CreateMenuItem(hHelpMenu,NULL,i++,NULL,NULL,FALSE,MFT_SEPARATOR);
		CreateMenuItem(hHelpMenu,"&About",i++,CM_HELP_ABOUT,NULL,FALSE,MFT_STRING);
		i=0;
		CreateMenuItem(hMainMenu,"&File",i++,NULL,hFileMenu,FALSE,MFT_STRING);
		CreateMenuItem(hMainMenu,"&Edit",i++,CM_EDIT_MENU,hEditMenu,FALSE,MFT_STRING);
		CreateMenuItem(hMainMenu,"&Help",i++,NULL,hHelpMenu,FALSE,MFT_STRING);
		SetMenuItem(hMainMenu,CM_EDIT_MENU,MFS_GRAYED,FALSE);
		DrawMenuBar(hwnd);

		DWORD dwStyle=WS_CHILD|WS_VISIBLE|WS_DLGFRAME;
		hToolBar=CreateToolBar(hwnd,dwStyle,ID_TOOLBAR);
		return 0;
	}
	case WM_COMMAND:
	{
		char str[30];
		if (HIWORD(wParam)==1)
			strcpy(str,"Message from Accelerator");
		else
			strcpy(str,"Message from Menu");
		switch (LOWORD(wParam))
		{

		case CM_FILE_NEW:
			MessageBox(hwnd,"New",str,MB_OK);
			return 0;
		case CM_FILE_SAVE:
			SetMenuItem(hFileMenu,CM_FILE_OPEN,MFS_ENABLED,FALSE);
			SetMenuItem(hFileMenu,CM_FILE_SAVE,MFS_GRAYED,FALSE);
			SetMenuItem(hMainMenu,CM_EDIT_MENU,MFS_GRAYED,FALSE);
			
			SendMessage(hToolBar,TB_SETSTATE,(WPARAM)CM_FILE_OPEN,
				(LPARAM)MAKELONG(TBSTATE_ENABLED,0));
			SendMessage(hToolBar,TB_SETSTATE,(WPARAM)CM_FILE_SAVE,
				(LPARAM)MAKELONG(TBSTATE_INDETERMINATE,0));

			SendMessage(hToolBar,TB_SETSTATE,(WPARAM)CM_EDIT_FIND,
				(LPARAM)MAKELONG(TBSTATE_HIDDEN,0));
			SendMessage(hToolBar,TB_SETSTATE,(WPARAM)CM_EDIT_REPLC,
				(LPARAM)MAKELONG(TBSTATE_HIDDEN,0));

			MessageBox(hwnd,"Save",str,MB_OK);
			return 0;
		case CM_FILE_OPEN:
			SetMenuItem(hFileMenu,CM_FILE_OPEN,MFS_GRAYED,FALSE);
			SetMenuItem(hFileMenu,CM_FILE_SAVE,MFS_ENABLED,FALSE);
			SetMenuItem(hMainMenu,CM_EDIT_MENU,MFS_ENABLED,FALSE);
			SetMenuItem(hEditMenu,CM_EDIT_FIND,MFS_UNCHECKED,FALSE);
			SetMenuItem(hEditMenu,CM_EDIT_REPLC,MFS_UNCHECKED,FALSE);

			SendMessage(hToolBar,TB_SETSTATE,(WPARAM)CM_FILE_OPEN,
				(LPARAM)MAKELONG(TBSTATE_INDETERMINATE,0));
			SendMessage(hToolBar,TB_SETSTATE,(WPARAM)CM_FILE_SAVE,
				(LPARAM)MAKELONG(TBSTATE_ENABLED,0));
			
			SendMessage(hToolBar,TB_SETSTATE,(WPARAM)CM_EDIT_FIND,
				(LPARAM)MAKELONG(TBSTATE_ENABLED,0));
			SendMessage(hToolBar,TB_SETSTATE,(WPARAM)CM_EDIT_REPLC,
				(LPARAM)MAKELONG(TBSTATE_ENABLED,0));
			MessageBox(hwnd,"Open",str,MB_OK);
			return 0;
		case CM_FILE_QUIT:
			DestroyWindow(hwnd);
			return 0;
		case CM_EDIT_CUT:
			MessageBox(hwnd,"Cut",str,MB_OK);
			return 0;
		case CM_EDIT_PASTE:
			MessageBox(hwnd,"Paste",str,MB_OK);
			return 0;
		case CM_EDIT_COPY:
			MessageBox(hwnd,"Copy",str,MB_OK);
			return 0;
		case CM_EDIT_DEL:
			MessageBox(hwnd,"Delete",str,MB_OK);
			return 0;
		case CM_EDIT_FIND:
			if (GetMenuItem(hEditMenu,CM_EDIT_FIND,FALSE)==MFS_CHECKED)
			{
				SetMenuItem(hEditMenu,CM_EDIT_FIND,MFS_UNCHECKED,FALSE);
				SendMessage(hToolBar,TB_SETSTATE,(WPARAM)CM_EDIT_FIND,
					(LPARAM)MAKELONG(TBSTATE_ENABLED,0));
			}
			else
			{
				SetMenuItem(hEditMenu,CM_EDIT_FIND,MFS_CHECKED,FALSE);
				SendMessage(hToolBar,TB_SETSTATE,(WPARAM)CM_EDIT_FIND,
					(LPARAM)MAKELONG(TBSTATE_ENABLED|TBSTATE_CHECKED,0));
			}
			MessageBox(hwnd,"Find",str,MB_OK);
			return 0;
		case CM_EDIT_REPLC:
			if (GetMenuItem(hEditMenu,CM_EDIT_REPLC,FALSE)==MFS_CHECKED)
			{
				SetMenuItem(hEditMenu,CM_EDIT_REPLC,MFS_UNCHECKED,FALSE);
				SendMessage(hToolBar,TB_SETSTATE,(WPARAM)CM_EDIT_REPLC,
					(LPARAM)MAKELONG(TBSTATE_ENABLED,0));
			}
			else
			{
				SetMenuItem(hEditMenu,CM_EDIT_REPLC,MFS_CHECKED,FALSE);
				SendMessage(hToolBar,TB_SETSTATE,(WPARAM)CM_EDIT_REPLC,
					(LPARAM)MAKELONG(TBSTATE_ENABLED|TBSTATE_CHECKED,0));
			}
			MessageBox(hwnd,"Replace",str,MB_OK);
			return 0;
		case CM_HELP_HELP:
			MessageBox(hwnd,"Help",str,MB_OK);
			return 0;
		case CM_HELP_ABOUT:
			MessageBox(hwnd,"Demo of Accelerators","About Program",MB_OK);
			return 0;
		}
		return 0;
	}
	case WM_RBUTTONDOWN:
	{
		DWORD xyPos=GetMessagePos();
		WORD xPos=LOWORD(xyPos);
		WORD yPos=HIWORD(xyPos);

		HMENU hFloatMenu=CreatePopupMenu();
		int i=0;
		CreateMenuItem(hFloatMenu,"Cut",i++,CM_EDIT_CUT,NULL,FALSE,MFT_STRING);
		CreateMenuItem(hFloatMenu,"Copy",i++,CM_EDIT_COPY,NULL,FALSE,MFT_STRING);
		CreateMenuItem(hFloatMenu,"Paste",i++,CM_EDIT_PASTE,NULL,FALSE,MFT_STRING);
		TrackPopupMenu(hFloatMenu,
			TPM_CENTERALIGN|TPM_LEFTBUTTON|TPM_VCENTERALIGN,xPos,
			yPos,0,hwnd,NULL);
		return 0;
	}

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
	HACCEL hAccel=CreateAccelTable();
	while (GetMessage(&msg,0,0,0))
	{
		if (!hAccel||!TranslateAccelerator(hwnd,hAccel,&msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	DestroyAcceleratorTable(hAccel);
	return msg.wParam;
}