#ifndef TCPHEADER_H
#define TCPHEADER_H

#define TCP_HEADER_SIZE 20

#define TCP_OPTION_END 0x00
#define TCP_OPTION_NOP 0x01
#define TCP_OPTION_MAXSEG 0x02

#define TCP_OPTION_MAXSEG_LEN 0x04

typedef struct _TCPHeader
{
	u_char tcph_sourceport[2]; /*Source Port*/
	u_char tcph_destport[2]; /*Destination Port*/
	u_char tcph_seqnum[4]; /*Sequence Number*/
	u_char tcph_acknum[4]; /*Acknowledgment Number*/
	u_char tcph_offset_reserv_cbits[2]; /*Data offset(4), Reserved(6) and Control Bits(6)*/
	u_char tcph_window[2]; /*Window*/
	u_char tcph_checksum[2]; /*Check Sum*/
	u_char tcph_urgentptr[2]; /*Urgent Pointer*/
} TCPHeader;

typedef struct _TCPHcbits
{
	u_char tcphc_urg;/*Urgent Pointer field significant*/
	u_char tcphc_ack;/*Acknowledgment field significant*/
	u_char tcphc_psh;/*Push Function*/
	u_char tcphc_rst;/*Reset the connection*/
	u_char tcphc_syn;/*Synchronize sequence numbers*/
	u_char tcphc_fin;/*No more data from sender*/
} TCPHcbits;

class TcpHeader
{
public:
	TcpHeader(const char *);
	~TcpHeader(void);
	void ReadHeader(const char *);
	u_short tcpSource_port;
	u_short tcpDestination_port;
	u_long tcpSeq_num;
	u_long tcpAck_num;
	u_char tcpData_offset;
	u_char tcpReserved;
	TCPHcbits tcpControl_bits;
	u_short tcpWindow;
	u_short tcpChecksum;
	u_short tcpUrgent_pointer;
	bool options;
private:
	char *options_data;
};

#endif TCPHEADER_H