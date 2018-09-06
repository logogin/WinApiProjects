#include "Includes.h"
//#include "Globals.h"
/*#include <iostream.h>
#include <winsock2.h>
#include <conio.h>
#include <stdlib.h>*/
#include "IpHeader.h"
#include "TcpHeader.h"
#include "UdpHeader.h"

#define SIO_RCVALL	0x98000001
#define BUFFERSIZE 0xFFFF

SOCKET listener;
unsigned long flag=1;

char buffer[BUFFERSIZE];

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

void display_tcpheader(const char *buffer)
{
	TcpHeader tcph(buffer); 

	cout<<"TCP Header :"<<endl;
	cout<<"Source port : "<<tcph.tcpSource_port
		<<" Destination port : "<<tcph.tcpDestination_port<<endl;
	cout<<"Sequence number : "<<tcph.tcpSeq_num
		<<" Acknowledgment number : "<<tcph.tcpAck_num<<endl;
	cout<<"Data offset : "<<(int)tcph.tcpData_offset
		<<" Struct size : "<<TCP_HEADER_SIZE<<endl;
	cout<<"Reserved : "<<(int)tcph.tcpReserved<<endl;
	cout<<"URG : "<<(int)tcph.tcpControl_bits.tcphc_urg
		<<"  ACK : "<<(int)tcph.tcpControl_bits.tcphc_ack
		<<"  PSH : "<<(int)tcph.tcpControl_bits.tcphc_psh
		<<"  RST : "<<(int)tcph.tcpControl_bits.tcphc_rst
		<<"  SYN : "<<(int)tcph.tcpControl_bits.tcphc_syn
		<<"  FIN : "<<(int)tcph.tcpControl_bits.tcphc_fin<<endl;
	cout<<"Window : "<<tcph.tcpWindow<<endl;
	cout<<"Checksum : "<<hex2string(tcph.tcpChecksum,4)<<endl;
	cout<<"Urgent Pointer : "<<tcph.tcpUrgent_pointer<<endl;
	cout<<"Options : "<<tcph.options<<endl;	
	cout<<endl;
	dump_data(buffer,TCP_HEADER_SIZE);
//	getch();
}

void display_udpheader(const char *buffer)
{
	UdpHeader udph(buffer);

	cout<<"Udp Header :"<<endl;
	cout<<"Source port : "<<udph.udpSource_port
		<<" Destination port : "<<udph.udpDestination_port<<endl;
	cout<<"Total Length : "<<udph.udpLength<<" Struct size : "<<UDP_HEADER_SIZE<<endl;
	cout<<"Checksum : "<<udph.udpChecksum<<endl;
	cout<<"Datagram follows : "<<udph.datagram<<endl;
	cout<<endl;
//	getch();
}

void display_ipheader(const char *buffer)
{
	hostent *hostinfo=NULL;
	protoent *protinfo;
	IpHeader iph(buffer);

	//hostinfo=gethostbyaddr((char *)&iph.hSource_address,sizeof(iph.hSource_address),AF_INET);
	
	cout<<"IP Header:"<<endl;
	cout<<"Packet from : "<<iph.ipaSource_address<<" ("
		<<(hostinfo!=NULL ? hostinfo->h_name : "*")<<") "<<flush;
	
	//hostinfo=gethostbyaddr((char *)&iph.hDestination_address,izeof(iph.hDestination_address),AF_INET);
	
	cout<<"To : "<<iph.ipaDestination_address<<
		" ("<<(hostinfo!=NULL ? hostinfo->h_name : "*")<<")"<<endl;

	cout<<"Version :"<<(int)iph.ipVersion<<endl;

	cout<<"Internet header length : "<<(int)iph.ipLength<<" Struct Size : "<<IP_HEADER_SIZE<<endl;

	cout<<"Type of Service : P: "<<(int)iph.ipType_of_service.ipht_precedence
		<<" D: "<<(int)iph.ipType_of_service.ipht_delay
		<<" T: "<<(int)iph.ipType_of_service.ipht_throughput
		<<" R: "<<(int)iph.ipType_of_service.ipht_relibility
		<<" Res: "<<(int)iph.ipType_of_service.ipht_reserved<<endl;
	
	cout<<"Total length : "<<iph.ipTotal_length<<endl;
	cout<<"Idendification : "<<hex2string(iph.ipIdentification,4)<<endl;
	cout<<"Flags : R: "<<(int)iph.ipFlags.iphf_reserved
		<<" DF: "<<(int)iph.ipFlags.iphf_df
		<<" MF: "<<(int)iph.ipFlags.iphf_mf<<endl;
	
	cout<<"Fragment offset : "<<hex2string(iph.ipFragment_offset,4)<<endl;

	cout<<"Time to Life : "<<(int)iph.ipTime_to_life<<endl;

	protinfo=getprotobynumber(iph.ipProtocol);
	cout<<"Protocol : "<<(protinfo!=NULL ? protinfo->p_name : "")<<endl;

	cout<<"Header checksum : "<<hex2string(iph.ipChecksum,4)<<endl;
	
	cout<<"Options : "<<iph.options<<endl;
	cout<<endl;
	if (!strcmp(protinfo->p_name,"tcp"))
		display_tcpheader(buffer+iph.ipLength);
	if (!strcmp(protinfo->p_name,"udp"))
		display_udpheader(buffer+iph.ipLength);
	dump_data(buffer,IP_HEADER_SIZE);
	getch();
}

void main(int argn,char **argv)
{
	WORD wVersionRequested=MAKEWORD(2,2);
	WSADATA wsaData;
	hostent *hostinfo;
	char name[80];
	
	sockaddr_in listener_addr;
	
	unsigned int bytesnum;

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

	listener=socket(AF_INET,SOCK_RAW,IPPROTO_IP);
	if (WSAGetLastError()==INVALID_SOCKET)
	{
		cerr<<"Creating socket filed"<<endl;
		exit(1);
	}

	gethostname(name,sizeof(name));
	hostinfo=gethostbyname(name);

	/*binding*/

	listener_addr.sin_family=AF_INET;
	listener_addr.sin_port=0;
	listener_addr.sin_addr.S_un.S_addr=((in_addr *)hostinfo->h_addr_list[0])->S_un.S_addr;
	memset(listener_addr.sin_zero,'\x0',8);
	if (bind(listener,(sockaddr *)&listener_addr,sizeof(sockaddr))==-1)
	{
		cerr<<"Binding filed!"<<endl;
		exit(1);
	}

	if (ioctlsocket(listener,SIO_RCVALL,&flag)==-1)
	{
		cerr<<"Socket controling filed (code: "<<WSAGetLastError()<<")"<<endl;
		exit(1);
	}
	while (!kbhit())
	{
		if ((bytesnum=recv(listener,buffer,sizeof(buffer),0))==-1)
		{
			cerr<<"Resiving Filed"<<endl;
			exit(1);
		}
		if (bytesnum>=IP_HEADER_SIZE)
		{
			//memcpy((char *)&iph,buffer,sizeof(IPHeader));
			display_ipheader(buffer);
		}
	}

	WSACleanup();
}
