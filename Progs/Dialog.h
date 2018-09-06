#ifndef DIALOG_H
#define DIALOG_H

int nCopyAnsiToWideChar(LPWORD,LPSTR);
LPWORD lpwAlign(LPWORD);
void DlgTemplate(PWORD &,DWORD,int,int,int,int,int,LPSTR);
void DlgItemTemplate(PWORD &,DWORD,int,int,int,int,WORD,LPSTR,LPSTR);

int nCopyAnsiToWideChar(LPWORD lpWCStr,LPSTR lpAnsiln)
{
	int cchAnsi=lstrlen(lpAnsiln);
	return MultiByteToWideChar(GetACP(),MB_PRECOMPOSED,lpAnsiln,cchAnsi,lpWCStr,cchAnsi)+1;
}

LPWORD lpwAlign(LPWORD lpln)
{
	ULONG ul=(ULONG)lpln;
	ul+=3;
	ul>>=2;
	ul<<=2;
	return (LPWORD)ul;
}

void DlgTemplate(PWORD &ptr,DWORD lStyle,int items,int x,int y,int cx,int cy,LPSTR txt)
{
	*ptr++=LOWORD(lStyle);
	*ptr++=HIWORD(lStyle);
	*ptr++=0;
	*ptr++=0;
	*ptr++=items;
	*ptr++=x;
	*ptr++=y;
	*ptr++=cx;
	*ptr++=cy;
	*ptr++=0;
	*ptr++=0;
	ptr+=nCopyAnsiToWideChar(ptr,TEXT(txt));
	ptr=lpwAlign((LPWORD)ptr);
}

void DlgItemTemplate(PWORD &ptr,DWORD lStyle,int x,int y,int cx,int cy,WORD id,LPSTR classname,LPSTR txt)
{
	*ptr++=LOWORD(lStyle);
	*ptr++=HIWORD(lStyle);
	*ptr++=0;
	*ptr++=0;
	*ptr++=x;
	*ptr++=y;
	*ptr++=cx;
	*ptr++=cy;
	*ptr++=id;
	ptr+=nCopyAnsiToWideChar(ptr,TEXT(classname));
	ptr+=nCopyAnsiToWideChar(ptr,TEXT(txt));
	*ptr++=0;
	ptr=lpwAlign((LPWORD)ptr);
}

#endif DIALOG_H