#include <iostream.h>
#include <winsock2.h>
#include <stdlib.h>

#define PORT 9034

void main(int argn,char** argv)
{
	WORD wVersionRequested=MAKEWORD(2,2);
	WSADATA wsaData;

	fd_set master;
	fd_set read_fds;
	sockaddr_in server_addr;
	sockaddr_in client_addr;
	int fdmax;//ignored in WinSock
	SOCKET listener;
	SOCKET newfd;
	char buffer[256];
	int nbytes;
	int optval=1;
	int addrlen;

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

	FD_ZERO(&master);
	FD_ZERO(&read_fds);

	if ((listener=socket(AF_INET,SOCK_STREAM,0))==-1) 
	{
		cerr<<"Cannot create socket"<<endl;
		exit(1);
	}
	
	if (setsockopt(listener,SOL_SOCKET,SO_REUSEADDR,(const char *)&optval,sizeof(int))==-1)
	{
		cerr<<"Setting up socket filed"<<endl;
		exit(1);
	}
	
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.S_un.S_addr=INADDR_ANY;
	server_addr.sin_port=htons(PORT);
	memset(&(server_addr.sin_zero),'\x0',8);

	if (bind(listener,(sockaddr *)&server_addr,sizeof(server_addr))==-1)
	{
		cerr<<"Binding socket filed"<<endl;
		exit(1);
	}

	if (listen(listener,10)==-1) 
	{
		cerr<<"Listening socket filed"<<endl;
		exit(1);
	}

	FD_SET(listener,&master);
	//fdmax=listener;

	while(1) 
	{
		read_fds=master;
		if (select(fdmax+1/*ignored*/,&read_fds,NULL,NULL,NULL)==-1) 
		{
			cerr<<"Selection filed"<<endl;
			exit(1);
		}

		for(int i=0; i<master.fd_count; i++) 
			if (FD_ISSET(master.fd_array[i],&read_fds)) 
				if (read_fds.fd_array[i]==listener) 
				{
					addrlen=sizeof(client_addr);
					newfd=accept(listener,(sockaddr *)&client_addr,&addrlen);
					if (WSAGetLastError()==INVALID_SOCKET)
						cerr<<"Accepting filed"<<endl;
					else 
					{
						FD_SET(newfd,&master);
						cout<<"selectserver: new connection from "
							<<inet_ntoa(client_addr.sin_addr)<<" on socket "
							<<newfd<<endl;
					}
				} 
				else 
					if ((nbytes=recv(master.fd_array[i],buffer,sizeof(buffer),0))<=0) 
					{
						if (nbytes==0)
							cout<<"selectserver: socket "<<master.fd_array[i]<<" hung up\n";
						else 
							cerr<<"Resiving filed"<<endl;
						closesocket(master.fd_array[i]);
						FD_CLR(master.fd_array[i], &master);
					}
					else 
						for(int j=0; j<master.fd_count; j++) 
							//if (FD_ISSET(master.fd_array[i], &master)) 
								if (master.fd_array[j]!=listener&&j!=i) 
									if (send(master.fd_array[j],buffer,nbytes,0)==-1) 
										cerr<<"Sending filed"<<endl;
	}
	WSACleanup();
}