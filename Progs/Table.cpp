#include <windows.h>
#include <math.h>

HINSTANCE hInstance;

char szClassName[]="WindowAppClass";
char text[80]="Default Attributes";
typedef struct
{
	char str[15];
	double val[50];
} COLUMN;

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

BOOL DrawLine(HDC hdc,int x0,int y0,int x,int y)
{
	MoveToEx(hdc,x0,y0,NULL);
	return LineTo(hdc,x,y);
}

LRESULT CALLBACK WndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	static COLUMN col[10];
	static int cx,cy,cxChar,cyChar;
	char font[]="Some Text";
	switch (msg)
	{
	case WM_SIZE:
	{
		cx=LOWORD(lParam);
		cy=HIWORD(lParam);
		return 0;
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc=BeginPaint(hwnd,&ps);
		char str[20];
		int left=cxChar,top=cyChar/2,dx=cxChar,dy=cyChar/4,hy=cyChar+2*dy,
			right=cx-cxChar,bottom=cy-cyChar,bounds[10];
		for (int j=0; j<10; j++)
		{
			bounds[j]=strlen(col[j].str);
			for (int i=0; i<50; i++)
			{
				_gcvt(col[j].val[i],7,str);
				int ss=strlen(str);
				if (bounds[j]<ss)
					bounds[j]=ss;
			}
			if (bounds[j]<=3)
				bounds[j]=4;
			if (bounds[j]>10)
				bounds[j]-=2;
			bounds[j]=cxChar*bounds[j];
		}
		int dd=left;
		for (int i=0; i<10; i++)
		{
			if (dd+bounds[i]<=right)
				dd+=bounds[i];
		}
		right=dd;

		RECT rc;
		GetWindowRect(hwnd,&rc);
		MoveWindow(hwnd,rc.left,rc.top,rc.right-rc.left-(cx-right)+dx,rc.bottom-rc.top,TRUE);
		SetTextAlign(hdc,TA_RIGHT);
		int y=top;
		DrawLine(hdc,left,y,right,y);
		int x=left;
		DrawLine(hdc,x,y,x,y+hy);
		for (i=0; i<10; i++)
		{
			x+=bounds[j];
			TextOut(hdc,x-dx,y+dy,col[i].str,strlen(col[i].str));
			DrawLine(hdc,x,y,x,y+hy);
		}
		y+=hy;
		DrawLine(hdc,left,y,right,y);
		i=0;
		while(i<50&&y<bottom)
		{
			x=left;
			DrawLine(hdc,x,y,x,y+hy);
			for (j=0; j<10; j++)
			{
				x+=bounds[j];
				if (j==0)
					_itoa((int)col[j].val[i],str,10);
				else
					_gcvt(col[j].val[i],7,str);
				TextOut(hdc,x-dx,y+dy,str,strlen(str));
				DrawLine(hdc,x,y,x,y+hy);
			}
			y+=hy;
			DrawLine(hdc,left,y,right,y);
			i++;
		}
		EndPaint(hwnd,&ps);
		return 0;
	}
	case WM_CREATE:
	{
		
		strcpy(col[0].str,"i");
		strcpy(col[1].str,"10*sin(i/10)");
		strcpy(col[2].str,"20*sin(i/20)");
		strcpy(col[3].str,"30*sin(i/30)");
		strcpy(col[4].str,"40*sin(i/40)");
		strcpy(col[5].str,"50*sin(i/50)");
		strcpy(col[6].str,"60*sin(i/60)");
		strcpy(col[7].str,"70*sin(i/70)");
		strcpy(col[8].str,"80*sin(i/80)");
		strcpy(col[9].str,"90*sin(i/90)");
		for (int i=0; i<50; i++)
		{
			col[0].val[i]=i;
			for (int j=1; j<10; j++)
				col[j].val[i]=10*sin(i/10./j);
		}
		TEXTMETRIC tm;
		HDC hdc=GetDC(hwnd);
		GetTextMetrics(hdc,&tm);
		ReleaseDC(hwnd,hdc);
		cyChar=tm.tmHeight+tm.tmExternalLeading;
		cxChar=tm.tmAveCharWidth+1;
		return 0;
	}

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