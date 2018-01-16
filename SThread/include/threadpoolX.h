#pragma once

#ifndef ThreadPoolX_H
#define ThreadPoolX_H
#ifdef OS_LINUX
#define STHREAD_API
#endif

#ifdef WIN32
#ifdef STHREAD_EXPORTS
#define STHREAD_API __declspec(dllexport)
#include "Windows.h"
#else
#define STHREAD_API __declspec(dllimport)
#endif
#endif

#include <deque>
#include <list>
using namespace std;

#include "Thread.h"
#include "mutex.h"
#include "Event.h"
#include "Semaphore.h"
#include <iostream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
using namespace SThread;
using namespace std;

namespace SThread{

class CTasksQueue;

typedef struct _sThreadInfo
{
	void *pObj;
	unsigned long nThreadId;
	CTasksQueue *pTasksQueue;
}sThreadInfo;

typedef enum _eThreadPoolXError
{
	eThreadPoolXError_Success = 0,
	eThreadPoolXError_Failed = -1,
	eThreadPoolXError_TimeOut = -2,
}eThreadPoolXError;

typedef int (__stdcall *ProcessFunction)(void *jobPara);

class STHREAD_API CRunnableX
{
	public:
		CRunnableX(ProcessFunction pfTaskFunc = NULL, void *pData = NULL);

		~CRunnableX();
		
		/*继承的类实现，默认调用回调函数*/
		virtual void Run();

		void Close();

		int Wait(int nMiliseconds);

		void Set();

		time_t m_nAddTaskTime;
		time_t m_nProcessTaskTime;

	protected:
		CEvent *m_pEvent;	
		ProcessFunction m_pfProcessFunction;
		void *m_pData;
};

class CTasksQueue
{
	public:
		CTasksQueue();
		~CTasksQueue();
		
		int PushBack(CRunnableX *pTask);
		int PushFront(CRunnableX *pTask);
		int Size();

		CRunnableX *PopBack();
		CRunnableX *PopFront();

	private:
		SThread::CMutex *m_pMutexDeque;
		std::deque<CRunnableX *> m_TasksDeque;
};

class STHREAD_API CThreadPoolX
{
	public:
		/*default thread num is 8*/
		CThreadPoolX(); 
		~CThreadPoolX(void);

		int Open(int nThreadCount, unsigned long nThreadIndexStart = 0);
		void Close();
		
		/*start or stop thread pool*/
		void Start();
		void Stop();
		
		int AddTask(CRunnableX *pTask, unsigned long nDispatchId);

	private:

#ifdef WIN32
		static int __stdcall ThreadProcessFunc(void* pArgs);
#else
        static void *ThreadProcessFunc(void* pArgs);
#endif

        /*线程数量为0，继续关闭*/
		CMutex *m_pMutexThreadCount;
		long m_nThreadCount;

		/*protect job queue, as a result of this queue is visited by multiple thread*/
		CMutex *m_pDequeMutex;

		CEvent *m_pRunStateEvent;
		CMutex *m_pRunStateMutex;
		bool m_bRunStateFlag;

		/*thread stored list*/
		std::list<sThreadInfo *> m_ThreadsInfoList;
		std::list<CThread *> m_ThreadsList;

		CMutex *m_pExitMutex;
		bool m_bThreadPoolExitFlag;

		CSemaphore *m_pAddTaskSemaphore;
		CEvent *m_pThreadPoolExitCompleteEvent;
};
}

#endif
