#include <windows.h>

HINSTANCE hInstance;

char szClassName[]="WindowAppClass";
char text[80]="Default Attributes";

bool RegClass(WNDPROC Proc,LPCTSTR szName,UINT brBackGround)
{
	WNDCLASS wc;
	wc.style=CS_HREDRAW|CS_VREDRAW/*|CS_CLASSDC CS_OWNDC*/;
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
	static int cy;
	char font[]="Some Text";
	switch (msg)
	{
	case WM_SIZE:
	{
		cy=HIWORD(lParam);
		return 0;
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc=BeginPaint(hwnd,&ps);
		static LOGFONT lf;
		lf.lfCharSet=DEFAULT_CHARSET;
		lf.lfPitchAndFamily=DEFAULT_PITCH;
		strcpy(lf.lfFaceName,"");
		lf.lfHeight=20;
		lf.lfWidth=FW_BOLD;
		for (int i=0; i<10; i++)
		{
		//	lf.lfOrientation=lf.lfEscapement=i*100;
			HFONT hNFont=CreateFontIndirect(&lf);
			HFONT hOFont=(HFONT)SelectObject(hdc,hNFont);
			SetTextColor(hdc,RGB((i+1)*15,(i+1)*20,(i+1)*25));
			SetBkColor(hdc,RGB(255-(i+1)*15,255-(i+1)*20,255-(i+1)*25));
			TextOut(hdc,20,cy-100,font,strlen(font));
			SelectObject(hdc,hOFont);
			DeleteObject(hNFont);
		}
		EndPaint(hwnd,&ps);
		return 0;
	}
	case WM_CREATE:
//		cx=GetSystemMetrics(SM_CYCAPTION);
//		cy=GetSystemMetrics(SM_CYFRAME);
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
	if (!RegClass(WndProc,szClassName,COLOR_WINDOW))
		return false;
	hwnd=CreateWindow(szClassName,"First Window",
		WS_OVERLAPPEDWINDOW|WS_VISIBLE,
		CW_USEDEFAULT,CW_USEDEFAULT,
		CW_USEDEFAULT,CW_USEDEFAULT,
		0,0,hInstance,NULL);
	if (!hwnd)
		return false;
	while (GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}