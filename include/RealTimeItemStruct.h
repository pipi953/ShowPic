//�궨���ļ�---���幫�õĺ�
#ifndef _REALTIMEITEM_STRUCR_H_
#define _REALTIMEITEM_STRUCR_H_

#include "public.h"

#define MAXTHREADNUM  60        //��󿪱ٵ��̸߳���

#define MAXMSGLENGTH  1024*10   //���������Ϣ����

#define NOMARKID       1000     //���ڸò��ּ�¼ID��
#define MINERRORRECT   160      //��С��󱨾���

#define MAXERRORNUM    400

#define RODNUMHORI   0         //���ˮƽ����
#define RODNUMVERT   1         //��Դ�ֱ����

#define ONECHANNEL   1
#define TWOCHANNEL   2

//����ʶ�����
#define RECONGNOIZENUM 10

#define METHOD_ADAPTIMAGE 0
#define METHOD_MATCHIMAGE 1

//��������������㷽���ĺ궨��
#define SLC          0
#define SFT          1

//������չ����
#define EXPENDSIZE 20
#define ERROREXPENDSIZE 10

//���ϵȼ�����
#define BIGERROR 1
#define OTHERERROR 2
#define KEYERROR 3

typedef struct tagCCVMParaIn
{
	int    currChannelID;
	int    histChannelID;
	int    ImageIndex;

	void Init()
	{
		histChannelID = currChannelID = ImageIndex = 0;
	}
}CCVMParaIn;

typedef struct tagCCVMParaOut
{
	CvRect  ocrParaRect;
	int     ocrResult; //���ڱ�ʾ�˺�ʶ���Ƿ�ɹ�
	char    ocrArray[20];//���ڼ�¼ʶ��ĸ˺�
	cvRectObj ocrRectObj;

	int    channelID;
	char   ocrImagePath[1024];

	int      errorMsgNum;
	RectMsg  errorMsg[MAXERRORNUM]; //ר�����ڼ�¼������Ϣ

	//���ڼ�¼ͼ�����
	int ImageIndex;

	void Init()
	{
		memset(&ocrParaRect, 0, sizeof(CvRect));

		ocrResult = 0;  channelID = 0;

		ImageIndex = 0;

		errorMsgNum = 0;
		memset(errorMsg, 0, MAXERRORNUM*sizeof(RectMsg));

		memset(ocrArray, '\0', 20 * sizeof(char));
		memset(&ocrRectObj, 0, sizeof(unsigned char));

		memset(ocrImagePath, '\0', 1024 * sizeof(char));
	}
}CCVMParaOut;


typedef struct tagTrainParaIn
{
	int startIndex;                 //��ʾ��ǰ�г�����ʼͼ�����
	int endIndex;                   //��ʾ��ǰ�г�����ֹͼ�����

	int  trainBI;                    //��ǰ�г����
	char trainBH[32];

	char currTrainID;               //��ʾ��ǰ�г����

	char trainCX[32];
	char trainCH[32];
	char trainDW[32];
	char trainLW[32];
	char trainZW[32];
	int trainTDH;

	void Init()
	{
		trainBI = 0;
		memset(trainBH, '\0', 32 * sizeof(char));
		currTrainID = 0; startIndex = endIndex = 0;

		memset(trainCX, '\0', 32 * sizeof(char));
		memset(trainCH, '\0', 32 * sizeof(char));
		memset(trainDW, '\0', 32 * sizeof(char));
		memset(trainLW, '\0', 32 * sizeof(char));
		memset(trainZW, '\0', 32 * sizeof(char));
		trainTDH = 0;
	}
}TrainParaIn;

typedef struct tagTrainParaOut
{
	//���ڼ�¼��ǰͼ���ŵĸ߶ȺͿ��
	int imageMark;     //���ڱ�ʾ��ǰ�����Ƿ�ʶ�����
	float brightness;	//����
	float contrast;	//�Աȶ�
	char resolution[1024];	//�ֱ���

	int totalNum;
	int alarmImage;

	void Init()
	{
		imageMark = 0;
		brightness = 0.0;
		contrast = 0.0;
		totalNum = 0; alarmImage = 0;
	}
}TrainParaOut;

