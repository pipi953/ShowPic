//�궨���ļ�---���幫�õĺ�
#ifndef _GLOBAL_DEFINE_H_
#define _GLOBAL_DEFINE_H_

#include "afxmt.h"

#include <DTTask/DTUtil.h>

#define MAXCAPSINFOCOUNT    200

//�������е�ͳ����Ϣ
typedef struct tagStatisticElement
{
	UINT dwSumCount;         //��õ��ź�����
	UINT dwUsedTimeSum;      //��õĺ�ʱ����

	UINT dwMinTime;          //������Сʱ��
	UINT dwMaxTime;

	UINT nMinLimitTime;      //ͳ�Ƶ���Сʱ������ʱ�����
	UINT nMaxLimitTime;
	UINT nMinLimitCount;
	UINT nMaxLimitCount;

	UINT dwStart;
	UINT dwTime;

	HANDLE m_hMutex;

	char m_szMsg[512];

	void Init()
	{
		dwSumCount = 0; dwUsedTimeSum = 0;
		dwMinTime = 100000;
		dwMaxTime = 0;  dwStart = 0;

		nMinLimitTime = 30; nMaxLimitCount = 100;
		nMinLimitCount = nMaxLimitCount = 0;

		memset(m_szMsg, '\0', 512);
	}

	void Start()
	{
		dwStart = GetTickCount();
	}

	void Stop()
	{
		esutil::LockMutex lock(m_hMutex, INFINITE);

		//cs.Lock();

		dwTime = GetTickCount() - dwStart;

		dwSumCount++;
		dwUsedTimeSum += dwTime;

		if(dwTime < nMinLimitTime)
			nMinLimitCount++;

		if(dwTime > nMaxLimitTime)
			nMaxLimitCount++;

		if(dwTime > dwMaxTime)
			dwMaxTime = dwTime;

		if(dwTime < dwMinTime)
			dwMinTime = dwTime;

		//cs.Unlock();		
	}
}StatisticElement;

//typedef enum RunTimeEnum {seAnalyse1, seAnalyse2,seAnalyse3,seAnalyse4,seAnalyse5, seDisplay, seIOControl};

#define  RUNCHANNEL    256
//���м�������ͳ����Ϣʵʱ��ʾ
typedef struct tagRunTimeElement
{
	//ͳ�Ƹ�������ķ���ʱ��
	StatisticElement analyElement[60][RUNCHANNEL];
	
	int dwAnalyGood[60][RUNCHANNEL];       //����������Ŀ
	int dwAnalyseNG[60][RUNCHANNEL];       //������Ʒ��Ŀ
	int dwExceptionCount;              //�쳣ģʽ�������쳣����

	void Init()
	{
		for(int hIndex = 0; hIndex < 60; hIndex++)
		{
			for (int wIndex = 0; wIndex < RUNCHANNEL; wIndex++)
			{
				analyElement[hIndex][wIndex].Init();
			}			
		}

		for(int hIndex = 0; hIndex < 60; hIndex++)
		{
			for (int wIndex = 0; wIndex < RUNCHANNEL; wIndex++)
			{
				dwAnalyGood[hIndex][wIndex] = dwAnalyseNG[hIndex][wIndex] = 0;
			}
		}

	    dwExceptionCount = 0;
	}
}RunTimeElement;

#endif  //_GLOBAL_DEFINE_H_