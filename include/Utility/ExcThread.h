
#include "Public.h"

#pragma once

class CExcThreadPool;


//////////////////////////////////////////////////////////////////////////
// CMutexLock
//////////////////////////////////////////////////////////////////////////
class GM_EXPORT CMutexLock
{
public:
	CMutexLock(void);
	~CMutexLock(void);

public:
	void Lock (void);
	void Unlock (void);

private:
	CRITICAL_SECTION  m_lock;
};


//////////////////////////////////////////////////////////////////////////
// CExcThread
//////////////////////////////////////////////////////////////////////////
class GM_EXPORT CExcThread
{
public:   //���̰߳������������𡢻ָ����ս��Լ�ͨ�Ź���
	CExcThread(void);
	virtual ~CExcThread(void);

public:
	/*!
		\brief ����
	 */
	BOOL	CreateExcThread(int priority = THREAD_PRIORITY_NORMAL, DWORD flags = 0);
	/*!
		\brief ����
	 */
	DWORD	SuspendExcThread(void);
	/*!
		\brief ����
	 */
	DWORD	ResumeExcThread(void);
	/*!
		\brief ��ֹ
	 */
	DWORD	TerminateExcThread(void);

	/*!
		\brief �������ȼ�
	 */
	BOOL	SetPriorityExcThread(int priority);

	/*!
		\brief ����ID��
	 */
	void	SetIDForExcThread(int id);

	/*!
		\brief ��ȡID��
	 */
	DWORD   GetIDForExcThread(void) const;

	virtual DWORD ThreadProcess(void);

protected:
	static DWORD	_thread_process	(CExcThread *_this);
	virtual BOOL	_enter_instance (void);
	virtual DWORD	_leave_instance (void);

protected:
	HANDLE m_hThread;
	DWORD  m_dwThreadId;

	HANDLE m_hEventSetExit;		// �����˳��¼�
	HANDLE m_hEventExited;		// �Ѿ��˳��¼�
	bool   m_isRunning;

	CExcThreadPool  *m_hPool;
};

typedef CExcThread    *HExcThread;
typedef CExcThread   *LPExcThread;


