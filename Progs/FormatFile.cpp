// Pass.cpp
#include <afx.h>
#include <afxwin.h>
// Main entry point
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	CFile InputFile(_T("choosedate1.js"), CFile::modeRead);
	CFile OutputFile(_T("choosedate_formated.js"), CFile::modeCreate | CFile::modeWrite);

	ULONGLONG ulLength= InputFile.GetLength();
	ULONGLONG ulLastPosition = 0;
	ULONGLONG ulSize;

	BYTE ch;
	LPBYTE lpBuffer = NULL;
	for (ULONGLONG i=0; i<ulLength; i++)
	{
		InputFile.Read(&ch, sizeof(BYTE));
		if (ch == ';' || ch == '}')
		{
			InputFile.Seek(ulLastPosition, CFile::begin);
			ulSize = i-ulLastPosition;
			lpBuffer = new BYTE[ulSize + 2];
			InputFile.Read(lpBuffer, ulSize);
			lpBuffer[ulSize] = '\n';
			lpBuffer[ulSize + 1] = '\t';
			OutputFile.Write(lpBuffer, ulSize + 2);
			delete []lpBuffer;
			ulLastPosition = i;
		}
	}

	InputFile.Close();
	OutputFile.Close();
	return 0;
}
