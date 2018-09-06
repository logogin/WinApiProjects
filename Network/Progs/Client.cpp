#include <iostream.h>
#include <stdlib.h>
#include <winsock.h>

#define SERVER_PORT 3490
#define MAXDATASIZE 100
#define BACKLOG 5

void main(int argn,char **argv)
{
	WORD wVersionRequested=MAKEWORD(2,2);
	WSADATA wsaData;

	SOCKET client;
	int data_size;
	char buffer[MAXDATASIZE];
	hostent *hostinfo;
	sockaddr_in server_addr;
	
//	int si_size;
	int optval=1;

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

	if ((hostinfo=gethostbyname("Death"))==NULL)
	{
		cerr<<"Cannot resolve host"<<endl;
		exit(0);
	}

	cout <<"Host name : "<<hostinfo->h_name<<endl;
	cout <<"IP Address :"<<inet_ntoa(*((in_addr *)hostinfo->h_addr))<<endl;

	cout<<endl;

	if ((client=socket(AF_INET,SOCK_STREAM,0))==-1) 
	{
		cerr<<"Creating Socket filed"<<endl;
		exit(0);
	}

	/*if (setsockopt(_server,SOL_SOCKET,SO_REUSEADDR,(const char *)&optval,sizeof(optval))==-1)
	{
		cerr<<"Socket configuration filed"<<endl;
		exit(0);
	}*/

	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(SERVER_PORT);
	server_addr.sin_addr=*((in_addr *)hostinfo->h_addr);;
	memset(&(server_addr.sin_zero),'\x0',8);

	if (connect(client,(sockaddr *)&server_addr,sizeof(sockaddr))==-1) 
	{
		cerr<<"Connection filed"<<endl;
		exit(0);
	}
	if ((data_size=recv(client,buffer,MAXDATASIZE-1,0))==-1)
	{
		cerr<<"Resiving filed"<<endl;
		exit(0);
	}

	buffer[data_size]='\x0';
	cout<<"Received: "<<buffer<<endl;
	
	closesocket(client);
	WSACleanup();
}