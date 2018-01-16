#include "StdAfx.h"
#include "dllMain.h"
#include "Event.h"
#include "EventData.h"

using namespace SThread;
 
CEvent::CEvent()
{
	m_pEventData = new CEventData();
	/*m_pEventData = NULL;*/
}

CEvent::~CEvent()
{
	if (m_pEventData)
	{
		//Set();
		if (m_pEventData->m_hEvent)
		{
			CloseHandle(m_pEventData->m_hEvent);
			m_pEventData->m_hEvent = NULL;
		}
		delete m_pEventData;
		m_pEventData = NULL;
	}
}

int CEvent::Create()
{
	/*��ʼ��Ϊ�˹���ʽ*/
	m_pEventData->m_hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	if (NULL == m_pEventData->m_hEvent)
	{
		return -1;
	}

	return 0;
}

/***************************************************************
 Method     : DestroyImpl
 Description: �ű���������
 Parameter  : 
 Returns    :					
****************************************************************/
void CEvent::Destroy()
{
	if (m_pEventData)
	{
		//Set();
		if (m_pEventData->m_hEvent)
		{
			CloseHandle(m_pEventData->m_hEvent);
			m_pEventData->m_hEvent = NULL;
		}
		delete m_pEventData;
		m_pEventData = NULL;
	}
}

/***************************************************************
 Method     : SetImpl
 Description: �����ű����ź�״̬
 Parameter  : 
 Returns    :					
****************************************************************/
int CEvent::Set()
{
	if (NULL!= m_pEventData->m_hEvent && !SetEvent(m_pEventData->m_hEvent))
	{
		return 0;
	}

	return -1;
}

/***************************************************************
 Method     : ResetImpl
 Description: �����ű�Ϊ���ź�״̬
 Parameter  : 
 Returns    :					
****************************************************************/
void CEvent::Reset()
{
	if (!ResetEvent(m_pEventData->m_hEvent))
	{
		return;
	}
}

/***************************************************************
 Method     : WaitImpl
 Description: ������ֱ���ű�Ϊ���ź�״̬
 Parameter  : 
 Returns    :					
****************************************************************/
bool CEvent::Wait()
{
	switch (WaitForSingleObject(m_pEventData->m_hEvent, INFINITE))
	{
		case WAIT_OBJECT_0:
			return true;

		default:
			return false;
	}

	return false;
}

/***************************************************************
 Method     : WaitImpl
 Description: ����ָ��ʱ��
 Parameter  : 
 Returns    :					
****************************************************************/
bool CEvent::Wait(long lMilliseconds)
{
	bool retVal=false;
	switch (WaitForSingleObject(m_pEventData->m_hEvent, lMilliseconds + 1))
	{
		case WAIT_TIMEOUT:
			retVal = false;
			break;

		case WAIT_OBJECT_0:
			retVal = true;
		    break;
		default:
			retVal = false;
			break;
	}

	return retVal;
}