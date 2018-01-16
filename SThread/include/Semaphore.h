#pragma once

#ifndef SEMAPHOREENCAP_H
#define SEMAPHOREENCAP_H

#ifdef WIN32
#include "Windows.h"
#include <stdio.h>
#include <stdlib.h>
#pragma comment(lib, "Kernel32.lib")

#ifdef STHREAD_EXPORTS
#define STHREAD_API __declspec(dllexport)
#else
#define STHREAD_API __declspec(dllimport)
#endif

#else
#include <semaphore.h>
#include <time.h>
#include <errno.h>

#define STHREAD_API

#endif

namespace SThread
{
	class CSemaphoreData;
	class STHREAD_API CSemaphore
	{
		public:
			CSemaphore();
			virtual ~CSemaphore();

			//lValue:windows�´�ֵ��ʾ�ź�����ʼ�����ֵ��linux�´�ֵ��ʾ�Ƿ��ڽ��̼䣨0������һ�����̵��̼߳乲����0��
			long Init(long lInitCount, long lValue = 10000);
			bool Wait();
			bool TryWait(long lTimeOut);
			long Post();

			long Destory();

		protected:
			CSemaphoreData *m_pSemaphoreData;
	};
}

#endif