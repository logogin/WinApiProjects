/*************************************************************
Файл Buffer.cpp
Copyright (c) 1999 Мешков А., Тихомиров Ю.
*************************************************************/

// Buffer.cpp : implementation file
//

#include "stdafx.h"
#include "Terminal.h"
#include "Buffer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBuffer

CBuffer::CBuffer(int nLength, int nExtra)
{
	m_Length = nLength;
	m_Extra = nExtra;
	m_Head = m_Tail = 0;

	m_pBuffer = new CHAR[m_Length];
}

CBuffer::~CBuffer()
{
	delete m_pBuffer;
}

BOOL CBuffer::ReadChar(CHAR& cChar)
{
	CSingleLock Lock(&m_Lock, TRUE);

	if (m_Tail == m_Head)
    return FALSE;

	cChar = m_pBuffer[m_Tail++];
	m_Tail %= m_Length;

  return TRUE;
}

void CBuffer::WriteChar(CHAR cChar)
{
	CSingleLock Lock(&m_Lock, TRUE);

  m_pBuffer[m_Head++] = cChar;
  m_Head %= m_Length;

  if (m_Head == m_Tail)
  {
    CHAR *pBuffer = new CHAR[m_Length+m_Extra];

    memcpy(pBuffer, m_pBuffer, sizeof(CHAR) * m_Head);
		memcpy(pBuffer+m_Tail+m_Extra, m_pBuffer+m_Tail, 
			sizeof(CHAR) * (m_Length-m_Tail));

		m_Length += m_Extra;
		m_Tail += m_Extra;

    delete m_pBuffer;
		m_pBuffer = pBuffer;
  }

	m_NotEmpty.SetEvent();
}
