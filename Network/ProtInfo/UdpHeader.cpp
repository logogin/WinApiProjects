#include "Includes.h"
#include "UdpHeader.h"

UdpHeader::UdpHeader(const char *data):datagram(false)
{
	UdpHeader::ReadHeader(data);
}

void UdpHeader::ReadHeader(const char *data)
{
	UDPHeader temp;
	memcpy((void *)&temp,data,UDP_HEADER_SIZE);
	udpSource_port=(temp.udph_sourceport[0]<<8)+temp.udph_sourceport[1];
	udpDestination_port=(temp.udph_destport[0]<<8)+temp.udph_destport[1];
	udpLength=(temp.udph_len[0]<<8)+temp.udph_len[1];
	udpChecksum=(temp.udph_checksum[0]<<8)+temp.udph_checksum[1];
	if (udpLength>UDP_HEADER_SIZE)
	{
		datagram=true;
		datagram_data=new char[udpLength-UDP_HEADER_SIZE];
		assert(datagram_data!=NULL);
		memcpy(datagram_data,data+UDP_HEADER_SIZE,sizeof(datagram_data));
	}
}

UdpHeader::~UdpHeader(void)
{
	if (datagram)
		delete []datagram_data;
}