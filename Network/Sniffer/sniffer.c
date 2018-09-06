//------------------------------------------------
// Sniffer.c
// NT sniffer
// Copyright (C) 2000  Brett Cooper
// see license.txt for information
//
// by: Brett Cooper BrettJCooper@hotmail.com
// date: April 29 2000
// Built with: MS VC++ 6.0
// 
//
//-----------------------------------------------

//------------------------------------------------------------------------
//
//  Include Files
//
//------------------------------------------------------------------------

#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <stdlib.h>
#include <conio.h>
#include "sniffer.h"



//------------------------------------------------------------------------
//
//  Definitions
//
//------------------------------------------------------------------------

#define ETH_ALEN       6
// the alignment bits for the header


#define MAGIC_NUM     14
// the size of the eth header is 14


#define WIN32_LEAN_AND_MEAN 
// tell compiler to run in lean mode

//------------------------------------------------------------------------
//
//  Prototypes
//
//------------------------------------------------------------------------
int Receiver();  // procedure that reads packets off of card
char *HostIp(unsigned long int in); // resolves the IP of and host



//------------------------------------------------------------------------
//
//  Structures
//
//------------------------------------------------------------------------


// these three typedefs make structures look cleaner
typedef unsigned char __u8;
typedef unsigned short __u16;
typedef unsigned int __u32;


// This is the structure of an ethernet header 
// which is the first 14 bits of a packet
typedef struct _ETH_HEADER
{
    __u8   h_dest[ETH_ALEN];
    __u8   h_source[ETH_ALEN];
    __u16  h_proto;
}               ETH_HEADER;

// This is a structure of an IP Header which is the 
// section of the packet see "Unix Network Progaming" pg884 
// for a detailed description
typedef struct _IP_HEADER
{
	__u8	        ihl:4;     //header length
	__u8            version:4; //IP version 4 or 6
    __u8            tos;       //type of service (see stevens fig 7.12)
    __u16           tot_len;   //total lenght including Payload
    __u16           id;        //identification, used for reassembly
    __u16           frag_off;  //whether to fragment and the offset
    __u8            ttl;       //time to live decremented at routers  
    __u8            protocol;  // protocol 6=tcp 17=udp
    __u16           check;     // 16 bit header checksum
    __u32           saddr;     // IvP4 source address
    __u32           daddr;     // IvP4 dest address
}               IP_HEADER;

// This is the TCP header section which is encapsulated in the
// IP data section it is usually 20 bytes long
typedef struct _TCP_HEADER
{
    __u16           source;  // source port
    __u16           dest;    // destination port
    __u32           seq;     // sequence number
    __u32           ack_seq; // acknowledge sequence number
	__u32	        res1:4,  // can't figure this one out
		            doff:4,  // data offset
		            fin:1,   // request to close connection
		            syn:1,   // synchronization sequence numbers
		            rst:1,   // Reset Connection
		            psh:1,   // transmit without filling buffer
		            ack:1,   // acknowledge field was valid
		            urg:1,   // urgent/highpriority data
		            res2:2;  
    __u16           window;  // for Window Flow Control
    __u16           check;   // CheckSum
    __u16           urg_ptr; // valid when urg flag is set
}               TCP_HEADER;


//This is the UDP structure it will take the place
//of the TCP Structure in a UDP packet
typedef struct _UDP_HEADER
{
    __u16           source;  // Soure Port
    __u16           dest;    // Destination Port
    __u16           len;     // Length of datagram
    __u16           check;   // checksum
}                UDP_HEADER;


// this is the ethernet packet which is the combination of
// the three headers: ethernet,IP, and TCP(or UDP)
typedef struct _ETHER_PACKET
{
    ETH_HEADER      ETH;
    IP_HEADER       IP;
    TCP_HEADER      TCP;
}               ETHER_PACKET;




//------------------------------------------------------------------------
//
//  Global variables
//
//------------------------------------------------------------------------

// this is the kind of packets we will pull from the 
// ethernet card
ULONG       Filters[6] = {0, NDIS_PACKET_TYPE_DIRECTED,
                          NDIS_PACKET_TYPE_MULTICAST,
                          NDIS_PACKET_TYPE_BROADCAST,
                          NDIS_PACKET_TYPE_ALL_MULTICAST,
                          NDIS_PACKET_TYPE_PROMISCUOUS};

TCHAR       szbuff[40];   // string buffer
LPADAPTER   lpAdapter;    // pointer to the ethernet card
LPPACKET    lpPacket;     // pointer to ethernet packet
ULONG       Filter = 0;   
static int  iResolveAddr = 0; //whether to resove addresses, not implemented
static int  HexOut= 0;        //whether to print out hex dump

