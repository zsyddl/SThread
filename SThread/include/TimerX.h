#pragma once

#ifdef WIN32
#include <process.h>
#include <Windows.h>
#include <time.h>
#include <list>
#include "SThread.h"
#include "Thread.h"
#include "Mutex.h"

using namespace std;
#elif

#endif

namespace SThread{
#ifdef WIN32
	typedef void (*pfSingleShotTimerOut)(void *pPara);
#elif

#endif

class STHREAD_API CTimerX
{
	public:
		CTimerX();
		~CTimerX();

		int Init();
		void UnInit();
		int Interval();
		void SetInterval(int nMsec);
		bool IsActive();
		bool IsSingleShot();
		void SetSingleShot(bool bSingleShot);
		void SetTimeoutFunc(pfSingleShotTimerOut pfFunc, void *pPara);

		void Start(int nMsec);
		void Start();
		void Stop();
	
	private:
		static void __stdcall SingleShot(int nMsec, CTimerX *pTimerX, pfSingleShotTimerOut pfFunc, void *pPara);
		static int __stdcall ThreadProc(void *pData);

		int m_nInterval;
		bool m_bIsActive;
		bool m_bIsSingleShot;
		int m_nTimerId;
		long m_nLastTime;

		CMutex *m_pMutex;

		static CMutex *m_pListMutex;
		static list<CTimerX *> m_listTimer;

		int GetListTimerSize();
		int RemoveFromListTimer(CTimerX *pTimer);
		pfSingleShotTimerOut m_pSingleShotFunc;
		void *m_pPara;

		static CMutex *m_pThreadMutex;
		static bool m_bThreadIsExit;
		static SThread::CThread *m_pThread;
};
}