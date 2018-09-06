#include <iostream.h>
#include <winsock2.h>
#include <conio.h>
#include <stdlib.h>

#define SIO_RCVALL	0x98000001
#define BUFFERSIZE 0xFFFF

typedef struct IPHeader
{
	unsigned char iph_ver_ihl; /*Version(4) and IHL(4)*/
	unsigned char iph_service; /*Type of Service*/
	unsigned short iph_totallen; /*Total Length*/
	unsigned short iph_ident; /*Identification*/
	unsigned short iph_flags_offset; /*Flags(3) and Fragment offset(13)*/
	unsigned char iph_tol; /*Time to Life*/
	unsigned char iph_protocol; /*Protocol*/
	unsigned short iph_checksum; /*Header Check Sum*/
	unsigned long iph_sourceaddr; /*Source Address*/
	unsigned long iph_destaddr; /*Destination Address*/
	//unsigned char iph_options_padding[8]; /*Options and Padding*/
} IPHeader;

typedef struct TCPHeader
{
	unsigned short tcph_sourceport; /*Source Port*/
	unsigned short tcph_destport; /*Destination Port*/
	unsigned long tcph_seqnum; /*Sequence Number*/
	unsigned long tcph_acknum; /*Acknowledgment Number*/
	unsigned short tcph_offset_reserv_cbits; /*Data offset(4), Reserved(6) and Control Bits(6)*/
	unsigned short tcph_window; /*Window*/
	unsigned short tcph_checksum; /*Check Sum*/
	unsigned short tcph_urgentptr; /*Urgent Pointer*/
} TCPHeader;

SOCKET listener;
unsigned long flag=1;

char buffer[BUFFERSIZE];

void display_tcpheader(TCPHeader &tcph,unsigned int offset)
{
	cout<<"TCP Header :"<<endl;
	cout<<"Source port : "<<ntohs(tcph.tcph_sourceport)
		<<" Destination port : "<<ntohs(tcph.tcph_destport)<<endl;
	cout<<"Sequence number : "<<tcph.tcph_seqnum
		<<" Acknowledgment number : "<<tcph.tcph_seqnum<<endl;
	cout<<"Data offset : "<<((HIBYTE(ntohs(tcph.tcph_offset_reserv_cbits)))>>4)*4
		<<" Struct size : "<<sizeof(TCPHeader)<<endl;
	cout<<"Reserved : "<<((ntohs(tcph.tcph_offset_reserv_cbits)>>6)&0x003F)<<endl;
	cout<<"URG : "<<((ntohs(tcph.tcph_offset_reserv_cbits)>>5)&0x0001)
		<<"  ACK : "<<((ntohs(tcph.tcph_offset_reserv_cbits)>>4)&0x0001)
		<<"  PSH : "<<((ntohs(tcph.tcph_offset_reserv_cbits)>>3)&0x0001)
		<<"  RST : "<<((ntohs(tcph.tcph_offset_reserv_cbits)>>2)&0x0001)
		<<"  SYN : "<<((ntohs(tcph.tcph_offset_reserv_cbits)>>1)&0x0001)
		<<"  FIN : "<<(ntohs(tcph.tcph_offset_reserv_cbits)&0x0001)<<endl;
	cout<<"Window : "<<tcph.tcph_window<<endl;
	cout<<"Checksum : "<<tcph.tcph_checksum<<endl;
	cout<<"Urgent Pointer : "<<tcph.tcph_urgentptr<<endl;
	for (int i=0; i<((HIBYTE(ntohs(tcph.tcph_offset_reserv_cbits)))>>4)*4-sizeof(TCPHeader); i++)
		cout<<(int)buffer[offset+sizeof(TCPHeader)+i]<<flush;
	getch();
}

