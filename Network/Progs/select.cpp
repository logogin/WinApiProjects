#include <iostream.h>
#include <stdlib.h>
#include <winsock2.h>

#define STDIN 0

void main(int argn,char** argv)
{
	WORD wVersionRequested=MAKEWORD(2,2);
	WSADATA wsaData;

	if (WSAStartup(wVersionRequested, &wsaData) != 0)
	{
		cerr<<"WSAStartup failed.\n";
		exit(0);
	}

	cout<<"WINSock Initalisation ... "<<endl;
	cout<<"Current version request: "
		<<char(LOBYTE(wVersionRequested)+0x30)
		<<"."<<char(HIBYTE(wVersionRequested)+0x30)<<endl;
	
	cout<<"Highest version support: "
		<<char(LOBYTE(wsaData.wHighVersion)+0x30)
		<<"."<<char(HIBYTE(wsaData.wHighVersion)+0x30)<<endl;

	cout<<endl;

	timeval tv;
	fd_set readfds;
	tv.tv_sec = 2;
	tv.tv_usec = 500000;
	FD_ZERO(&readfds);
	FD_SET(STDIN, &readfds);
	select(STDIN+1,&readfds,NULL,NULL,&tv);

	if (FD_ISSET(STDIN, &readfds))
		cout<<"A key was pressed"<<endl;
	else
		cout<<"Time out"<<endl;

	WSACleanup();
}