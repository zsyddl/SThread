// SThread.cpp : ���� DLL Ӧ�ó������ڵ㡣
//
 
#include "stdafx.h"
#include "dllMain.h"
bool APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
    return TRUE;
}

// ���ǵ���������һ��ʾ��
STHREAD_API int nSThread=0;

// ���ǵ���������һ��ʾ����
STHREAD_API int fnSThread(void)
{
	return 42;
}

// �����ѵ�����Ĺ��캯����
// �й��ඨ�����Ϣ������� SThread.h
CSThreadLib::CSThreadLib()
{ 
	return; 
}
