#include <iostream.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "Memlib.h"
#include "IpHeader.h"
#include "IcmpHeader.h"

#define STATUS_FAILED 0xFFFF
#define MAX_PACKET_SIZE 64
#define MAX_DATA_SIZE MAX_PACKET_SIZE-IP_HEADER_SIZE-ICMP_HEADER_SIZE_ECHO

SOCKET icmp_socket;
int timeout=1000;
char hostname[80]="bullshit";
char buffer[MAX_PACKET_SIZE];
LARGE_INTEGER frequency;
hostent *hostinfo;
sockaddr_in dest,source;
IcmpHeader icmp_packet;

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

/*void read_icmp(const u_short bytes)
{
	LARGE_INTEGER counter;
	LARGE_INTEGER recived_counter;

	IpHeader *ip_packet=&icmp_packet;
	ip_packet->ReadHeader(buffer);
	icmp_packet.ReadHeader(buffer+ip_packet->GetIHL(),bytes-ip_packet->GetIHL());
	if (bytes<MAX_DATA_SIZE)
		cout<<"Too few bytes from "<<ip_packet->GetASource()<<endl;

	if (icmp_packet.GetID()!=(u_short)GetCurrentProcessId()) 
	{
		cout<<"Someone else's packet!"<<endl;
		return ;
	}

	if (icmp_packet.GetType()==ICMP_TYPE_ECHOREPLY)
	{
		cout<<"ECHO reply packet "<<icmp_packet.GetType()<<endl;
		end_flag=true;
		//return;
	}
	else
		if (icmp_packet.GetType()!=ICMP_TYTE_EXCEEDED&&
			icmp_packet.GetCode()!=ICMP_TYPE_EXCEEDED_TTL)
		{
			cout<<"Non TTL Exceeded packet"<<endl;
			return;
		}
	
	
	cout<<bytes<<" bytes from "<<ip_packet->GetASource()<<flush;
	cout<<" icmp_seq = "<<icmp_packet.GetSeq()<<flush;
	QueryPerformanceCounter(&counter);
	pcopy(&recived_counter,icmp_packet.GetDataPtr(),sizeof(recived_counter));
	cout<<" time: "<<100*(float)(counter.QuadPart
		-recived_counter.QuadPart)/frequency.QuadPart<<" ms "<<flush;
	cout<<"TTL="<<(int)ip_packet->GetTTL()<<endl;
}*/

void send_icmp(void)
{
	char *icmp_data;
	//LARGE_INTEGER frequency;
	u_short seq_num=0;
	short bytesnum;
	int fromlen=sizeof(source);
	int ttl;
	bool end_flag=false;
	LARGE_INTEGER counter;
	LARGE_INTEGER recived_counter;
	float min_time;

	//int ttllen=sizeof(ttl);

	hostinfo=gethostbyname(hostname);
	memcpy(&dest.sin_addr,hostinfo->h_addr_list[0],hostinfo->h_length);
	dest.sin_family=hostinfo->h_addrtype;
	//icmp_packet.FillHeader(ICMP_TYPE_ECHO,ICMP_CODE_ECHO);
	icmp_data=(char *)palloc(MAX_DATA_SIZE);
	
	//icmp_packet.AddData(icmp_data,MAX_DATA_SIZE);
	QueryPerformanceFrequency(&frequency);
	for (int i=0; i<30&&!end_flag; i++)
	{
		cout<<i+1<<") "<<flush;
		for (int j=0; j<4; j++)
		{
			pmemset(icmp_data,MAX_DATA_SIZE,'0');
			/*for (int i=0; i<MAX_DATA_SIZE; i++)
			icmp_data[i]='0';*/
			QueryPerformanceCounter(&counter);
			memcpy(icmp_data,&counter,sizeof(counter));
			icmp_packet.CreateEchoRequest((u_short)GetCurrentProcessId(),seq_num++,icmp_data,MAX_DATA_SIZE);
			icmp_packet.SetCRC();
			
			ttl=i+1;
			if(setsockopt(icmp_socket,IPPROTO_IP,IP_TTL,(char*)&(ttl),sizeof(ttl))==SOCKET_ERROR)
			{
				cerr<<"Socket configuration filed "<<WSAGetLastError()<<endl;
				ExitProcess(STATUS_FAILED);
			}
		
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
				IpHeader *ip_packet=&icmp_packet;
				ip_packet->ReadHeader(buffer);
				icmp_packet.ReadHeader(buffer+ip_packet->GetIHL(),bytesnum-ip_packet->GetIHL());
				if (bytesnum<MAX_DATA_SIZE)
					cout<<"Too few bytes from "<<ip_packet->GetASource()<<endl;

				if (icmp_packet.GetID()!=(u_short)GetCurrentProcessId()) 
				{
					cout<<"Someone else's packet!"<<endl;
					//return;
				}

				if (icmp_packet.GetType()==ICMP_TYPE_ECHOREPLY)
				{
				//	cout<<"ECHO reply packet "<<icmp_packet.GetType()<<endl;
					end_flag=true;

				}
				else
				if (icmp_packet.GetType()!=ICMP_TYPE_EXCEEDED&&
					icmp_packet.GetCode()!=ICMP_CODE_EXCEEDED_TTL)
				{
					cout<<"Non TTL Exceeded packet"<<endl;
					//return;
				}
				//cout<<bytesnum<<" bytes from "<<ip_packet->GetASource()<<flush;
				//cout<<" icmp_seq = "<<icmp_packet.GetSeq()<<flush;
				QueryPerformanceCounter(&counter);
				pcopy(&recived_counter,icmp_packet.GetDataPtr(),sizeof(recived_counter));
				cout<<"From "<<ip_packet->GetASource()<<" "<<flush;
				cout<<100*(float)(counter.QuadPart-recived_counter.QuadPart)/frequency.QuadPart<<" ms  "<<endl;
			}
		}
		cout<<endl;
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