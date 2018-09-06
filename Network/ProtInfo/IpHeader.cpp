#include "Includes.h"
#include "IpHeader.h"
//#include "Globals.h"

IpHeader::IpHeader(void)
{
	ipVersion=0;
	ipIHL=0;
	ipTotalLength=0;
	ipIdentification=0;
	ipFragmentOffset=0;
	ipTTL=0;
	ipProtocol=0;
	ipCheckSum=0;
	ipASourceAddress=NULL;
	ipADestinationAddress=NULL;
	ipHeaderData=NULL;
}

void IpHeader::ReadHeader(const char *data)
{
	IPHeader temp;
	//u_char tos;
	u_char flags;
	//in_addr address;
	//temp=new char[IPHEADER_SIZE];
	//assert(temp!=NULL);
	memcpy((void *)&temp,data,IP_HEADER_SIZE);
	ipVersion=get_bits(temp.iph_ver_ihl,4,4);
	ipIHL=get_bits(temp.iph_ver_ihl,0,4)*4;
	//tos=temp.iph_service;
	ipTOS.ipht_precedence=get_bits(temp.iph_service,5,3);
	ipTOS.ipht_delay=get_bits(temp.iph_service,4,1);
	ipTOS.ipht_throughput=get_bits(temp.iph_service,3,1);
	ipTOS.ipht_relibility=get_bits(temp.iph_service,2,1);
	ipTOS.ipht_reserved=get_bits(temp.iph_service,0,2);
	ipTotalLength=ntohs(temp.iph_totallen.short_val);
	ipIdentification=ntohs(temp.iph_ident.short_val);
	flags=get_bits(temp.iph_flags_offset.char_val[0],5,3);
	ipFlags.iphf_reserved=get_bits(flags,2,1);
	ipFlags.iphf_df=get_bits(flags,1,1);
	ipFlags.iphf_mf=get_bits(flags,0,1);
	ipFragmentOffset=((temp.iph_flags_offset.char_val[0]&0x1F)<<8)
		+temp.iph_flags_offset.char_val[1];
	ipTTL=temp.iph_ttl;
	ipProtocol=temp.iph_protocol;
	ipCheckSum=ntohs(temp.iph_checksum.short_val);
	memcpy(&ipSourceAddress.S_un.S_un_b,temp.iph_sourceaddr.char_val,4);
	memcpy(&ipDestinationAddress.S_un.S_un_b,temp.iph_destaddr.char_val,4);
	ipASourceAddress=strdup(inet_ntoa(ipSourceAddress));
	assert(ipASourceAddress!=NULL);
	ipADestinationAddress=strdup(inet_ntoa(ipDestinationAddress));
	assert(ipADestinationAddress!=NULL);
	if (ipIHL>IP_HEADER_SIZE)
	{
		options=true;
		options_data=new char[ipIHL-IP_HEADER_SIZE];
		assert(options_data!=NULL);
		memcpy(options_data,data+IP_HEADER_SIZE,sizeof(options_data));
	}
}

u_char IpHeader::GetIHL(void) const
{
	return ipIHL;
}

u_char IpHeader::GetTTL(void) const
{
	return ipTTL;
}

char *IpHeader::GetASource(void) const
{
	return strdup(ipASourceAddress);
}

char *IpHeader::GetADestination(void) const
{
	return strdup(ipADestinationAddress);
}

/*IpHeader::~IpHeader(void)
{
	if (options)
		delete []options_data;
}*/