//------------------------------------------------------------------------
//
//  packet -- basic NT packet driver test
//
//  TESTS:  PacketGetAdapterNames, PacketopenAdapter, PacketSetFilter, 
//          PacketGetAddress, PacketAllocatePacket, PacketInitPacket,
//          PacketReceive, PacketFreePacket, PacketCloseAdapter
//
//------------------------------------------------------------------------

main(int nargs, char **args)
{
    TCHAR   buf[256];
    TCHAR   *Name;
    ULONG   NameLength = 256;
    UCHAR   Address[6];
    UINT    i;
    DWORD   tid;
    HANDLE  hThread;

	// check to see what adapter to use
    if (nargs < 2) {
        printf("Usage: test [Adapter 0..3]  (-h) \n");
        printf("Defaulting to Adapter 0 \n");
        args[1]="0";
    }

	// check to see if they want a hex dump
	if (nargs==3){
		if (strcmp(args[2],"-h")==0)
			HexOut=1;
	}

	// did they type in to many variables?
    if (atoi(args[1]) > 3) {
        printf("Usage: test [Adapter 0..3]\n");
        return 0;
    }
            

    printf("\nNT Sniffer\n Copyright 2000 Brett Cooper,\n see licence.txt for details\n\n");


    Name = buf; //Point name at the buffer
        
    // get the adapters
    PacketGetAdapterNames(Name, &NameLength);

	// check to see if they chose a valid adapter
    switch (atoi(args[1])) {
        case 3: Name = &Name[strlen(Name)+1];
                if (!strlen(Name))
                    break;
        case 2: Name = (char *) &Name[strlen(Name)+1];
                if (!strlen(Name))
                    break;
        case 1: Name = (char *) &Name[strlen(Name)+1];
                if (!strlen(Name))
                    break;
        case 0: break;
    }
    
	// print the adapter name
    if (strlen(Name) != 0) {
        printf("Adapter Name: %s\n", Name);
        }
    else {
        printf("Adapter %s not present\n", args[1]);
        return 0;
    }
    
    
	// open the adapter to read packets from 
    lpAdapter = PacketOpenAdapter(Name);

	// set the filters from above to the adapter
    Filter = Filters[5];
    PacketSetFilter(lpAdapter, Filter);

	// get the adapters MAC address
    PacketGetAddress(lpAdapter, Address);

    // print the adapters address
    printf("Adapter Addr: [");

    for (i=0; i<5; i++)
        printf("%02x:", Address[i]);
    printf("%02x]\n\n", Address[i]);    

	// create a thread to read form the ethernet card
    hThread = CreateThread(0, 
                           0,
                           (LPTHREAD_START_ROUTINE) Receiver,
                           0,
                           0,
                           &tid);
                            
    printf("Hit RETURN to terminate...\n\n");
    getchar(); // wait until a key is pressed

    // stop sniffing packets
    TerminateThread(hThread, 0);

	// Close the adapter
    PacketCloseAdapter(lpAdapter);

    return 0;    // exit the program
}


//------------------------------------------------------------------------
//
// HostIp get the hosts IP
//
//------------------------------------------------------------------------

char    *HostIp(unsigned long int in)
{

    static char     szHostName[512] = "";
    struct in_addr  iaddr;

    memset(&iaddr,0,sizeof(iaddr));
    iaddr.s_addr = in;

    strcpy(szHostName, inet_ntoa(iaddr));

    return (szHostName);

}






//------------------------------------------------------------------------
//
//  receiver -- a packet sniffer in promiscuous mode that
//  prints out packet information and data
//
//------------------------------------------------------------------------

