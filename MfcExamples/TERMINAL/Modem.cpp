/*************************************************************
Файл Modem.cpp
Copyright (c) 1999 Мешков А., Тихомиров Ю.
*************************************************************/

// Modem.cpp : implementation file
//

#include "stdafx.h"
#include "Terminal.h"
#include "Modem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModem

CModem::CModem()
{
	m_hComm = INVALID_HANDLE_VALUE;
}

CModem::~CModem()
{
	UnInitialize();
}

BOOL CModem::Initialize(LPCTSTR lpCommPort)
{
	m_hComm = CreateFile(lpCommPort,
		GENERIC_READ | GENERIC_WRITE, 0, NULL, 
		OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);

	if (m_hComm == INVALID_HANDLE_VALUE) 
		return FALSE;

	DCB dcb;

	GetCommState(m_hComm, &dcb);
	BuildCommDCB("baud=19200 parity=N data=8 stop=1", &dcb);
	SetCommState(m_hComm, &dcb);

	SetCommMask(m_hComm, EV_BREAK | EV_RXCHAR);

	return TRUE;
}

void CModem::UnInitialize()
{
	if (m_hComm != INVALID_HANDLE_VALUE)
	{
		EscapeCommFunction(m_hComm, SETBREAK);

		CloseHandle(m_hComm);
		m_hComm = INVALID_HANDLE_VALUE;
	}
}


