#include <windows.h>

HINSTANCE hInstance;

char szClassName[]="WindowAppClass";
char text[80]="Default Text";

bool RegClass(WNDPROC Proc,LPCTSTR szName,UINT brBackGround)
{
	WNDCLASS wc;
	wc.style=CS_HREDRAW|CS_VREDRAW;
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
		SetTextColor(hdc,RGB(255,0,255));
		SetBkColor(hdc,RGB(255,251,240));
		SetTextAlign(hdc,TA_CENTER);
		TextOut(hdc,cx/2,cy/2,text,strlen(text));
		EndPaint(hwnd,&ps);
		return 0;
	}
	case WM_LBUTTONDOWN:
	{
		/*strcpy(text,"Left button pressed");
		InvalidateRect(hwnd,NULL,true);*/

		HDC hdc=GetDC(hwnd);
		SetTextColor(hdc,RGB(0,0,255));
		SetBkColor(hdc,RGB(255,251,240));
		SetTextAlign(hdc,TA_CENTER);
		TextOut(hdc,cx/2,cy/2-60,"WM_BUTTON message",strlen("WM_BUTTON message"));
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