#include <iostream.h>
#include <stdlib.h>
#include <winsock.h>

#define SERVER_PORT 9110
#define BACKLOG 5

void main(int argn,char **argv)
{
	WORD wVersionRequested=MAKEWORD(2,2);
	WSADATA wsaData;

	SOCKET _server,client;
	sockaddr_in server_addr;
	sockaddr_in client_addr;

	int si_size;
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

	if ((_server=socket(AF_INET,SOCK_STREAM,0))==-1) 
	{
		cerr<<"Creating Socket filed"<<endl;
		exit(0);
	}
	if (setsockopt(_server,SOL_SOCKET,SO_REUSEADDR,(const char *)&optval,sizeof(optval))==-1)
	{
		cerr<<"Socket configuration filed"<<endl;
		exit(0);
	}

	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(SERVER_PORT);
	server_addr.sin_addr.S_un.S_addr=INADDR_ANY;
	memset(&(server_addr.sin_zero),'\x0',8);

	if (bind(_server,(sockaddr *)&server_addr,sizeof(sockaddr))==-1)
	{
		cerr<<"Socket binding filed"<<endl;
		exit(0);
	}

	if (listen(_server,BACKLOG)==-1) 
	{
		cerr<<"Socket connecting filed"<<endl;
		exit(0);
	}
	
	while(1)
	{
		si_size=sizeof(sockaddr_in);
		if ((client=accept(_server, (struct sockaddr *)&client_addr,&si_size)) == -1) 
		{
			cerr<<"Accepting connection filed"<<endl;
			continue;
		}
		cout<<"Server: got connection from "<<inet_ntoa(client_addr.sin_addr)<<endl;

		//close(serverockfd);
		if (send(client,"Hello, world!\n",14,0)==-1)
		{
			cerr<<"Sending message filed"<<endl;
			exit(0);
		}
		closesocket(client);
		
	}
	closesocket(_server);
	WSACleanup();
}