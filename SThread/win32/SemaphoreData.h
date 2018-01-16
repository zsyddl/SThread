#pragma once

#ifndef SEMAPHOREDATA_H
#define SEMAPHOREDATA_H

#ifdef WIN32
	typedef void * HANDLE;
#else
	typedef sem_t HANDLE;
#endif

namespace SThread
{
	class CSemaphoreData
	{
		friend class CSemaphore;
		public:
			CSemaphoreData();
			virtual ~CSemaphoreData();
	
		protected:
			HANDLE m_hSemaphore;
	};
}

#endif