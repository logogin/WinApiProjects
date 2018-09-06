#include <iostream.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

#define MAX_PACKET_SIZE    0x10000
#define SIO_RCVALL         0x98000001

char Buffer[MAX_PACKET_SIZE];



typedef struct _IPHeader {
  UCHAR   iph_verlen;   // ������ � ����� ���������
  UCHAR   iph_tos;      // ��� �������
  USHORT  iph_length;   // ����� ����� ������
  USHORT  iph_id;       // �������������
  USHORT  iph_offset;   // ����� � ��������
  UCHAR   iph_ttl;      // ����� ����� ������
  UCHAR   iph_protocol; // ��������
  USHORT  iph_xsum;     // ����������� �����
  ULONG   iph_src;      // IP-����� �����������
  ULONG   iph_dest;     // IP-����� ����������
} _IPHeader;

char src[10];
char dest[10];
char ds[15];
unsigned short lowbyte;
unsigned short hibyte;

void main()
{
  WSADATA     wsadata;   // ������������� WinSock.
  SOCKET      s;         // C�������� �����.
  char        name[128]; // ��� ����� (����������).
  HOSTENT*    phe;       // ���������� � �����.
  SOCKADDR_IN sa;        // ����� �����
  IN_ADDR sa1;        //
  unsigned long        flag = 1;  // ���� PROMISC ���/����.

  // �������������
  WSAStartup(MAKEWORD(2,2), &wsadata);
  s = socket( AF_INET, SOCK_RAW, IPPROTO_IP );
  gethostname(name, sizeof(name));
  phe = gethostbyname( name );
  ZeroMemory( &sa, sizeof(sa) );
  sa.sin_family = AF_INET;
  sa.sin_addr.s_addr = ((struct in_addr *)phe->h_addr_list[0])->s_addr;
  bind(s, (SOCKADDR *)&sa, sizeof(SOCKADDR));
  
  // ��������� promiscuous mode.
  if (ioctlsocket(s,SIO_RCVALL,&flag)==-1)
	{
		cerr<<"Socket controling filed"<<endl;
		exit(1);
	}
  // ����������� ���� ����� IP-�������.
  while( !_kbhit() )
  {
    int count;
    if ((count = recv( s, Buffer, sizeof(Buffer), 0 ))==-1)
	{
		cerr<<"Filed"<<endl;
		exit(1);
	}
	
    // ��������� IP-������
    if( count >= sizeof(IPHeader) )
    {
      IPHeader* hdr = (IPHeader *)Buffer;
      //�������� ������ ������...

	strcpy(src,"Packet: ");
	CharToOem(src,dest);
	printf(dest);
	// ����������� � �������� ��� ����� �����������.
	printf("From ");
	sa1.s_addr = hdr->iph_src;
	printf(inet_ntoa(sa1));

	// ����������� � �������� ��� ����� ����������.
	printf(" To ");
	sa1.s_addr = hdr->iph_dest;
	printf(inet_ntoa(sa1));

	// ��������� ��������. ������ ������ ���� ��������
	// ���������� � ����� winsock2.h
	printf(" Prot: ");
	if(hdr->iph_protocol == IPPROTO_TCP) printf("TCP ");
	if(hdr->iph_protocol == IPPROTO_UDP) printf("UDP ");

	// ��������� ������. ��� ��� � ���� ������ ������ �������
	// ������, � �� ��������, �� �������� �������� ����� �������.
	printf("Size: ");
	lowbyte = hdr->iph_length>>8;
	hibyte = hdr->iph_length<<8;
	hibyte = hibyte + lowbyte;
	char buffer[80];
	printf("%s",itoa(hibyte,buffer,10));

	// ��������� ����� ����� ������.
	printf(" TTL:%s",itoa(hdr->iph_ttl,buffer,10));
	printf("\n");

    }
  }

  closesocket( s );
  WSACleanup();
}