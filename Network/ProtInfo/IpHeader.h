#ifndef IPHEADER_H
#define IPHEADER_H
#include "Globals.h"
#include <winsock2.h>

#define IP_HEADER_SIZE 20

/***Options Coping****/
#define IP_OPTION_COPY 0x80
#define IP_OPTION_DONTCOPY 0x00

/***Options Classes***/
#define IP_OPTION_CONTROL 0x00
#define IP_OPTION_RESERVED1 0x20
#define IP_OPTION_DEBUG 0x40
#define IP_OPRION_RESERVED2 0x60

/****Options Types*****/
#define IP_OPTION_END 0x00 //end of list
#define IP_OPTION_NOP 0x01 //no operation
#define IP_OPTION_SECURITY 0x02 //security,length=11
#define IP_OPTION_LSRR 0x03 //Loose Source and Record Route
#define IP_OPTION_SSRR 0x09 //Strict Source and Record Route
#define IP_OPTION_RECORDROUTE 0x07 //Record Route,tracing the route
#define IP_OPTION_STREAMID 0x08 //Stream ID,carry the stream identifier.length=4
#define IP_OPTION_TIMESTAMP 0x44 //Time stamp

/*Security option definitions*/
#define IP_OPTION_SECURITY_LENGTH 0x0B
#define IP_OPTION_STREAMID_LENGTH 0x04
/*Secuity field*/
#define IP_OPTION_SECURITY_UNCLASSIFIED 0x0000
#define IP_OPTION_SECURITY_CONFEDENTIAL 0xF135
#define IP_OPTION_SECURITY_EFTO 0x789A
#define IP_OPTION_SECURITY_MMMM 0xBC4D
#define IP_OPTION_SECURITY_PROG 0x5E26
#define IP_OPTION_SECURITY_RESTRICTED 0xAF13
#define IP_OPTION_SECURITY_SECRET 0xD788
#define IP_OPTION_SECURITY_TOPSECTET 0x6BC5
#define IP_OPTION_SECURITY_RESERVED1 0x35E2
#define IP_OPTION_SECURITY_RESERVED2 0x9AF1
#define IP_OPTION_SECURITY_RESERVED3 0x4D78
#define IP_OPTION_SECURITY_RESERVED4 0x24BD
#define IP_OPTION_SECURITY_RESERVED5 0x135E
#define IP_OPTION_SECURITY_RESERVED6 0x89AF
#define IP_OPTION_SECURITY_RESERVED7 0xC4D6
#define IP_OPTION_SECURITY_RESERVED8 0xE26B

/*Timestamp flags*/
#define IP_OPTION_TIMESTAMP_STAMPONLY 0x00
#define IP_OPTION_TIMESTAMP_STAMPEACH 0x01
#define IP_OPTION_TIMESTAMP_STAMPPRES 0x03

#define IP_TOS_PRECEDENCE 0x07
#define IP_TOS_CONTROL 0x06
#define IP_TOS_CRITIC 0x05
#define IP_TOS_FLASHOVERRIDE 0x04
#define IP_TOS_FLASH 0x03
#define IP_TOS_IMMEDIATE 0x02
#define IP_TOS_PRIORITY 0x01
#define IP_TOS_ROUTINE 0x00
#define IP_TOS_ICMP 0x00

#define IP_FLAGS_RESERVED 0x00
#define IP_FLAGS_DF 0x04
#define IP_FLAGS_MF 0x02

typedef struct _IPHeader
{
	u_char iph_ver_ihl; /*Version(4 bits) and IHL(4 bits)*/
	u_char iph_service; /*Type of Service*/
	u_short_un iph_totallen; /*Total Length*/
	u_short_un iph_ident; /*Identification*/
	u_short_un iph_flags_offset; /*Flags(3 bits) and Fragment offset(13 bits)*/
	u_char iph_ttl; /*Time to Life*/
	u_char iph_protocol; /*Protocol*/
	u_short_un iph_checksum; /*Header Check Sum*/
	u_long_un iph_sourceaddr; /*Source Address*/
	u_long_un iph_destaddr; /*Destination Address*/
} IPHeader;

typedef struct _IPHtos
{
	u_char ipht_precedence;/*Priority(2 bits)*/
	u_char ipht_delay;/*0 = Normal Delay,1 = Low Delay(1 bit)*/
	u_char ipht_throughput;/*0 = Normal Throughput,1 = High Throughput(1 bit)*/
	u_char ipht_relibility;/*0 = Normal Relibility,1 = High Relibility(1 bit)*/
	u_char ipht_reserved;/*Reserved(2 bits)*/
} IPHtos;

typedef struct _IPHflags
{
	u_char iphf_reserved;/*Reserved, must be zero(1 bit)*/
	u_char iphf_df;/*0 = May Fragment,1 = Don't Fragment(1 bit)*/
	u_char iphf_mf;/*0 = Last Fragment,1 = More Fragments*/
} IPHflags;

class IpHeader
{
public:
	IpHeader(void);
	//IpHeader(const char *);
	//~IpHeader(void);
	void ReadHeader(const char *data);
	u_char GetIHL(void) const;
	u_char GetTTL(void) const;
	char *GetASource(void) const;
	char *GetADestination(void) const;
private:
	u_char ipVersion;
	u_char ipIHL;
	IPHtos ipTOS;
	u_short ipTotalLength;
	u_short ipIdentification;
	IPHflags ipFlags;
	u_short ipFragmentOffset;
	u_char ipTTL;
	u_char ipProtocol;
	u_short ipCheckSum;
	in_addr ipSourceAddress;
	in_addr ipDestinationAddress;
	char *ipASourceAddress;
	char *ipADestinationAddress;
	bool options;
	char *options_data;
	char *ipHeaderData;
};

#endif IPHEADER_H