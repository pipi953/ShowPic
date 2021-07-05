//宏定义文件---定义公用的宏
#ifndef _REALTIMEITEM_STRUCR_H_
#define _REALTIMEITEM_STRUCR_H_

#include "public.h"

#define MAXTHREADNUM  60        //最大开辟的线程个数

#define MAXMSGLENGTH  1024*10   //定义最大信息长度

#define NOMARKID       1000     //基于该部分记录ID号
#define MINERRORRECT   160      //最小最大报警数

#define MAXERRORNUM    400

#define RODNUMHORI   0         //针对水平方向
#define RODNUMVERT   1         //针对垂直方向

#define ONECHANNEL   1
#define TWOCHANNEL   2

//定义识别次数
#define RECONGNOIZENUM 10

#define METHOD_ADAPTIMAGE 0
#define METHOD_MATCHIMAGE 1

//针对显著特征计算方法的宏定义
#define SLC          0
#define SFT          1

//定义扩展参数
#define EXPENDSIZE 20
#define ERROREXPENDSIZE 10

//故障等级类型
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
	int     ocrResult; //用于标示杆号识别是否成功
	char    ocrArray[20];//用于记录识别的杆号
	cvRectObj ocrRectObj;

	int    channelID;
	char   ocrImagePath[1024];

	int      errorMsgNum;
	RectMsg  errorMsg[MAXERRORNUM]; //专门用于记录错误信息

	//用于记录图像序号
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
	int startIndex;                 //表示当前列车的起始图像序号
	int endIndex;                   //表示当前列车的终止图像序号

	int  trainBI;                    //当前列车编号
	char trainBH[32];

	char currTrainID;               //表示当前列车序号

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
	//用于记录当前图像单张的高度和宽度
	int imageMark;     //用于标示当前任务是否识别完成
	float brightness;	//亮度
	float contrast;	//对比度
	char resolution[1024];	//分辨率

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
	int alarmNum;	//警报数量
	int imageIndex;
	CvRect alarmRect[5];	//警报区域
	int alarmSize[5];

	void Init()
	{
		alarmNum = 0; imageIndex = 0;
		memset(alarmSize, 0, 5 * sizeof(int));
		memset(alarmRect, 0, 5 * sizeof(CvRect));
	}
}AlarmParaOut;

typedef struct tagAnalyDataTask   //对应的分析任务单元
{
	int   currAnalyTask;

	char  currImagePath[1024];
	char  histImagePath[1024];

	char  debugImagePath[1024];
	char  histdebugImagePath[1024];

	char  trainBH[64];       //记录当前列车编号
	char  siteInterval[128];     //站点区间

	CCVMParaIn   ParaIn;
	CCVMParaOut  ParaOut;      //按照对象操作

	TrainParaIn    m_analyParaIn;          //记录当前标准信息	
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
	int    ParaAll_ImageWidth;       //针对配准图像的切割等分

	int    ParaAll_GanHaoChannel;    //用于区分杆号单通道或双通道

	int    ParaAll_SavePara;
	int	   ParaAll_IsClipping;
	int    ParaAll_SaveOcrImage;
	int    ParaAll_MatchMark;        //配置是否保存配准中间结果
	int    ParaAll_SaveErrorPara;

	int    ParaAll_MatchHeight;
	int    ParaAll_MatchWidth;
	int    ParaAll_MatchErrorValue;


	//对故障报警总数加以限制
	int    ParaAll_ErrorNum;

	//大区域滤波参数
	float  ParaAll_WidthHeightRotio;
	float  ParaAll_AreaPercent;

	//关键部件滤波参数
	float  ParaAll_KeyAreaPercent;

	float  ParaMatch_UpThreshold;
	int    ParaMatch_IsSaveSimilar;
	int    ParaMathc_IsNeedGrayValue;
	int    ParaAll_MergeSize;

	float  ParaMatch_MatchAngle;
	float  ParaMatch_MatchPointPercent;

	//踏面控制参数
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

		//对故障报警总数进行限制
		ParaAll_ErrorNum = 3;

		ParaAll_MatchHeight = 6;
		ParaAll_MatchWidth = 6;

		ParaAll_MatchErrorValue = 20;

		//检测识别区域
		ParaTM_Score = 0;

		ParaMatch_MatchAngle = 5.0;
		ParaMatch_MatchPointPercent = 0.3;

		//滤波面积初始化
		ParaMatch_UpThreshold = 0.98;
		ParaMatch_IsSaveSimilar = 0;
		ParaAll_WidthHeightRotio = 3;
		ParaAll_AreaPercent = 0.001;
		ParaAll_KeyAreaPercent = 0.4;
	}
}GlobalPara;

#endif//_REALTIMEITEM_STRUCR_H_