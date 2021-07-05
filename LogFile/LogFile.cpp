
#include "LogFile/LogFile.h"//../include/

#define  MAX_FILEPATH_LEN	520

CLogFile::CLogFile()
{
	InitializeCriticalSection(&cs);
	bFirst = TRUE;
	//m_pfunLog = NULL;
}

CLogFile::~CLogFile()
{
	if(m_File)
		fclose(m_File);

	DeleteCriticalSection(&cs);
}

void CLogFile::TraceMessage(const char *fmt, ...)
{
	char logMsg[MAX_PATH*5] = {0};
	int argc;
	va_list args;
	va_start(args, fmt);
	argc = vsprintf(logMsg, fmt, args);
	va_end(args);

	OutputDebugString(logMsg);
}

BOOL CLogFile::LogFormat(const char* szPath, int logLevel, const char *fmt, ...)
{
	char logMsg[MAX_MSG_SIZE] = {0};
	char logFmt[1024] = {0};
	char logLev[32] = {0};

	switch (logLevel)
	{
	case LOG_DEBUG:     sprintf_s(logLev, "DEBUG");       break;
	case LOG_INFO:      sprintf_s(logLev, "INFO");        break;
	case LOG_WARN:      sprintf_s(logLev, "WARNING");     break;
	case LOG_ERROR:     sprintf_s(logLev, "ERROR");       break;
	case LOG_CRIT:      sprintf_s(logLev, "CRITICAL");    break;
	case LOG_FATAL:     sprintf_s(logLev, "FATAL");       break;
	case LOG_NULL:		break;
	default:    return false;
	}
	if(logLevel == LOG_NULL)
	{
		sprintf_s(logFmt,"%s",fmt);
	}
	else
	{
		sprintf_s(logFmt, "[%s] : %s", logLev, fmt);
	}
	int argc;
	va_list args;
	va_start(args, fmt);
	argc = vsprintf(logMsg, logFmt, args);
	va_end(args);

	//OutputDebugString(szMessage);

	return LogMessage(szPath, logMsg);
}

BOOL CLogFile::LogMessage(const char* szPath, const char *szMsg, const char *szMsg1)
{
	char szSubDir[MAX_PATH] = {0};

	if (!strlen(szMsg))
	{
		return FALSE;
	}

	EnterCriticalSection(&cs);

	try
	{
		if (bFirst) 
		{
			if(szPath != NULL)
				sprintf_s(szLogFilePath, "%s", szPath);
			else
			{
				GetModuleFileName(NULL, szLogFilePath, MAX_PATH);
				int len=strlen(szLogFilePath);

				while (len > 0)
				{
					len--;

					if (szLogFilePath[len] == '\\')
					{
						break;
					}
				}

				if (len > 0)
				{
					szLogFilePath[len] = 0;
				}
				else
				{
					GetCurrentDirectory(MAX_PATH, szLogFilePath);
				}

				if (szLogFilePath[0] != '\\')
				{
					strcat_s(szLogFilePath, "\\");
				}

				strcat_s(szLogFilePath, "log\\");

				//sprintf_s(szSubDir, "%ld\\", g_nIndex);
				strcat_s(szLogFilePath, szSubDir);
			}

			CreateMultiDir(szLogFilePath);
			bFirst = FALSE;
		}


		nowTime = time(NULL);

		tmTemp = *localtime(&nowTime);
		tmTemp.tm_mday -= 30;			//30days
		yesTime = mktime(&tmTemp);

		tmNow = *localtime(&nowTime);
		tmYes = *localtime(&yesTime);

		strftime(szNowTime, MAX_PATH, "%Y%m%d", &tmNow);
		strftime(szYesTime, MAX_PATH, "%Y%m%d", &tmYes);

		sprintf(szLogFile,    "%s%s.log", szLogFilePath, szNowTime);
		sprintf(szDelLogFile, "%s%s.log", szLogFilePath, szYesTime);

		strftime(szDT, MAX_PATH,"%Y-%m-%d %H:%M:%S", &tmNow);

		//删除30天以前的旧日志文件
		DeleteFile(szDelLogFile);

		if (szMsg1 != NULL)
		{
			sprintf(szMessage, "%s[%d]  %s: %s\r\n", szDT, GetCurrentThreadId(), szMsg, szMsg1);
		}
		else
		{
			sprintf(szMessage, "%s[%d]  %s\r\n", szDT, GetCurrentThreadId(), szMsg);
		}

		/*if(m_pfunLog != NULL)
		{
			m_pfunLog(szMessage);
		}*/

		if (m_File == NULL)
		{
			m_File = fopen(szLogFile, "a");
		}

		if (m_File != NULL)				
		{
			fwrite(szMessage, sizeof(char), strlen(szMessage), m_File);
			fclose(m_File);

			m_File = NULL;
		}
	}
	catch (...)
	{
	}

	LeaveCriticalSection(&cs);

	return TRUE;
}

int CLogFile::CreateMultiDir(char* szPath)
{
	char szFilePath[MAX_FILEPATH_LEN];
	int k = 0;

	char szBuf[MAX_FILEPATH_LEN];
	strcpy_s(szBuf, szPath);
	int i = strlen(szBuf);
	for(int j = 0; j<i; j++)
	{
		if(szBuf[j] == '\\' || szBuf[j] == '/')
		{
			// 解出一级目录
			k = j;
			strncpy(szFilePath, szBuf, k);
			szFilePath[k] = '\0';

			if((_access(szFilePath, 0)) == -1)
			{
				// 创建目录
				if(mkdir(szFilePath) == -1)
					return -1;
			}
		}
	}

	if (k == 0) // 非法目录 
	{
		return -1;
	}

	return 0;
}
