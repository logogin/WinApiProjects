/*************************************************************
Файл Modem.h
Copyright (c) 1999 Мешков А., Тихомиров Ю.
*************************************************************/

// Modem.h : header file
//

#include "Buffer.h"

/////////////////////////////////////////////////////////////////////////////
// CModem class

class CModem : public CObject
{
// Construction
public:
	CModem();

	BOOL Initialize(LPCTSTR lpCommPort);
	void UnInitialize();

// Attributes
public:
	CBuffer m_OutBuffer;
	CBuffer m_InBuffer;

	HANDLE m_hComm;

// Operations
public:

// Implementation
public:
	virtual ~CModem();
};

/////////////////////////////////////////////////////////////////////////////
