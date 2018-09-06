
#include <windows.h>

#define ID_BUTTON1 3001
#define ID_BUTTON2 3002

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
	static HWND hButton1,hButton2;
	//static HWND hScroll;
	static HWND hxScroll,hyScroll,hxStatic,hyStatic;
	static int xPos,yPos,xMin,xMax,yMin,yMax;
	switch (msg)
	{
	case WM_CREATE:
		hxScroll=CreateWindow("scrollbar",NULL,WS_CHILD|WS_VISIBLE|SBS_HORZ,
			15,0,200,15,hwnd,(HMENU)0,hInstance,NULL);
		xPos=100;xMin=1;xMax=200;
		SetScrollRange(hxScroll,SB_CTL,xMin,xMax,true);
		SetScrollPos(hxScroll,SB_CTL,xPos,true);
		hxStatic=CreateWindow("static",NULL,WS_CHILD|WS_VISIBLE|SS_BLACKRECT,
			30,15,xPos-15,15,hwnd,(HMENU)0,hInstance,NULL);

		hyScroll=CreateWindow("scrollbar",NULL,WS_CHILD|WS_VISIBLE|SBS_VERT,
			0,15,15,200,hwnd,(HMENU)0,hInstance,NULL);
		yPos=100;yMin=1;yMax=200;
		SetScrollRange(hyScroll,SB_CTL,yMin,yMax,true);
		SetScrollPos(hyScroll,SB_CTL,yPos,true);
		hyStatic=CreateWindow("static",NULL,WS_CHILD|WS_VISIBLE|SS_GRAYRECT,
			15,30,15,yPos-15,hwnd,(HMENU)0,hInstance,NULL);

		/*hScroll=CreateWindow("scrollbar",NULL,WS_CHILD|SBS_SIZEGRIP,0,0,16,16,
			hwnd,(HMENU)0,hInstance,NULL);*/
		/*CreateWindow("static","NULL",WS_CHILD|WS_VISIBLE|SS_BLACKFRAME,20,40,100,50,
			hwnd,(HMENU)0,hInstance,NULL);*/
		CreateWindow("button","Group from two Buttons",WS_CHILD|WS_VISIBLE|BS_GROUPBOX,
			130,75,190,120,hwnd,(HMENU)0,hInstance,NULL);
		hButton1=CreateWindow("button","Upper Button",WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
			150,100,150,30,hwnd,(HMENU)ID_BUTTON1,hInstance,NULL);
		hButton2=CreateWindow("button","Lower Button",WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
			150,150,150,30,hwnd,(HMENU)ID_BUTTON2,hInstance,NULL);
		return 0;
	/*case WM_SIZE:
		ShowWindow(hScroll,SW_HIDE);
		return 0;
	case WM_LBUTTONDOWN:
		MoveWindow(hScroll,LOWORD(lParam)-8,HIWORD(lParam)-8,16,16,true);
		ShowWindow(hScroll,SW_NORMAL);
		return 0;*/
	case WM_HSCROLL:
		switch (LOWORD(wParam))
		{
		case SB_PAGELEFT:
			xPos-=10;
			break;

		case SB_PAGERIGHT:
			xPos+=10;
			break;
		case SB_LINELEFT:
			xPos-=1;
			break;
		case SB_LINERIGHT:
			xPos+=1;
			break;
		case SB_TOP:
			xPos=xMin;
			break;
		case SB_BOTTOM:
			xPos=xMax;
			break;
		case SB_THUMBPOSITION:
		case SB_THUMBTRACK:
			xPos=HIWORD(wParam);
			break;
		}
	if (xPos>xMax)
		xPos=xMax;
	if (xPos<xMin)
		xPos=xMin;
	SetScrollPos(hxScroll,SB_CTL,xPos,true);
	MoveWindow(hxStatic,30,15,xPos-15,15,true);
	return 0;

	case WM_VSCROLL:
		switch (LOWORD(wParam))
		{
		case SB_PAGELEFT:
			yPos-=10;
			break;
		case SB_PAGERIGHT:
			yPos+=10;
			break;
		case SB_LINELEFT:
			yPos-=1;
			break;
		case SB_LINERIGHT:
			yPos+=1;
			break;
		case SB_TOP:
			yPos=yMin;
			break;
		case SB_BOTTOM:
			yPos=yMax;
			break;
		case SB_THUMBPOSITION:
		case SB_THUMBTRACK:
			yPos=HIWORD(wParam);
			break;
		}
	if (yPos>yMax)
		yPos=yMax;
	if (xPos<yMin)
		yPos=yMin;
	SetScrollPos(hyScroll,SB_CTL,yPos,true);
	MoveWindow(hyStatic,15,30,15,yPos-15,true);
	return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_BUTTON1:
			MessageBox(hwnd,"Upper Button pressed","Button Message",MB_OK);
			SendMessage((HWND)lParam,BM_SETSTATE,true,0);
			if (SendMessage(hButton2,BM_GETSTATE,0,0))
				SendMessage(hButton2,BM_SETSTATE,false,0);
			return 0;
		case ID_BUTTON2:
			MessageBox(hwnd,"Lower Button pressed","Button Message",MB_OK);
			SendMessage((HWND)lParam,BM_SETSTATE,true,0);
			if (SendMessage(hButton1,BM_GETSTATE,0,0))
				SendMessage(hButton1,BM_SETSTATE,false,0);
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
	//static HWND hButton;
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
	/*hButton=CreateWindow("button","Button Example",WS_CHILD|WS_VISIBLE|BS_DEFPUSHBUTTON,
		0,0,200,20,hwnd,(HMENU)ID_BUTTON1,hInstance,NULL);*/
	UpdateWindow(hwnd);
	while (GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}