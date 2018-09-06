/*************************************************************
Файл Buffer.h
Copyright (c) 1999 Мешков А., Тихомиров Ю.
*************************************************************/

// Buffer.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBuffer class

class CBuffer : public CObject
{
// Construction
public:
	CBuffer(int nLength = 100, int m_Extra = 10);

// Attributes
private:
	CHAR *m_pBuffer;
	int m_Length, m_Extra;
  int m_Head, m_Tail;
	CCriticalSection m_Lock;

public:
	CEvent m_NotEmpty;
	
// Operations
public:
	void WriteChar(CHAR cChar);
	BOOL ReadChar(CHAR& cChar);

// Implementation
public:
	virtual ~CBuffer();
};

/////////////////////////////////////////////////////////////////////////////
