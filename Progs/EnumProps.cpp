#include <tchar.h>
#include <windows.h>
#include <stdio.h>

BOOL CALLBACK PropEnumProcEx(HWND hwnd,
    LPTSTR lpszString,
    HANDLE hData,
    ULONG_PTR dwData)
{ 
    static int nProp = 1;    // property counter 
	printf("\tWinProp %d:  %s", nProp++, lpszString);
    return TRUE; 
}

// Callback for EnumChildWindows
BOOL CALLBACK EnumChildProc(HWND hWnd, LPARAM lParam)
{
	static TCHAR szClass[512];
	GetClassName(hWnd, szClass, 512);
	printf("hWnd=%X, className=%s\n", hWnd, szClass);
	EnumPropsEx(hWnd, PropEnumProcEx, lParam);
	return TRUE;
}

// Main entry point
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	HWND hParent=(HWND)0x00070970;
	EnumChildWindows(hParent, &EnumChildProc, NULL);
	return 0;
}