void display_ipheader(IPHeader &iph)
{
	in_addr addr;
	hostent *hostinfo;
	protoent *protinfo;
	addr.S_un.S_addr=iph.iph_sourceaddr;
	flag=0;
	if (ioctlsocket(listener,SIO_RCVALL,&flag)==-1)
	{
		cerr<<"Socket controling filed"<<endl;
		exit(1);
	}
	hostinfo=gethostbyaddr((char *)&iph.iph_sourceaddr,sizeof(iph.iph_sourceaddr),AF_INET);
	flag=1;
	if (ioctlsocket(listener,SIO_RCVALL,&flag)==-1)
	{
		cerr<<"Socket controling filed"<<endl;
		exit(1);
	}
	cout<<"IP Header:"<<endl;
	cout<<"Packet from : "<<inet_ntoa(addr)<<" ("
		<<(hostinfo!=NULL ? hostinfo->h_name : "*")<<") "<<flush;
	addr.S_un.S_addr=iph.iph_destaddr;
	hostinfo=gethostbyaddr((char *)&iph.iph_destaddr,sizeof(iph.iph_sourceaddr),AF_INET);
	flag=1;
	if (ioctlsocket(listener,SIO_RCVALL,&flag)==-1)
	{
		cerr<<"Socket controling filed"<<endl;
		exit(1);
	}
	cout<<"To : "<<inet_ntoa(addr)<<" ("<<(hostinfo!=NULL ? hostinfo->h_name : "*")<<")"<<endl;
	cout<<"Version :"<<(iph.iph_ver_ihl>>4)<<endl;
	cout<<"Internet header length : "<<(((iph.iph_ver_ihl<<4)&0xFF)>>4)*4
		<<" Struct Size : "<<sizeof(IPHeader)<<endl;
	
	cout<<"Type of Service : ";
	for (int i=7; i>=0; i--)
		cout<<(iph.iph_service&(1<<i) ? '1' : '0');
	cout<<endl;
	cout<<"Total length : "<<ntohs(iph.iph_totallen)<<endl;
	cout<<"Idendification : "<<ntohs(iph.iph_ident)<<endl;
	cout<<"Flags : ";
	for (i=2; i>=0; i--)
		cout<<((ntohs(iph.iph_flags_offset)>>13)&1<<i ? '1' : '0');
	cout<<endl;
	cout<<"Fragment offset : "<<(((ntohs(iph.iph_flags_offset)<<3)&0xD)>>3)<<endl;
	cout<<"Time to Life : "<<(int)iph.iph_tol<<endl;
	protinfo=getprotobynumber(iph.iph_protocol);
	cout<<"Protocol : "<<(protinfo!=NULL ? protinfo->p_name : "")<<endl;
	cout<<"Header checksum : "<<iph.iph_checksum<<endl;
	//getch();
	if(iph.iph_protocol==IPPROTO_TCP)
	{
		TCPHeader tcph;
		if (ntohs(iph.iph_totallen>=(((iph.iph_ver_ihl<<4)&0xFF)>>4)*4+sizeof(TCPHeader)))
			memcpy((char *)&tcph,buffer+(((iph.iph_ver_ihl<<4)&0xFF)>>4)*4,sizeof(TCPHeader));
		display_tcpheader(tcph,(((iph.iph_ver_ihl<<4)&0xFF)>>4)*4);
	}
};

void main(int argn,char **argv)
{
	WORD wVersionRequested=MAKEWORD(2,2);
	WSADATA wsaData;
	
	sockaddr_in listener_addr;
	IPHeader iph;
	hostent *hostinfo;

	unsigned int bytesnum;
	char name[128];

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
		cerr<<"Socket controling filed"<<endl;
		exit(1);
	}
	while (!kbhit())
	{
		if ((bytesnum=recv(listener,buffer,sizeof(buffer),0))==-1)
		{
			cerr<<"Resiving Filed"<<endl;
			exit(1);
		}
		if (bytesnum>=sizeof(IPHeader))
		{
			memcpy((char *)&iph,buffer,sizeof(IPHeader));
			display_ipheader(iph);
		}
	}

	WSACleanup();
}
