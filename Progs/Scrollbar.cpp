#include <windows.h>

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
	static unsigned int yPos,yMin,yMax,yPage;
	static SCROLLINFO sInfo;
	switch (msg)
	{
	case WM_CREATE:
		yPos=yMin=1;yMax=200;yPage=10;
		sInfo.cbSize=sizeof(sInfo);
		sInfo.fMask=SIF_ALL;
		sInfo.nMin=yMin;
		sInfo.nMax=yMax;
		sInfo.nPage=yPage;
		sInfo.nPos=yPos;
		SetScrollInfo(hwnd,SB_VERT,&sInfo,true);
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
			sInfo.nPage-=1;
			yPos-=1;
			break;
		case SB_LINERIGHT:
			yPos+=1;
			sInfo.nPage+=1;
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
	if (yPos<yMin)
		yPos=yMin;
	sInfo.nPos=yPos;
	sInfo.fMask=SIF_POS|SIF_PAGE;
	if (sInfo.nPage<yPage||sInfo.nPage>yMax)
		sInfo.nPage=yPage;
	SetScrollInfo(hwnd,SB_VERT,&sInfo,true);
	return 0;
	
	case WM_KEYDOWN:
	switch(wParam)
	{
	case VK_HOME:
		if (HIBYTE(GetKeyState(VK_CONTROL)))
			SendMessage(hwnd,WM_VSCROLL,SB_TOP,0);
		break;
	case VK_END:
		if (HIBYTE(GetKeyState(VK_CONTROL)))
			SendMessage(hwnd,WM_VSCROLL,SB_BOTTOM,0);
		break;
	case VK_UP:
	if (HIBYTE(GetKeyState(VK_CONTROL)))
			SendMessage(hwnd,WM_VSCROLL,SB_LINELEFT,0);
		break;
	case VK_DOWN:
	if (HIBYTE(GetKeyState(VK_CONTROL)))
			SendMessage(hwnd,WM_VSCROLL,SB_LINERIGHT,0);
		break;
	case VK_PRIOR:
	if (HIBYTE(GetKeyState(VK_CONTROL)))
			SendMessage(hwnd,WM_VSCROLL,SB_PAGELEFT,0);
		break;
	case VK_NEXT:
	if (HIBYTE(GetKeyState(VK_CONTROL)))
			SendMessage(hwnd,WM_VSCROLL,SB_PAGERIGHT,0);
		break;
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