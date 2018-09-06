//------------------------------------------------
// Sniffer.h
//
// by: Brett Cooper BrettJCooper@hotmail.com
// date: April 29 2000
// Built with: MS VC++ 6.0
// 
// Modified from Christopher Chlap's test.h file
//
//-------------------------------------------------

#ifndef __PACKET32
#define __PACKET32
#define EXPORT __declspec(dllexport)

#define        DOSNAMEPREFIX   TEXT("Packet_")

#define        MAX_LINK_NAME_LENGTH   64

#include "packon.h"

typedef struct _PACKET_OID_DATA {

    ULONG           Oid;
    ULONG           Length;
    UCHAR           Data[1];

}   PACKET_OID_DATA, *PPACKET_OID_DATA;

#include "packoff.h"

typedef struct _ADAPTER {

    HANDLE     hFile;

    TCHAR      SymbolicLink[MAX_LINK_NAME_LENGTH];

    } ADAPTER, *LPADAPTER;


typedef struct _PACKET {
    HANDLE       hEvent;
    OVERLAPPED   OverLapped;
    PVOID        Buffer;
    UINT         Length;
    } PACKET, *LPPACKET;


PVOID PacketOpenAdapter(LPTSTR AdapterName);


BOOLEAN PacketSendPacket(LPADAPTER lpAdapter,
                         LPPACKET  lpPacket,
                         BOOLEAN   Sync);


PVOID PacketAllocatePacket(VOID);


VOID PacketInitPacket(LPPACKET lpPacket,    
                      PVOID    Buffer,
                      UINT     Length);


VOID PacketFreePacket(LPPACKET lpPacket);


BOOLEAN PacketResetAdapter(LPADAPTER lpAdapter);


ULONG PacketGetAddress(LPADAPTER lpAdapter,
                       PUCHAR    AddressBuffer);


BOOLEAN PacketWaitPacket(LPADAPTER  lpAdapter,
                         LPPACKET   lpPacket,
                         PULONG     BytesReceived);


BOOLEAN PacketReceivePacket(LPADAPTER lpAdapter,
                            LPPACKET  lpPacket,
                            BOOLEAN   Sync,
                            PULONG    BytesReceived);


VOID PacketCloseAdapter(LPADAPTER lpAdapter);


BOOLEAN PacketSetFilter(LPADAPTER lpAdapter,
                        ULONG     Filter);


ULONG PacketGetAdapterNames(PTSTR   pStr,
                            PULONG  BufferSize);


ULONG PacketRequest(LPADAPTER lpAdapter,
                    BOOLEAN   Set,
                    PPACKET_OID_DATA OidData);

//
// Ndis Packet Filter Bits (OID_GEN_CURRENT_PACKET_FILTER).
//

#define NDIS_PACKET_TYPE_DIRECTED           0x0001
#define NDIS_PACKET_TYPE_MULTICAST          0x0002
#define NDIS_PACKET_TYPE_ALL_MULTICAST      0x0004
#define NDIS_PACKET_TYPE_BROADCAST          0x0008
#define NDIS_PACKET_TYPE_SOURCE_ROUTING     0x0010
#define NDIS_PACKET_TYPE_PROMISCUOUS        0x0020
#define NDIS_PACKET_TYPE_SMT                0x0040
#define NDIS_PACKET_TYPE_ALL_LOCAL          0x0080
#define NDIS_PACKET_TYPE_MAC_FRAME          0x8000
#define NDIS_PACKET_TYPE_FUNCTIONAL         0x4000
#define NDIS_PACKET_TYPE_ALL_FUNCTIONAL     0x2000
#define NDIS_PACKET_TYPE_GROUP              0x1000

#endif
