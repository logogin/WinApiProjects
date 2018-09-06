#ifndef Protocol_H
#define Protocol_H

class Protocol
{
public:
	//Protocol(void);
	Protocol(const char *name,const u_short id,const char data,const u_short size);
	~Protocol(void);
protected:
	char prName[MAX_PRTOCOL_NAME];
	u_short prID;
	u_short prSize;
	char *prData;
};

#endif Protocol_H