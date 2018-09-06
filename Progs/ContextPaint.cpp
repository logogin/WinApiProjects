#include <windows.h>

HINSTANCE hInstance;

char szClassName[]="WindowAppClass";
char text[80]="Default Attributes";

bool RegClass(WNDPROC Proc,LPCTSTR szName,UINT brBackGround)
{
	WNDCLASS wc;
	wc.style=CS_HREDRAW|CS_VREDRAW|/*CS_CLASSDC*/CS_OWNDC;
	wc.cbClsExtra=wc.cbWndExtra=0;
	wc.lpfnWndProc=Proc;
	wc.hInstance=hInstance;
	wc.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	wc.hCursor=LoadCursor(NULL,IDC_ARROW);
	wc.hbrBackground=(HBRUSH)(brBackGround+1);
	wc.lpszMenuName=NULL;
	wc.lpszClassName=szName;
	return (RegisterClass(&wc)!=0);
}

void ContAttr(HWND hwnd)
{
	HDC hdc=GetDC(hwnd);
	SetTextColor(hdc,RGB(0,0,255));
	SetBkColor(hdc,RGB(255,255,0));
	SetTextAlign(hdc,TA_CENTER);
	ReleaseDC(hwnd,hdc);
}

LRESULT CALLBACK WndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	static int cx,cy;
	switch (msg)
	{
	case WM_SIZE:
		cx=LOWORD(lParam);
		cy=HIWORD(lParam);
		return 0;
	case WM_PAINT:
	{	
		PAINTSTRUCT ps;
		HDC hdc=BeginPaint(hwnd,&ps);
		TextOut(hdc,cx/2,cy/2,text,strlen(text));
		EndPaint(hwnd,&ps);
		return 0;
	}
	case WM_LBUTTONDOWN:
	{
		HDC hdc=GetDC(hwnd);
		SetTextColor(hdc,RGB(255,0,255));
		SetBkColor(hdc,RGB(255,251,240));
		SetTextAlign(hdc,TA_CENTER);
		TextOut(hdc,cx/2,cy/2-60,"Changed Attributes",strlen("Changed Attributes"));
		ReleaseDC(hwnd,hdc);
		return 0;
	}
	case WM_RBUTTONDOWN:
	{
		ContAttr(hwnd);
		HDC hdc=GetDC(hwnd);
		TextOut(hdc,cx/2,cy/2,"Restored Attributes",strlen("Restored Attributes"));
		ReleaseDC(hwnd,hdc);
		return 0;
	}
	case WM_CREATE:
		return 0;

	case WM_COMMAND:
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
	HWND hwnd1,hwnd2;
	hInstance=hInst;
	if (!RegClass(WndProc,szClassName,COLOR_WINDOW))
		return false;
	hwnd1=CreateWindow(szClassName,"First Window",
		WS_OVERLAPPEDWINDOW|WS_VISIBLE,
		CW_USEDEFAULT,CW_USEDEFAULT,
		CW_USEDEFAULT,CW_USEDEFAULT,
		0,0,hInstance,NULL);
	if (!hwnd1)
		return false;
	hwnd2=CreateWindow(szClassName,"Second Window",
		WS_OVERLAPPEDWINDOW|WS_VISIBLE,
		CW_USEDEFAULT,CW_USEDEFAULT,
		CW_USEDEFAULT,CW_USEDEFAULT,
		0,0,hInstance,NULL);
	if (!hwnd2)
		return false;
	ContAttr(hwnd1);
	while (GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}