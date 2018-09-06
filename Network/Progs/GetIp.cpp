#include <iostream.h>
#include <stdlib.h>
#include <winsock.h>

void main(int argn,char **argv)
{
	hostent *h;

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

	if ((h=gethostbyname("Flash"))==NULL)
	{
		cerr<<"Cannot resolve host"<<endl;
		exit(0);
	}

	cout <<"Host name : "<<h->h_name<<endl;
	cout <<"IP Address :"<<inet_ntoa(*(( in_addr *)h->h_addr))<<endl;

	WSACleanup();
}