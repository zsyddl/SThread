#pragma once

#ifndef EVENT_H
#define EVENT_H
#ifdef OS_LINUX
#define STHREAD_API
#endif

namespace SThread
{
	class CEventData;
	class STHREAD_API CEvent
	{
		public:
			CEvent();
			virtual ~CEvent();

			/*����һ�������¼�����bAutoReset  true   �˹�����false  �Զ�����*/
			int Create();

			/*����ǰ�¼���������Ϊ���ź�״̬���Զ����ã���ȴ����¼�����������߳�ֻ��һ���ɱ�����
				���˹����ã���ȴ����¼�����������̱߳�Ϊ�ɱ�����*/
			int Set();

			/*�Ե�ǰ�¼����������̣߳�������Զ����ֱ���¼���������Ϊ���ź�״̬*/
			bool Wait();

			/*�Ե�ǰ�¼����������̣߳��������ָ��ʱ����֮���߳��Զ��ָ��ɵ���*/
			bool Wait(long lMilliseconds);

			/*����ǰ�¼���������Ϊ���ź�״̬*/
			void Reset();
            void Destroy();
    //        void Close();

		protected:
			CEventData *m_pEventData;
	};
}

#endif
