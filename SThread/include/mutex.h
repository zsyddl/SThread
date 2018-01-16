#pragma once

#ifndef Mutex_H
#define Mutex_H
#ifdef WIN32
#ifdef STHREAD_EXPORTS
#define STHREAD_API __declspec(dllexport)
#else
#define STHREAD_API __declspec(dllimport)
#endif
#else
#define STHREAD_API
#endif

namespace SThread{
class CMutexData;
class STHREAD_API CMutex
{
public:
	CMutex(void);
	virtual ~CMutex(void);
	bool Lock(long lTimeOut=0);
	
	bool Unlock();
protected:
	CMutexData *m_pMutexData;
};

}

#endif
