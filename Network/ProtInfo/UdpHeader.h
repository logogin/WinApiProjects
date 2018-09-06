#ifndef UDPHEADER_H
#define UDPHEADER_H

#define UDP_HEADER_SIZE 8

typedef struct _UDPHeader
{
	u_char udph_sourceport[2];/*Source Port*/
	u_char udph_destport[2];/*Destination Port*/
	u_char udph_len[2];/*Tatal Length including header*/
	u_char udph_checksum[2];/*Check Sum*/
} UDPHeader;

class UdpHeader
{
public:
	UdpHeader(const char *);
	~UdpHeader(void);
	void ReadHeader(const char *);
	u_short udpSource_port;
	u_short udpDestination_port;
	u_short udpLength;
	u_short udpChecksum;
	bool datagram;
private:
	char *datagram_data;
};

#endif UDPHEADER_H