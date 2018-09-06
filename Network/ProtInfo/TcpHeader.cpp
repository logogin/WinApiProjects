#include "Includes.h"
#include "TcpHeader.h"
#include "Globals.h"

TcpHeader::TcpHeader(const char *data):options(false)
{
	TcpHeader::ReadHeader(data);
}

void TcpHeader::ReadHeader(const char *data)
{
	TCPHeader temp;
	u_char bits;
	//u_short offset_reserv_cbits;
	memcpy((void *)&temp,data,TCP_HEADER_SIZE);
	tcpSource_port=(temp.tcph_sourceport[0]<<8)+temp.tcph_sourceport[1];
	tcpDestination_port=(temp.tcph_destport[0]<<8)+temp.tcph_destport[1];
	tcpSeq_num=(temp.tcph_seqnum[0]<<24)+(temp.tcph_seqnum[1]<<16)+
		(temp.tcph_seqnum[2]<<8)+temp.tcph_seqnum[3];
	tcpAck_num=(temp.tcph_acknum[0]<<24)+(temp.tcph_acknum[1]<<16)+
		(temp.tcph_acknum[2]<<8)+temp.tcph_acknum[3];
	//offset_reserv_cbits=temp.tcph_offset_reserv_cbits);
	tcpData_offset=get_bits(temp.tcph_offset_reserv_cbits[0],4,4)*4;
	tcpReserved=(get_bits(temp.tcph_offset_reserv_cbits[0],0,4)<<2)+
		get_bits(temp.tcph_offset_reserv_cbits[1],6,2);
	bits=get_bits(temp.tcph_offset_reserv_cbits[1],0,6);
	tcpControl_bits.tcphc_urg=get_bits(bits,5,1);
	tcpControl_bits.tcphc_ack=get_bits(bits,4,1);
	tcpControl_bits.tcphc_psh=get_bits(bits,3,1);
	tcpControl_bits.tcphc_rst=get_bits(bits,2,1);
	tcpControl_bits.tcphc_syn=get_bits(bits,1,1);
	tcpControl_bits.tcphc_fin=get_bits(bits,0,1);
	tcpWindow=(temp.tcph_window[0]<<8)+temp.tcph_window[1];
	tcpChecksum=(temp.tcph_checksum[0]<<8)+temp.tcph_checksum[1];
	tcpUrgent_pointer=(temp.tcph_urgentptr[0]<<8)+temp.tcph_urgentptr[1];
	if (tcpData_offset>TCP_HEADER_SIZE)
	{
		options=true;
		options_data=new char[tcpData_offset-TCP_HEADER_SIZE];
		assert(options!=NULL);
		memcpy(options_data,data+TCP_HEADER_SIZE,sizeof(options_data));
	}
}

TcpHeader::~TcpHeader(void)
{
	if (options)
		delete []options_data;
}