// Pass.cpp
//
// Copyright (C) Toby Sharp, February 2000
// mailto:toby.sharp@mailexcite.com
//
// A simple utility to remove the password style from
// all existing edit boxes to show their true text content.
//
// Works correctly under Windows NT 4.0. Not tested for
// other Windows versions.
#include <tchar.h>

#include <windows.h>
//#include <winbase.h>

// Callback for EnumChildWindows
BOOL CALLBACK EnumChildProc(HWND hWnd, LPARAM lParam)
{
	static TCHAR szClass[512];

	// See if the current window is an edit control
	GetClassName(hWnd, szClass, 512);
	if (lstrcmp(szClass, "Button") == 0)
	{
		// Window is an edit control
		// Remove the password style if set
		SendMessage(hWnd, EM_SETPASSWORDCHAR, 0, 0);
		// And redraw
		InvalidateRect(hWnd, NULL, FALSE);
	}

	// Return TRUE to continue with window enumeration
	return TRUE;
}

// Main entry point
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	// Get desktop window -- the parent of all other windows
//	HWND hDesktop = GetDesktopWindow();
	
	// Enumerate all its children (and their children etc.)
	// calling EnumChildProc for each window
//	EnumChildWindows(hDesktop, &EnumChildProc, 0);
	//HWND hParent=(HWND)0x00090862;
	//HWND hWnd=FindWindowEx(hParent,NULL,_T("Button"),_T("Настройка"));
	//EnableWindow(hWnd,TRUE);
	//SYSTEM_INFO lpSystemInfo;
	//GetSystemInfo(&lpSystemInfo);
	//GetLargePageMinimum();
	//// And we're done
	HWND hParent=(HWND)0x001D00CC;
	HWND hWnd=FindWindowEx(hParent, NULL, _T("Button"), _T("Бинарные данные"));
	BOOL bVisible = ::IsWindowVisible(hWnd);
	::ShowWindow(hWnd, SW_SHOWNA);
	return 0;
}
