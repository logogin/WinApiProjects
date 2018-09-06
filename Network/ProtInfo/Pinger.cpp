#include <iostream.h>
#include <winsock2.h>
#include "Memlib.h"
#include "IpHeader.h"
#include "IcmpHeader.h"

/*#define xmalloc(size) HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,(size))
#define xfree(ptr) HeapFree(GetProcessHeap(),0,(ptr))*/

#define STATUS_FAILED 0xFFFF
#define MAX_PACKET_SIZE 64
#define MAX_DATA_SIZE MAX_PACKET_SIZE-IP_HEADER_SIZE-ICMP_HEADER_SIZE_ECHO

SOCKET icmp_socket;
int timeout=1000;
char hostname[80]="bullshit";
char buffer[MAX_PACKET_SIZE];
LARGE_INTEGER frequency1;
LARGE_INTEGER counter1;
LARGE_INTEGER frequency2;
LARGE_INTEGER counter2;

hostent *hostinfo;
sockaddr_in dest,source;
IcmpHeader icmp_packet;

void dump_data(const char *data,const u_char size)
{
	cout<<endl;
	for (int i=0; i<size; i++)
	{
		cout<<hex2string(data[i],2)<<" "<<flush;
		if (!((i+1)%4))
			cout<<"  "<<flush;
		if (!((i+1)%8))
			cout<<endl;
	}
}

void InitWinSock(void)
{
	WORD wVersionRequested=MAKEWORD(2,2);
	WSADATA wsaData;

	if (WSAStartup(wVersionRequested, &wsaData) != 0)
	{
		cerr<<"WSAStartup failed.\n";
		exit(STATUS_FAILED);
	}

	cout<<"WINSock Initalisation ... "<<endl;
	cout<<"Current version request: "
		<<char(LOBYTE(wVersionRequested)+0x30)
		<<"."<<char(HIBYTE(wVersionRequested)+0x30)<<endl;
	
	cout<<"Highest version support: "
		<<char(LOBYTE(wsaData.wHighVersion)+0x30)
		<<"."<<char(HIBYTE(wsaData.wHighVersion)+0x30)<<endl;

	cout<<endl;

	if((icmp_socket=WSASocket(AF_INET,SOCK_RAW,IPPROTO_ICMP,NULL,0,0))==INVALID_SOCKET)
	{
		cerr<<"Socket creation filed "<<WSAGetLastError()<<endl;
		ExitProcess(STATUS_FAILED);
	}

	if(setsockopt(icmp_socket,SOL_SOCKET,SO_RCVTIMEO,
		(char*)&timeout,sizeof(timeout))==SOCKET_ERROR)
	{
		cerr<<"Socket configuration filed "<<WSAGetLastError()<<endl;
		ExitProcess(STATUS_FAILED);
	}
	if(setsockopt(icmp_socket,SOL_SOCKET,SO_SNDTIMEO,
		(char*)&timeout,sizeof(timeout))==SOCKET_ERROR)
	{
		cerr<<"Socket configuration filed "<<WSAGetLastError()<<endl;
		ExitProcess(STATUS_FAILED);
	}
}

void read_icmp(const u_short bytes)
{
	//LARGE_INTEGER counter;
	//LARGE_INTEGER recived_counter;

	IpHeader *ip_packet=&icmp_packet;
	ip_packet->ReadHeader(buffer);
	icmp_packet.ReadHeader(buffer+ip_packet->GetIHL(),bytes-ip_packet->GetIHL());

	dump_data(icmp_packet.GetIcmpDataPtr(),ICMP_HEADER_SIZE+ICMP_HEADER_SIZE_ECHO+12);
	cout<<endl;

	if (bytes<MAX_DATA_SIZE)
		cout<<"Too few bytes from "<<ip_packet->GetASource()<<endl;

	if (icmp_packet.GetType()!= ICMP_TYPE_ECHOREPLY)
	{
		cout<<"Non ECHO reply packet "<<icmp_packet.GetType()<<endl;
		return;
	}
	u_short id=(u_short)GetCurrentProcessId();
	if (icmp_packet.GetID()!=id) 
	{
		cout<<"Someone else's packet!"<<endl;
		return;
	
	}
	QueryPerformanceFrequency(&frequency2);
	QueryPerformanceCounter(&counter2);
	cout<<bytes<<" bytes from "<<ip_packet->GetASource()<<flush;
	cout<<" icmp_seq = "<<icmp_packet.GetSeq()<<flush;
	dump_data((char *)&counter1,sizeof(counter1));
	cout<<endl;
	pcopy(&counter1,icmp_packet.GetDataPtr(),sizeof(counter1));

	dump_data((char *)&counter1,sizeof(counter1));
	cout<<endl;

	cout<<" time: "<<100*(float)(counter2.QuadPart
		-counter1.QuadPart)/frequency1.QuadPart<<" ms "<<flush;
	cout<<"TTL="<<(int)ip_packet->GetTTL()<<endl;
}

void send_icmp(void)
{
	char *icmp_data;
	//LARGE_INTEGER counter;
	u_short seq_num=0;
	short bytesnum;
	int fromlen=sizeof(source);

	hostinfo=gethostbyname(hostname);
	memcpy(&dest.sin_addr,hostinfo->h_addr_list[0],hostinfo->h_length);
	dest.sin_family=hostinfo->h_addrtype;
	//icmp_packet.FillHeader(ICMP_TYPE_ECHO,ICMP_CODE_ECHO);
	icmp_data=(char *)palloc(MAX_DATA_SIZE);
	
	//icmp_packet.AddData(icmp_data,MAX_DATA_SIZE);
	
	while (1)
	{
		for (int i=0; i<MAX_DATA_SIZE; i++)
			icmp_data[i]='0';
		QueryPerformanceCounter(&counter1);
		memcpy(icmp_data,&counter1,sizeof(counter1));
		icmp_packet.CreateEchoRequest((u_short)GetCurrentProcessId(),seq_num++,icmp_data,MAX_DATA_SIZE);
		icmp_packet.SetCRC();
		QueryPerformanceFrequency(&frequency1);
		
		if ((bytesnum=sendto(icmp_socket,icmp_packet.GetIcmpDataPtr(),
			icmp_packet.GetTotalLength(),0,(sockaddr *)&dest,sizeof(dest)))==SOCKET_ERROR)
		{
			cerr<<"Sending filed "<<WSAGetLastError()<<endl;
			ExitProcess(STATUS_FAILED);
		}
		if (bytesnum<icmp_packet.GetTotalLength())
			cout<<"Wrote "<<bytesnum<<" bytes"<<endl;

		if ((bytesnum=recvfrom(icmp_socket,buffer,MAX_PACKET_SIZE,
			0,(sockaddr *)&source,&fromlen))==WSAETIMEDOUT)
			cout<<"Timed out "<<endl;
			
		else
		{
			if (bytesnum==SOCKET_ERROR)
			{
				cerr<<"Reciving filed "<<WSAGetLastError()<<endl;
				ExitProcess(STATUS_FAILED);
			}
			
			read_icmp(bytesnum);
		}
		Sleep(1000);
	}
}

void main()
{
	InitWinSock();
	send_icmp();
	closesocket(icmp_socket);
	WSACleanup();
}