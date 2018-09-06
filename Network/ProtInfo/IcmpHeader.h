#ifndef ICMPHEADER_H
#define ICMPHEADER_H

#include "Globals.h"
#include "IpHeader.h"

#define ICMP_HEADER_SIZE 4

#define ICMP_TYPE_NOTYPE 0xFF
#define ICMP_CODE_NOCODE 0xFF

#define ICMP_TYPE_UNREACHABLE 0x03
#define ICMP_CODE_UNREACHABLE_NET 0x00
#define ICMP_CODE_UNREACHABLE_HOST 0x01
#define ICMP_CODE_UNREACHABLE_PROTOCOL 0x02
#define ICMP_CODE_UNREACHABLE_PORT 0x03
#define ICMP_CODE_UNREACHABLE_FRAGMENTATION 0x04
#define ICMP_CODE_UNREACHABLE_ROUTE 0x05

#define ICMP_TYPE_EXCEEDED 0x0B
#define ICMP_CODE_EXCEEDED_TTL 0x00
#define ICMP_CODE_EXCEEDED_REASSEMBLY 0x01

#define ICMP_TYPE_PARAMPROBLEM 0x0C
#define ICMP_CODE_PARAMPROBLEM_POINTER 0x00

#define ICMP_TYPE_QUENCH 0x04
#define ICMP_CODE_QUENCH 0x00

#define ICMP_TYPE_REDIRECT 0x05
#define ICMP_CODE_REDIRECT_NETWORK 0x00
#define ICMP_CODE_REDIRECT_HOST 0x01
#define ICMP_CODE_REDIRECT_TOSANDHETWORK 0x02
#define ICMP_CODE_REDIRECT_TOSANDHOST 0x03

#define ICMP_HEADER_SIZE_ECHO 8
#define ICMP_TYPE_ECHOREQUEST 0x08
#define ICMP_TYPE_ECHOREPLY 0x00
#define ICMP_CODE_ECHO 0x00

#define ICMP_TYPE_TIMESTAMP 0x0D
#define ICMP_TYPE_TIMESTAMPREPLAY 0x0E
#define ICMP_CODE_TIMESTAMP 0x00

#define ICMP_TYPE_INFORMATIONREQUEST 0x0F
#define ICMP_TYPE_INFORMATIONREPLAY 0x10
#define ICMP_CODE_INFORMATION 0x00

typedef struct _ICMPHeader
{
	u_char icmph_type;
	u_char icmph_code;
	u_short_un icmph_checksum;
} ICMPHeader;

typedef struct _ICMPHecho
{
	u_short_un icmphe_idnum;
	u_short_un icmphe_seqnum;
} ICMPHecho;

class IcmpHeader:public IpHeader
{
public:
	IcmpHeader(void);
	void CreateEchoRequest(const u_short id_num,const u_short seq_num,
		const char *echo_data,const u_short echo_data_size);
	void ReadHeader(const char *data,const u_short data_size);
	u_short SetCRC(void);
	u_char GetType(void) const;
	u_char GetCode(void) const;
	u_short GetID(void) const;
	u_short GetSeq(void) const;
	char *GetDataPtr(void) const;
	char *GetIcmpDataPtr(void) const;
	u_short GetTotalLength(void) const;
private:
	//bool icmpInitialised;
	void ReadEcho(void);
	char *icmpIcmpData;
	u_short icmpIcmpDataSize;
	u_char icmpDataOffset;
	u_short icmpSeqNumber;
	u_short icmpIDNumber;
	u_char icmpType;
	u_char icmpCode;
	u_short icmpCheckSum;
};

#endif ICMPHEADER_H