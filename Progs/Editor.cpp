#include <windows.h>

#define ID_EDIT 1001
#define ID_LISTBOX 1002
#define ID_COMBOBOX 1003
#define ID_BUTTON1 1004
#define ID_BUTTON2 1005

HINSTANCE hInstance;

char szClassName[]="WindowAppClass";

bool RegClass(WNDPROC Proc,LPCTSTR szName,UINT brBackGround)
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

LRESULT CALLBACK WndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	static HWND hEdit,hListBox,hComboBox,hButton1,hButton2,hStatic;
	char buffer[80];
	int item;
	switch (msg)
	{
	case WM_CREATE:
		hStatic=CreateWindow("static","Enter line and press button \"OK\"",
			WS_CHILD|WS_VISIBLE|SS_CENTER,30,10,300,20,hwnd,(HMENU)0,hInstance,NULL);
		hEdit=CreateWindow("edit",NULL,WS_CHILD|WS_VISIBLE|WS_BORDER|ES_LEFT|ES_PASSWORD,
			30,40,300,30,hwnd,(HMENU)ID_EDIT,hInstance,NULL);
		hButton1=CreateWindow("button","Add to ListBox",WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
			40,85,100,30,hwnd,(HMENU)ID_BUTTON1,hInstance,NULL);
		hButton1=CreateWindow("button","Add to ComboBox",WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
			200,85,120,30,hwnd,(HMENU)ID_BUTTON2,hInstance,NULL);
		hListBox=CreateWindow("listbox",NULL,WS_CHILD|WS_VISIBLE|LBS_STANDARD|WS_HSCROLL,
			30,120,120,200,hwnd,(HMENU)ID_LISTBOX,hInstance,NULL);
		hComboBox=CreateWindow("combobox",NULL,WS_CHILD|WS_VISIBLE|WS_VSCROLL|CBS_SIMPLE|CBS_SORT,
			180,120,150,200,hwnd,(HMENU)ID_COMBOBOX,hInstance,NULL);
		SetFocus(hEdit);
		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_EDIT:
			if (HIWORD(wParam)==EN_ERRSPACE)
				MessageBox(hwnd,"Not Enough Memory","Error",MB_OK);
			return 0;
		case ID_BUTTON1:
		{
			/*LRESULT ul;*/
			int l;
			char buffer[80];
			/*ul=SendMessage(hEdit,EM_GETHANDLE,0,0);
			SendMessage(hEdit,EM_SETPASSWORDCHAR ,0,0);
			InvalidateRect(hEdit,NULL,true);*/
			l=SendMessage(hEdit,EM_LINELENGTH,0,0);
			SendMessage(hEdit,WM_GETTEXT,(WPARAM) (l+1),(LPARAM) buffer);
			SendMessage(hEdit,EM_GETLINE,0,(LPARAM)buffer);
			SendMessage(hListBox,LB_ADDSTRING,0,(LPARAM)buffer);
			//SetWindowText(hEdit,"\0x0");
			SetFocus(hEdit);
			return 0;
		}
		case ID_BUTTON2:
			SendMessage(hEdit,EM_GETLINE,0,(LPARAM)buffer);
			SendMessage(hComboBox,CB_ADDSTRING,0,(LPARAM)buffer);
			SetWindowText(hEdit,"\0x0");
			SetFocus(hEdit);
			return 0;
		case ID_LISTBOX:
			switch (HIWORD(wParam))
			{
			case LBN_ERRSPACE:
				MessageBox(hwnd,"Not Enough Memory","Error",MB_OK);
				return 0;
			case LBN_DBLCLK:
				item=SendMessage(hListBox,LB_GETCURSEL,0,0);
				if (item!=LB_ERR)
				{
					SendMessage(hListBox,LB_GETTEXT,item,(LPARAM)buffer);
					MessageBox(hwnd,buffer,"Selected Item",MB_OK);
				}
			}
		case ID_COMBOBOX:
			switch (HIWORD(wParam))
			{
			case CBN_ERRSPACE:
				MessageBox(hwnd,"Not Enough Memory","Error",MB_OK);
				return 0;
			case CBN_DBLCLK:
				item=SendMessage(hComboBox,CB_GETCURSEL,0,0);
				if (item!=CB_ERR)
				{
					SendMessage(hComboBox,CB_GETLBTEXT,item,(LPARAM)buffer);
					MessageBox(hwnd,buffer,"Selected Item",MB_OK);
				}
			}
		return 0;
		}
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
	hwnd=FindWindow("WindowAppClass","My Application");
	if (hwnd!=NULL)
	{
		
		if (MessageBox(hwnd,"Another Application found\nMove it to foreground?",
			"Message",MB_YESNO|MB_ICONSTOP)==IDYES)
		{
			if (IsIconic(hwnd))
				ShowWindow(hwnd,SW_RESTORE);
			SetForegroundWindow(hwnd);
		}
		return 0;
	}

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
	while (GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}