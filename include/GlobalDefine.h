//宏定义文件---定义公用的宏
#ifndef _GLOBAL_DEFINE_H_
#define _GLOBAL_DEFINE_H_

#include "afxmt.h"

#include <DTTask/DTUtil.h>

#define MAXCAPSINFOCOUNT    200

//定义所有的统计信息
typedef struct tagStatisticElement
{
	UINT dwSumCount;         //获得的信号总数
	UINT dwUsedTimeSum;      //获得的耗时总数

	UINT dwMinTime;          //单次最小时间
	UINT dwMaxTime;

	UINT nMinLimitTime;      //统计的最小时间和最大时间界限
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
//所有检测软件的统计信息实时显示
typedef struct tagRunTimeElement
{
	//统计各个相机的分析时间
	StatisticElement analyElement[60][RUNCHANNEL];
	
	int dwAnalyGood[60][RUNCHANNEL];       //分析正常数目
	int dwAnalyseNG[60][RUNCHANNEL];       //分析次品数目
	int dwExceptionCount;              //异常模式发生的异常个数

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