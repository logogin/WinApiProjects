#include <iostream.h>
#include <stdlib.h>
#include <winsock.h>

#define LISTENER_PORT 4950
#define MAXBUFFERSIZE 100
#define BACKLOG 5

void main(int argn,char **argv)
{
	WORD wVersionRequested=MAKEWORD(2,2);
	WSADATA wsaData;

	SOCKET listener;
	sockaddr_in listener_addr;
	sockaddr_in talker_addr;
	int addr_len,numbytes;
	char buffer[MAXBUFFERSIZE];
	
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

	if ((listener=socket(AF_INET,SOCK_DGRAM,0))==-1) 
	{
		cerr<<"Creating socket filed"<<endl;
		exit(1);
	}

	listener_addr.sin_family=AF_INET;
	listener_addr.sin_port=htons(LISTENER_PORT);
	listener_addr.sin_addr.S_un.S_addr=INADDR_ANY;
	memset(&listener_addr.sin_zero,'\x0',8);

	if (bind(listener,(sockaddr *)&listener_addr,sizeof(sockaddr))==-1) 
	{
		cerr<<"Binding socket filed"<<endl;
		exit(1);
	}

	addr_len = sizeof(sockaddr);

	if ((numbytes=recvfrom(listener,buffer,MAXBUFFERSIZE-1,0,
		(sockaddr *)&talker_addr,&addr_len)) == -1) 
	{

		cerr<<"Resiving message filed"<<endl;
		exit(1);
	}

	cout<<"got packet from "<<inet_ntoa(talker_addr.sin_addr)<<endl;
	cout<<"packet is "<<numbytes<<" bytes long\n";
	buffer[numbytes]='\x0';
	cout<<"packet contains :"<<buffer<<endl;
	closesocket(listener);
	WSACleanup();
}