
/*
* for windows 32
*
*/
#pragma once

namespace SThread{
 
class CThreadData
{
	friend class CThread;
public:
	CThreadData(void);
	virtual ~CThreadData(void);

protected:

	HANDLE			m_hThread;
	DWORD			m_dwThreadID;

};
}