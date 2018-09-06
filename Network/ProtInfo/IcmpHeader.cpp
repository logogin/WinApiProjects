#include "Includes.h"
#include "IcmpHeader.h"
#include "Memlib.h"
#include <assert.h>

IcmpHeader::IcmpHeader(void)
{
	icmpIcmpData=NULL;
	icmpIcmpDataSize=0;
	icmpDataOffset=0;
	icmpType=ICMP_TYPE_NOTYPE;
	icmpCode=ICMP_CODE_NOCODE;
	icmpCheckSum=0;
}

void IcmpHeader::CreateEchoRequest(const u_short id_num,const u_short seq_num,
								   const char *echo_data,const u_short echo_data_size)
{
	ICMPHeader header;
	ICMPHecho echo;
	icmpType=ICMP_TYPE_ECHOREQUEST;
	icmpCode=ICMP_CODE_ECHO;
	icmpCheckSum=0;
	icmpDataOffset=ICMP_HEADER_SIZE_ECHO;
	icmpIDNumber=id_num;
	icmpSeqNumber=seq_num;
	icmpIcmpDataSize=ICMP_HEADER_SIZE_ECHO+echo_data_size;

	if (icmpIcmpData!=NULL)
		delete []icmpIcmpData;

	icmpIcmpData=new char[ICMP_HEADER_SIZE_ECHO+echo_data_size];
	//icmpIcmpData=pdup(echo_data,echo_data_size);
	assert(icmpIcmpData!=NULL);
	header.icmph_type=icmpType;
	header.icmph_code=icmpCode;
	header.icmph_checksum.short_val=/*htons(*/icmpCheckSum/*)*/;
	//pcopy(&header.icmph_type,&icmpCurrentType,sizeof(u_char));
	//pcopy(&header.icmph_code,&icmpCurrentCode,sizeof(u_char));
	//pcopy(header.icmph_checksum,&icmpCheckSum,sizeof(u_short));
	pcopy(icmpIcmpData,&header,ICMP_HEADER_SIZE);

	echo.icmphe_idnum.short_val=htons(icmpIDNumber);
	echo.icmphe_seqnum.short_val=htons(icmpSeqNumber);
	pcopy(icmpIcmpData+ICMP_HEADER_SIZE,&echo,sizeof(echo));
	pcopy(icmpIcmpData+ICMP_HEADER_SIZE_ECHO,echo_data,echo_data_size);
}

void IcmpHeader::ReadHeader(const char *data,const u_short data_size)
{
	ICMPHeader header;
	if (icmpIcmpData!=NULL)
		delete []icmpIcmpData;

	icmpIcmpData=new char[data_size];
	pcopy(icmpIcmpData,data,data_size);
	icmpIcmpDataSize=data_size;
	pcopy(&header,icmpIcmpData,ICMP_HEADER_SIZE);
	icmpType=header.icmph_type;
	icmpCode=header.icmph_code;
	icmpCheckSum=ntohs(header.icmph_checksum.short_val);
	switch (icmpType)
	{
	case ICMP_TYPE_ECHOREQUEST:
	case ICMP_TYPE_ECHOREPLY:
		ReadEcho();
		break;
	}
}

void IcmpHeader::ReadEcho(void)
{
	ICMPHecho echo;

	pcopy(&echo,icmpIcmpData+ICMP_HEADER_SIZE,sizeof(echo));
	icmpIDNumber=ntohs(echo.icmphe_idnum.short_val);
//	cout<<"Readed ID : "<<icmpIDNumber<<endl;
	icmpSeqNumber=ntohs(echo.icmphe_seqnum.short_val);
//	cout<<"Readed Seq : "<<icmpSeqNumber<<endl;
	icmpDataOffset=ICMP_HEADER_SIZE_ECHO;
}

u_short IcmpHeader::SetCRC(void)
{
	ICMPHeader header;
	u_long_un check_sum;
	u_short_un word;
	check_sum.long_val=0;
//	header.icmph_checksum.short_val=htons(icmpCheckSum);
//	pcopy(icmpIcmpData+sizeof(u_short),header.icmph_checksum.char_val,sizeof(u_short));
	for (int i=0; i<icmpIcmpDataSize; i+=2)
	{
		word.char_val[0]=icmpIcmpData[i];
		word.char_val[1]=icmpIcmpData[i+1];
		check_sum.long_val+=word.short_val;
	}
		
	check_sum.long_val=check_sum.short_val[0]+check_sum.short_val[1];
	check_sum.long_val=check_sum.short_val[0]+check_sum.short_val[1];
	icmpCheckSum=~check_sum.short_val[0];

	header.icmph_checksum.short_val=/*htons(*/icmpCheckSum/*)*/;
	pcopy(icmpIcmpData+sizeof(u_short),header.icmph_checksum.char_val,sizeof(u_short));
	return icmpCheckSum;
}

u_char IcmpHeader::GetType(void) const
{
	return icmpType;
}

u_char IcmpHeader::GetCode(void) const
{
	return icmpCode;
}

u_short IcmpHeader::GetID(void) const
{
	return icmpIDNumber;
}

u_short IcmpHeader::GetSeq(void) const
{
	return icmpSeqNumber;
}

char *IcmpHeader::GetDataPtr(void) const
{
	return icmpIcmpData+icmpDataOffset;
}

char *IcmpHeader::GetIcmpDataPtr(void) const
{
	return icmpIcmpData;
}

u_short IcmpHeader::GetTotalLength(void) const
{
	return icmpIcmpDataSize;
}