int Receiver()
{
    int    i;
    UCHAR  buf[1514]; // buffer to write packets to 
    ULONG  Length;    // lenght of current packet
    int    count = 0; // running count of packets
    ETHER_PACKET  *pEthPkt = (ETHER_PACKET *) buf; //packet definition
    IP_HEADER     *ip;  // ip header
    TCP_HEADER    *tcp; // tcp header
    UDP_HEADER    *udp; // udp header
	ETH_HEADER    *eth;
	int data_len;       // length of data segment of packet
    char *data_start;   // where the data segment starts

	// keep sniffing packets forever
    while (TRUE) {


		// these 3 lines use functionality of the packet32 driver
		// to read a packet form the ethernet card into the buffer
        lpPacket = PacketAllocatePacket();
        PacketInitPacket(lpPacket, buf, 1514);
        PacketReceivePacket(lpAdapter, lpPacket, TRUE, &Length);


		// point the structures at the buffer
		eth     = (ETH_HEADER *) buf;
        ip      = (IP_HEADER  *)(buf + MAGIC_NUM);
        tcp     = (TCP_HEADER *) (buf +(4*ip->ihl)+MAGIC_NUM);;
        udp     = (UDP_HEADER *) tcp; // decide later if UDP
	

        // print the packet number
        printf("Packet [%d]\n", count++);
       
		// print hex dump of packet if hex mode was requested
		if (HexOut)
		{
			for (i=0; i<(int)Length; i++) {
				 printf("%02x ", buf[i]);
				 if (!((i+1) % 16))
                     printf("\n");
			}
		}



        // print the Ethernet header Information
		printf("\nEthernet: Dest");
	    for (i=0; i<6; i++) printf(":%02x", buf[i]);
    	printf(" Source");
     	for (i=6; i<12; i++) printf(":%02x", buf[i]);
    	printf(" protocol: %02x%02x ",buf[12],buf[13] );

	

        // print the Ip header information
        printf("\n\nIP: version=%d ihl=%d tos=%d tot_len=%d id=%d "
               "frag_off=%d ttl=%d\nprotocol=%d check=%d saddr=%lx "
               "daddr=%lx\n",
               ip->version,                         /* 4 bits */ 
               ip->ihl,                             /* 4 bits */
               ip->tos,                             /* 8 bits */ 		
               ntohs(ip->tot_len), 
               ntohs(ip->id),
                                                       /* 3 bits (flags) */
               ntohs(ip->frag_off & 0x1fff),    /* 6 bits */
               ip->ttl,                                   /* 8 bits */
			   ip->protocol,                              /* 8 bits */
               ntohs(ip->check), 
               ntohl(ip->saddr), 
               ntohl(ip->daddr));
        if((ip->frag_off & 0x4000) || (ip->frag_off & 0x2000))
        {
			// print the flags
			// I got the maskes from the linux ip.h file
            printf("Flags: ");
            if(ip->frag_off & 0x4000) printf("DF ");
            if(ip->frag_off & 0x2000) printf("MF ");
            printf("\n");
        }

        if(ip->ihl > 5)      // If there are any IP options
        {
            printf("IP options: ");
            for(i = 5; i < ip->ihl; i++)
            {
                 printf("%lx ", ntohl(((long*)ip)[i]));
            }
            printf("\n");
        }

		// if this is a TCP packet print TCP information
        if(ip->protocol == 6)             
        {
            data_len = ntohs(ip->tot_len) - 4 * (ip->ihl + tcp->doff);
            data_start = (char *)ip + 4 * (ip->ihl + tcp->doff);

            printf("\nTCP: source=%d dest=%d seq=%lx "
                   "ack_seq=%lx doff=%d\n[flags] window=%d check=%d "
                   "urg_ptr=%d\n", 
                   ntohs(tcp->source), 
                   ntohs(tcp->dest), 
                   ntohl(tcp->seq), 
                   ntohl(tcp->ack_seq), 
                   tcp->doff,                        /* 6 bits */
                   ntohs(tcp->window), 
                   ntohs(tcp->check),
                   ntohs(tcp->urg_ptr));
                   printf("Flags: ");
                   if(tcp->urg) printf("URG ");
                   if(tcp->ack) printf("ACK ");
                   if(tcp->psh) printf("PSH ");
                   if(tcp->rst) printf("RST ");
                   if(tcp->syn) printf("SYN ");
                   if(tcp->fin) printf("FIN ");
                    printf("\n");

               if(tcp->doff > 5)   // if > 5 then TCP options are present
               {
                  printf("TCP options: ");
                  for(i = 5; i < (int)tcp->doff; i++)
                  {
                     printf("%lx ", ntohl(((long*)tcp)[i]));
                  }
                  printf("\n");
			   }

			   // print to/froms
               printf("s_host:%s s_port:%d\n",
                     HostIp(ip->saddr),
                     ntohs(tcp->source));
               printf("d_host:%s d_port:%d\n",
                     HostIp(ip->daddr),
                     ntohs(tcp->dest));

			   // print the data from the packet, usefull for 
			   // grabing passwords, annoying for binary packets
               printf("Data <%d bytes>: ", data_len); 
               fwrite(data_start, 1, data_len, stdout);
               printf("\n");
            }

		    // if this is an UDP packet print UDP Information
            else if(ip->protocol == 17)                             {
               // udp packet is 64 bits
               data_len = ntohs(ip->tot_len) - 4 * (ip->ihl + 2);
               data_start = (char *)ip + 4 * (ip->ihl + 2);

			   // print to/froms
               printf("UDP: source=%d dest=%d len=%d check=%d\n",
                     ntohs(udp->source), ntohs(udp->dest),
                     ntohs(udp->len), ntohs(udp->check));
               printf("s_host:%s s_port:%d\n",
                     HostIp(ip->saddr),
                     ntohs(udp->source));

			   
               printf("d_host:%s d_port:%d\n",
                     HostIp(ip->daddr),
                     ntohs(udp->dest));
              
               printf("\n");
            }		
    
    	printf("\n\n\n"); 
    
		
		//release the packet 
		PacketFreePacket(lpPacket);
    }
}