typedef struct tagTrainAlarmParaOut
{
	int alarmNum;	//��������
	int imageIndex;
	CvRect alarmRect[5];	//��������
	int alarmSize[5];

	void Init()
	{
		alarmNum = 0; imageIndex = 0;
		memset(alarmSize, 0, 5 * sizeof(int));
		memset(alarmRect, 0, 5 * sizeof(CvRect));
	}
}AlarmParaOut;

typedef struct tagAnalyDataTask   //��Ӧ�ķ�������Ԫ
{
	int   currAnalyTask;

	char  currImagePath[1024];
	char  histImagePath[1024];

	char  debugImagePath[1024];
	char  histdebugImagePath[1024];

	char  trainBH[64];       //��¼��ǰ�г����
	char  siteInterval[128];     //վ������

	CCVMParaIn   ParaIn;
	CCVMParaOut  ParaOut;      //���ն������

	TrainParaIn    m_analyParaIn;          //��¼��ǰ��׼��Ϣ	
	TrainParaOut   m_analyParaOut;
	AlarmParaOut   m_anlarmParaOut[100];
	int  m_analyImageIndex;
	char m_AnalyImagePath[1024];

	void Init()
	{

		memset(trainBH, '\0', 64 * sizeof(char));
		memset(siteInterval, '\0', 128 * sizeof(char));

		memset(currImagePath, '\0', 1024 * sizeof(char));
		memset(histImagePath, '\0', 1024 * sizeof(char));

		m_analyParaIn.Init();	m_analyParaOut.Init();
		memset(m_anlarmParaOut, '\0', 100 * sizeof(AlarmParaOut));
		m_analyImageIndex = 0;
		memset(m_AnalyImagePath, '\0', 1024 * sizeof(char));

		ParaIn.Init();  ParaOut.Init();
	}
}AnalyDataTask;

#define ArrayString std::vector<CString>

typedef struct tagGlobalPara
{
	int    ParaAll_FTNum;
	int    ParaAll_ImageHeight;
	int    ParaAll_ImageWidth;       //�����׼ͼ����и�ȷ�

	int    ParaAll_GanHaoChannel;    //�������ָ˺ŵ�ͨ����˫ͨ��

	int    ParaAll_SavePara;
	int	   ParaAll_IsClipping;
	int    ParaAll_SaveOcrImage;
	int    ParaAll_MatchMark;        //�����Ƿ񱣴���׼�м���
	int    ParaAll_SaveErrorPara;

	int    ParaAll_MatchHeight;
	int    ParaAll_MatchWidth;
	int    ParaAll_MatchErrorValue;


	//�Թ��ϱ���������������
	int    ParaAll_ErrorNum;

	//�������˲�����
	float  ParaAll_WidthHeightRotio;
	float  ParaAll_AreaPercent;

	//�ؼ������˲�����
	float  ParaAll_KeyAreaPercent;

	float  ParaMatch_UpThreshold;
	int    ParaMatch_IsSaveSimilar;
	int    ParaMathc_IsNeedGrayValue;
	int    ParaAll_MergeSize;

	float  ParaMatch_MatchAngle;
	float  ParaMatch_MatchPointPercent;

	//̤����Ʋ���
	int    ParaTM_NormMaxArea;
	int    ParaTM_NormMinArea;
	int    ParaTM_NormFilter;
	int    ParaTM_NormHeight;
	int    ParaTM_NormWiedth;
	int	   ParaTM_NormRatio;
	float  ParaTM_Score;
	float  ParaTM_CircleScore;

	void Init()
	{
		ParaMathc_IsNeedGrayValue = 1;
		ParaAll_SaveErrorPara = 1;
		ParaAll_ImageHeight = 250;
		ParaAll_ImageWidth = 250;

		//�Թ��ϱ���������������
		ParaAll_ErrorNum = 3;

		ParaAll_MatchHeight = 6;
		ParaAll_MatchWidth = 6;

		ParaAll_MatchErrorValue = 20;

		//���ʶ������
		ParaTM_Score = 0;

		ParaMatch_MatchAngle = 5.0;
		ParaMatch_MatchPointPercent = 0.3;

		//�˲������ʼ��
		ParaMatch_UpThreshold = 0.98;
		ParaMatch_IsSaveSimilar = 0;
		ParaAll_WidthHeightRotio = 3;
		ParaAll_AreaPercent = 0.001;
		ParaAll_KeyAreaPercent = 0.4;
	}
}GlobalPara;

#endif//_REALTIMEITEM_STRUCR_H_