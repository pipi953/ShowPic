#include <Utility/ExcThread.h>

//////////////////////////////////////////////////////////////////////////
CMutexLock::CMutexLock(void)
{
	::InitializeCriticalSection(&m_lock);
}

CMutexLock::~CMutexLock(void)
{
	::DeleteCriticalSection(&m_lock);
}

//���߳�����
void CMutexLock::Lock (void)
{
	::EnterCriticalSection(&m_lock);
}

//���߳̽���
void CMutexLock::Unlock (void)
{
	::LeaveCriticalSection(&m_lock);
}

//////////////////////////////////////////////////////////////////////////
CExcThread::CExcThread(void)
: m_hThread(NULL)
, m_dwThreadId(0)
, m_isRunning(false)
{
	m_hEventSetExit = CreateEvent(NULL,FALSE,FALSE,NULL);
	m_hEventExited  = CreateEvent(NULL,FALSE,FALSE,NULL);
}

CExcThread::~CExcThread(void)
{
	//Stop();
	if (m_hEventSetExit)
		CloseHandle(m_hEventSetExit);
	if (m_hEventExited)
		CloseHandle(m_hEventExited);
}

BOOL CExcThread::CreateExcThread( int priority, DWORD flags )
{
	//���ڵ�ǰ�߳�ID�Ŵ����µ��߳�
	m_hThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)_thread_process, this, flags, &m_dwThreadId);
	
	if (!m_hThread)
	{
		//���ô����߳�ʧ��---��¼��־
		return FALSE;
	}

	//���õ�ǰ�̵߳����ȼ�
	::SetThreadPriority(m_hThread, priority);

	return TRUE;
}

DWORD CExcThread::SuspendExcThread (void)
{
	//����ǰ�̹߳���
	DWORD ret = ::SuspendThread(m_hThread);
	m_isRunning = false;

	return ret;
}

DWORD CExcThread::ResumeExcThread (void)
{
	//������ǰ�߳�
	DWORD ret = ::ResumeThread(m_hThread);
	return ret;
}

//ֹͣ��ǰ�߳�
DWORD CExcThread::TerminateExcThread (void)
{
	if (m_hThread != NULL && m_hThread != INVALID_HANDLE_VALUE)
	{
		DWORD dwCode = 0;
		GetExitCodeThread(m_hThread, &dwCode);

		//��ʾ��ǰ�̻߳��ǻ�Ծ�߳�
		if (dwCode == STILL_ACTIVE)
		{
			SetEvent(m_hEventSetExit);

			//�ȴ�������ʱ��
			if (WaitForSingleObject(m_hEventExited, 2000) == WAIT_TIMEOUT)
			{
				TerminateThread(m_hThread,-1);
			}
		}

		CloseHandle(m_hThread);
		m_hThread = NULL;
		m_isRunning = false;
	}
	return 0;
}


DWORD CExcThread::ThreadProcess(void)
{
	return 100;
}

//���õ�ǰ�̵߳����ȼ�
BOOL CExcThread::SetPriorityExcThread( int nPriority )
{
	if (!m_hThread)
		return false;

	return ::SetThreadPriority(m_hThread, nPriority);
}

//���õ�ǰ�̵߳�ID��
void CExcThread::SetIDForExcThread (int id)
{
	m_dwThreadId = id;
}

//��õ�ǰ�̵߳�ID��
DWORD CExcThread::GetIDForExcThread   (void) const
{
	return m_dwThreadId;
}

BOOL CExcThread::_enter_instance(void)
{
	return TRUE;
}

DWORD CExcThread::_leave_instance(void)
{
	return 0;
}

DWORD CExcThread::_thread_process( CExcThread *_this )
{
	DWORD dwSleep = 0;
	_this->_enter_instance();
	_this->m_isRunning = true;
	while (1)
	{
		if (WaitForSingleObject(_this->m_hEventSetExit, 0) == WAIT_OBJECT_0)
			break;

		dwSleep = _this->ThreadProcess();
		if(dwSleep)
			Sleep(dwSleep);
	}
	_this->_leave_instance();	
	_this->m_isRunning = false;
	SetEvent(_this->m_hEventExited);
	return 0;
}

