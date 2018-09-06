#include <iostream.h>
#include <stdlib.h>
#include <winsock.h>

#define LISTENER_PORT 4950

void main(int argn,char **argv)
{
	WORD wVersionRequested=MAKEWORD(2,2);
	WSADATA wsaData;

	SOCKET talker;
	sockaddr_in listener_addr;
	hostent *hostinfo;
	int numbytes;
		
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

	if ((hostinfo=gethostbyname("death"))==NULL) 
	{
		cerr<<"Cannot resolve host"<<endl;
		exit(1);
	}
	if ((talker=socket(AF_INET,SOCK_DGRAM,0))==-1) 
	{
		cerr<<"Socket creation filed"<<endl;
		exit(1);
	}
	listener_addr.sin_family=AF_INET;
	listener_addr.sin_port=htons(LISTENER_PORT);
	listener_addr.sin_addr= *((in_addr *)hostinfo->h_addr);
	memset(&(listener_addr.sin_zero),'\x0',8);

	if ((numbytes=sendto(talker,"ksjfhjdfhjksfhjdfh",strlen("ksjfhjdfhjksfhjdfh"),
		0,(sockaddr *)&listener_addr,sizeof(sockaddr)))==-1)
	{
		cerr<<"Sending message filed"<<endl;
		exit(1);	
	}
	cout<<"sent "<<numbytes<<" bytes to "<<inet_ntoa(listener_addr.sin_addr)<<endl;
	closesocket(talker); 

	WSACleanup();
}