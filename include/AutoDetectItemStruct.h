//�궨���ļ�---���幫�õĺ�
#ifndef _AUTODETECTITEM_STRUCR_H_
#define _AUTODETECTITEM_STRUCR_H_

#include "Public.h"

#define MAXTHREADNUM  60
#define MAXROBOTID    60
#define MAXCHANNELID  100
#define MAXPANTO      20
#define MAXSTEP       1000

#define MAXMSGLENGTH  1024*10

#define NOMARKID       1000     //���ڸò��ּ�¼ID��
#define MINERRORRECT   160

#define MAXERRORNUM    400

#define SECTIONSIZE   4
//#define OTHERSSIZE    8
#define MAXFILEPATH   1024

#define CHEHAOMOKUAITASK         0
#define FASTSCANTASK             1
#define STRICKSCANTASK           2

#define INITPROCESS   0      //�����ʼ����
#define PROCESSING    20     //�����������
#define COMPLETETASK  25     //�����������

#define MAXRECTNUM    100
#define MAXRCHANNEL   100
#define MAXTRAINNUM   100
#define MAXERRORNUM   400

#define ANALYFASTTASK   0x0001
#define ANALYSTRICKTASK 0x0002

#define ZHAPIANMEASURE    100
#define HENDANGMEASURE    101
#define DHENDANGMEASURE   104
#define DZHAPIANMEASURE   103
#define DSASHAMEASURE     102
#define DPAISHIMEASURE    105
#define DCHETOUMEASURE    106
#define BDZHAPIANMEASURE  107
#define BDDZHAPIANMEASURE 108
#define DZHAPIANMEASURESY 109

#define UPTODOWN    0
#define DOWNTOUP    1
#define LEFTTORIGHT 2
#define RIGHTTOLEFT 3

#define CX_NUM 10000

#define TRAININ     1
#define TRAINOUT    2

#define DEVICEIN     1
#define DEVICEOUT    2
#define RESOLVESIZE  600

#define MATCHNUM 600


typedef struct tagKeyPartPara
{
	//�����Թؼ��������ʶ�����ز���
	vector<string>	ImageIndex;
	vector<string>  KeyPartName;
	vector<int>		KeyTypeID;
	vector<float>	KeyTypeScore;
	vector<int>		PartFlag;
	void Init()
	{
		ImageIndex.clear();
		KeyPartName.clear();
		KeyTypeID.clear();
		KeyTypeScore.clear();
		PartFlag.clear();
	}
}KeyPartPara;

typedef struct tagChannelKeyPartPara
{
	int Channel;
	vector<KeyPartPara> KeyParts;

}ChannelKeyPartPara;

typedef struct tagTrainTypePara
{
	CString TrainType[CX_NUM];
	int  TrainTypeNum;

	void Init()
	{
		TrainTypeNum = 0;
	}
}TrainTypePara;
//���ų���



//�����׼�м����洢
typedef struct tagMatchOut
{
	int      m_heightcenter[MATCHNUM];     //�߶�����
	int      m_matchvalue[MATCHNUM];     //��׼��ֵ
	int      m_matcherror[MATCHNUM];     //��׼�в�
	int      m_matchnum;
	void Init()
	{
		m_matchnum = 0;
		memset(m_heightcenter, 0, MATCHNUM * sizeof(int));
		memset(m_matchvalue, 0, MATCHNUM * sizeof(int));
		memset(m_matcherror, 0, MATCHNUM * sizeof(int));
		
	}
}MatchOut;


//��Է�����������ݹ���
typedef struct tagSendCleanTask
{
	int      m_widthIndex;      //��ȱ��
	int      m_heightIndex;     //�߶ȱ��
	int      m_currwidth;
	int      m_currheight;      //��ǰСͼ���
	int      m_histwidth;
	int      m_histheight;      //��ʷСͼ���
	unsigned char m_histpicdata[RESOLVESIZE*RESOLVESIZE];
	unsigned char m_currpicdata[RESOLVESIZE*RESOLVESIZE];
	

	void Init()
	{
		m_widthIndex = 0;
		m_heightIndex = 0;
		m_currwidth = 0;
		m_currheight = 0;
		m_histwidth = 0;
		m_histheight = 0;
		memset(m_histpicdata, '\0', RESOLVESIZE*RESOLVESIZE * sizeof(unsigned char));
		memset(m_currpicdata, '\0', RESOLVESIZE*RESOLVESIZE * sizeof(unsigned char));
	}
}SendCleanTask;

typedef struct tagStrickParaIn
{
	char currTrainNum[20];
	int  currTrainID;
	int  currChannelID;

	char trainBH[32];     //�г����
	int  trainBI;     //�г���λ

	int updataTask;  //�Ƿ���³���ģ��

	int detectImageID;
	int detectRobotID;

	int detectFilterSize;
	int detectAreaSize;
	int detectRectSize;
	int detectTypeID;

	char detectRobotName[256];

	int    MeasureRectNum;
	float  MeasurePixelMM[10];
	int    MeasureThreshold[10];

	int    MeasureRectID[10];
	int    MeasureRectDirect[10];
	CvRect MeasureRect[10];

	int currRectNum;
	CvRect currRectArray[MAXRECTNUM];

	int currSpinRectNum;
	CvRect currSpinRectArray[10];
	float    Rect1Threshold[10];
	float    Rect2Threshold[10];
	float    Depth1Threshold[10];
	float    Depth2Threshold[10];




	void Init()
	{
		detectImageID = detectRobotID = 0;
		detectFilterSize = detectAreaSize = detectRectSize = 0;
		detectTypeID = 1;
		memset(detectRobotName, '\0', 256*sizeof(char));
		
		trainBI = 0; updataTask = 1;
		memset(trainBH, '\0', 32*sizeof(unsigned char));

		currRectNum = 0; currTrainID = currChannelID = 0;
		memset(currTrainNum, '\0', 20*sizeof(char));
		memset(currRectArray, 0, MAXRECTNUM*sizeof(CvRect));

		MeasureRectNum = 0;
		memset(MeasureRectID, 0, 10*sizeof(int));
		memset(MeasurePixelMM, 0, 10*sizeof(float));
		memset(MeasureRectDirect, 0, 10*sizeof(int));
		memset(MeasureThreshold, 0, 10*sizeof(int));
		memset(MeasureRect, 0, 10*sizeof(CvRect));

		currSpinRectNum = 0;
		memset(currSpinRectArray, 0, 10*sizeof(CvRect));
		memset(Rect1Threshold, 0, 10*sizeof(float));
		memset(Rect2Threshold, 0, 10*sizeof(float));
		memset(Depth1Threshold, 0, 10*sizeof(float));
		memset(Depth2Threshold, 0, 10*sizeof(float));

	}
}StrickParaIn;

typedef struct tagStrickParaOut
{
	int      MeasureRectNum;
	CvRect   MeasureRect[10];
	float    MeasurePixelValue[10];
	float    MeasureMMValue[10];

	CvPoint  MeasureStartPoint[10];
	CvPoint  MeasureEndPoint[10];

	//���ڼ�¼��ǰͼ���ŵĸ߶ȺͿ��
	int      errorMsgNum;
	RectMsg  errorMsg[MAXERRORNUM]; //ר�����ڼ�¼������Ϣ
	RectMsg  histMsg[MAXERRORNUM];  //���ڼ�¼ת������ʷ��Ϣ

	void Init()
	{
		MeasureRectNum = 0;
		memset(MeasureRect, 0, 10*sizeof(CvRect));
		memset(MeasurePixelValue, 0, 10*sizeof(float));
		memset(MeasureMMValue, 0, 10*sizeof(float));

		memset(MeasureStartPoint, 0, 10*sizeof(CvPoint));
		memset(MeasureEndPoint, 0, 10*sizeof(CvPoint));

		errorMsgNum = 0;	
		memset(errorMsg, 0, MAXERRORNUM*sizeof(RectMsg));
		memset(histMsg, 0, MAXERRORNUM*sizeof(RectMsg));
	}
}StrickParaOut;

typedef struct tagFastParaIn
{
	char currTrainNum[20];
	int  currTrainID;
	int  currChannelID;

	int startImageIndex;
	int endImageIndex;

	int axledistance12;
	int axledistance23;
	int axledistance34;
	

	int axleImageIndex1;
	int axleImageIndex2;
	int axleImageIndex3;
	int axleImageIndex4;

	int axleImagePercent1;
	int axleImagePercent2;
	int axleImagePercent3;
	int axleImagePercent4;

	char trainBH[32];     //�г����
	int  trainBI;     //�г���λ

	int updataTask;  //�Ƿ���³���ģ��

	int detectImageID;
	int detectRobotID;
	char detectRobotName[256];

	int currRectNum[5];
	CvRect currRectArray[5][MAXRECTNUM];
	int currRectType[5][MAXRECTNUM];

	void Init()
	{
		startImageIndex = endImageIndex = 0;
		detectImageID = detectRobotID = 0;
		axleImageIndex1 = axleImageIndex2 = axleImageIndex3 = axleImageIndex4 = 0;
		axleImagePercent1 = axleImagePercent2 = axleImagePercent3 = axleImagePercent4 = 0;
		axledistance12 = axledistance23 = axledistance34 = 0;

		memset(detectRobotName, '\0', 256*sizeof(char));

		trainBI = 0; updataTask = 1;
		memset(trainBH, '\0', 32*sizeof(unsigned char));

		currTrainID = currChannelID = 0;
		memset(currTrainNum, '\0', 20*sizeof(char));

		for(int hIndex = 0; hIndex < 5; hIndex++)
		{
			currRectNum[hIndex] = 0;

			memset(currRectArray[hIndex], 0, MAXRECTNUM*sizeof(CvRect));
			memset(currRectType[hIndex], 0, MAXRECTNUM*sizeof(int));
			
		}	
	}
}FastParaIn;






typedef struct tagFastParaOut
{
	//���ڼ�¼��ǰͼ���ŵĸ߶ȺͿ��
	int imageHeight;
	int imageWidth;    //ͼ��߶ȺͿ��

	int imageAxleMark[SECTIONSIZE];   //ר�����ڱ�ʾ��ǰ�����Ƿ����

	int      errorCurrAxle;           //��¼��ǰ��
	int      errorImageNum;
	int      errorCurrStartImage[5];        //��¼��ǰ��ʼ��
	int      errorHistStartImage[5];

	int      errorMsgNum[5];	
	RectMsg  errorMsg[5][MAXERRORNUM]; //ר�����ڼ�¼������Ϣ

	void Init()
	{
		imageHeight = imageWidth = 0;  errorCurrAxle = errorImageNum = 0;

		memset(imageAxleMark, 0, SECTIONSIZE*sizeof(int));

		for(int hIndex = 0; hIndex < 5; hIndex++)
		{
			errorMsgNum[hIndex] = 0;  
			errorCurrStartImage[hIndex] = 0;  errorHistStartImage[hIndex] = 0;

			memset(errorMsg[hIndex], 0, MAXERRORNUM*sizeof(RectMsg));
		}
		
	}
}FastParaOut;

#define   DETECTTASK          0     //ʶ������
#define   NORMALTASK          1     //��׼����---����ʼ��ģ��
#define   MODELTYPETASK       2     //��׼��׼---����ģ�����
#define   MODELNUMTASK        3     //��׼��׼---����ģ�����

//��Է�����������ݹ���
typedef struct tagAnalyFastTask
{
	int  m_detectTaskType;               //�������ֵ�ǰ�������

	int  m_detectRobotID;                //������ID
	char m_detectRobotName[256];         //�����ֱ�����

	//��Ա�׼ͼ���������Ϣ
	FastParaIn   m_NormParaIn;
	char m_NormImagePath[MAXFILEPATH];   
	char m_NormMsgPath[MAXFILEPATH];   

	//�����ʷͼ���������Ϣ
	FastParaIn   m_HistParaIn;
	char m_HistImagePath[MAXFILEPATH];   
	char m_HistMsgPath[MAXFILEPATH];

	//��Ե�ǰͼ���������Ϣ
	FastParaIn   m_CurrParaIn;
	FastParaOut  m_CurrParaOut;
	char m_CurrImagePath[MAXFILEPATH];   
	char m_CurrMsgPath[MAXFILEPATH];

	char m_TrainType[20];                //��¼����
	char m_NormTrainNum[20];             //��׼����
	char m_CurrTrainNum[20];             //��ǰ����

	int  m_AllChannelID;                //ͨ����
	int  m_AllTrainDirect;              //��������
	int  m_AllTrainFirst;  
	int  m_AllTrainID;                  //�������

	bool m_AllExistTask;                //�Ƿ������Ҫ���������

	char m_CurrDebugPath[MAXFILEPATH];  //���ڼ�¼��ǰ������Ϣ

	void Init()
	{
		m_detectTaskType = DETECTTASK;  m_AllExistTask = false;  m_detectRobotID = 0;

		memset(m_TrainType, '\0', 20*sizeof(char));
		memset(m_NormTrainNum, '\0', 20*sizeof(char));
		memset(m_CurrTrainNum, '\0', 20*sizeof(char));

		m_AllChannelID = m_AllTrainDirect = m_AllTrainFirst = m_AllTrainID = 0;		

		m_NormParaIn.Init();  m_HistParaIn.Init();  m_CurrParaIn.Init();  m_CurrParaOut.Init();
		

		memset(m_detectRobotName, '\0', 256*sizeof(char));

		memset(m_NormImagePath, '\0', MAXFILEPATH*sizeof(unsigned char));
		memset(m_HistImagePath, '\0', MAXFILEPATH*sizeof(unsigned char));
		memset(m_CurrImagePath, '\0', MAXFILEPATH*sizeof(unsigned char));

		memset(m_NormMsgPath, '\0', MAXFILEPATH*sizeof(unsigned char));
		memset(m_HistMsgPath, '\0', MAXFILEPATH*sizeof(unsigned char));
		memset(m_CurrMsgPath, '\0', MAXFILEPATH*sizeof(unsigned char));

		memset(m_CurrDebugPath, '\0', MAXFILEPATH*sizeof(unsigned char));
	}
}AnalyFastTask;

typedef struct tagAnalyStrickTask
{
	int m_detectImageID;

	int  m_detectRobotID;                //������ID
	char m_detectRobotName[256];         //�����ֱ�����

	int  m_detectCheckID;

	//�����ʷͼ���������Ϣ
	StrickParaIn   m_HistParaIn;
	char m_Hist2DImagePath[MAXFILEPATH];
	char m_Hist3DImagePath[MAXFILEPATH];
	char m_HistMsgPath[MAXFILEPATH];

	//��Ե�ǰͼ���������Ϣ
	StrickParaIn   m_CurrParaIn;
	StrickParaOut  m_CurrParaOut;
	char m_Curr2DImagePath[MAXFILEPATH]; 
	char m_Curr3DImagePath[MAXFILEPATH];
	char m_CurrMsgPath[MAXFILEPATH];

	char m_TrainType[20];                //��¼����
	char m_NormTrainNum[20];             //��׼����
	char m_CurrTrainNum[20];             //��ǰ����
	char m_BogieID[20];                  //ת���ID

	int  m_AllChannelID;                //ͨ����
	int  m_AllTrainDirect;              //��������
	int  m_AllTrainFirst;  
	int  m_AllTrainID;                  //�������

	char m_CurrDebugPath[MAXFILEPATH];  //���ڼ�¼��ǰ������Ϣ

	void Init()
	{
		m_detectImageID = m_detectRobotID = 0;

		memset(m_TrainType, '\0', 20);
		memset(m_NormTrainNum, '\0', 20);
		memset(m_CurrTrainNum, '\0', 20);
		memset(m_BogieID, '\0', 20);

		m_AllChannelID = m_AllTrainDirect = m_AllTrainFirst = m_AllTrainID = 0;		

		m_HistParaIn.Init();  m_CurrParaIn.Init();  m_CurrParaOut.Init();

		memset(m_Hist2DImagePath, '\0', MAXFILEPATH*sizeof(unsigned char));
		memset(m_Hist3DImagePath, '\0', MAXFILEPATH*sizeof(unsigned char));
		memset(m_Curr2DImagePath, '\0', MAXFILEPATH*sizeof(unsigned char));
		memset(m_Curr3DImagePath, '\0', MAXFILEPATH*sizeof(unsigned char));

		memset(m_HistMsgPath, '\0', MAXFILEPATH*sizeof(unsigned char));
		memset(m_CurrMsgPath, '\0', MAXFILEPATH*sizeof(unsigned char));

		memset(m_CurrDebugPath, '\0', MAXFILEPATH*sizeof(unsigned char));
	}
}AnalyStrickTask;

#define ArrayString std::vector<CString>

typedef struct tagMeasurePara
{
	int m_gdlength;     // �����ⳤ����ֵ
	int m_stopdepth;      //��Ƚ�������
	int m_startdepth;     //��ȿ�ʼ����
	double m_datajingdu;   //�ܵ繭��ά���ݾ���
	double m_datathreshold;  //�ܵ繭�����ֵ
	int m_pointstart;   //�ܵ繭��ʼ��
	int m_pointend;
	char m_MeasureChannel[20];           //�豸ID��
	int m_camHeight;
	int m_camWidth;
	int m_huaBanDis;
	double m_focal;
	int m_pantographDis;
	int m_pointContact;
	double m_pointValue;
	double m_limitValue;
	double m_measureStart;
	double m_curveHight;

	void Init()
	{
		m_gdlength = 0;
		m_stopdepth = 0;
		m_startdepth = 0;
		m_datajingdu = 0;
		m_datathreshold = 0;
		m_pointstart = 0;
		m_pointend = 0;
		m_camHeight = 0;
		m_camWidth = 0;
		m_huaBanDis = 0;
		m_focal = 0;
		m_pantographDis = 0;
		m_pointContact = 0;
		m_pointValue = 0;
		m_limitValue = 0;
		m_measureStart = 0;
		m_curveHight = 0;
		memset(m_MeasureChannel, '\0', 20 * sizeof(unsigned char));
	}
}MeasurePara;

typedef struct tagDetectPara
{

	char m_DetectChannel[20];           //�豸ID��
	int m_DetectThreshold;
	int m_StartChangeNum;
	int m_EndChangeNum;
	int m_StartForwardNum;
	int m_EndBackwardNum;
	void Init()
	{
		memset(m_DetectChannel, '\0', 20 * sizeof(unsigned char));
		m_DetectThreshold = 0;
		m_StartChangeNum = 0;
		m_EndChangeNum = 0;
		m_StartForwardNum = 0;
		m_EndBackwardNum = 0;
	}
}DetectPara;

typedef struct tagGlobalPara
{
	
	/**************************************
          �������ı궨����
	***************************************/
	int  m_RecvTaskPortNum;         //����ʶ������˿ں�
	int  m_RecvMhPortNum;         //����ʶ������˿ں�
	int  m_RecvXzPortNum;         //����ʶ������˿ں�
	int  m_RecvResultPortNum;
	int  m_SendResultPortNum;       //����ʶ�����˿ں�
	char m_SendResultIP[20];        //����ʶ����IP
	int  m_SendTaskPortNum;
	char m_SendTaskIP[20];

	char m_DeviceId[256];           //�豸ID��

	char m_PZDataPath[MAXFILEPATH];
	char m_PZStandardPath[MAXFILEPATH];

	

	vector<MeasurePara>	m_MeasurePara;
	int m_measureChannelNum;
	vector<DetectPara>  m_DetectPara;
	int m_DetectChannelNum;
	

	int m_picheight;    //����ͼ��߶�
	int m_shibietime;   //��ʱʱ��
	int m_modelControl; //ģ����Ʋ���
	int m_deleteData;
	int m_CaiJiTime;
	int m_DetectTime;

	void Init()
	{
		m_MeasurePara.clear();
		m_measureChannelNum = 0;
		m_DetectPara.clear();
		m_DetectChannelNum = 0;
		m_RecvTaskPortNum = 0;
		m_RecvMhPortNum = 0;
		m_RecvXzPortNum = 0;
		m_SendResultPortNum = 0;
		m_RecvResultPortNum = 0;
		m_SendTaskPortNum = 0;
		memset(m_SendResultIP, '\0', 20 * sizeof(unsigned char));
		memset(m_SendTaskIP, '\0', 20 * sizeof(unsigned char));
		memset(m_DeviceId, '\0', 256 * sizeof(unsigned char));
		memset(m_PZDataPath, '\0', MAXFILEPATH*sizeof(unsigned char));
		memset(m_PZStandardPath, '\0', MAXFILEPATH*sizeof(unsigned char));
		
		m_picheight = 0;
		m_shibietime = 100;
		m_modelControl = 0;
		m_deleteData = 0;
		m_CaiJiTime = 10;
		m_DetectTime = 0;
		
	}
}GlobalPara;

typedef struct tagMeasureResult
{
	char m_DataPath[MAXFILEPATH];
	char m_SavePath[MAXFILEPATH];
	char m_MeasureChannel[20];           //�豸ID��
	int m_pantographNum;
	int m_sdgNum;
	int m_sdgstartLineIndex[MAXPANTO];
	int m_sdgendLineIndex[MAXPANTO];
	int m_startLineIndex[MAXPANTO];
	int m_endLineIndex[MAXPANTO];
	int m_picheight;
	int m_picwidth;
	double m_pantographmaxValue[MAXPANTO];
	double  m_pantographmaxPosition[MAXPANTO];
	double m_pantographminValue[MAXPANTO];
	double m_pantographpjValue[MAXPANTO];
	double  m_pantographminPosition[MAXPANTO];
	double  m_pantographpyValue[MAXPANTO];
	double m_pantographLineValue[MAXPANTO][220];
	MeasurePara m_taskMeasurePara;
	

	void Init()
	{
		memset(m_DataPath, '\0', MAXFILEPATH*sizeof(unsigned char));
		memset(m_SavePath, '\0', MAXFILEPATH*sizeof(unsigned char));
		memset(m_MeasureChannel, '\0', 20 * sizeof(unsigned char));
		m_pantographNum = 0;
		m_picheight = 0;
		m_picwidth = 0;
		m_sdgNum = 0;

		for (int hIndex = 0; hIndex < MAXPANTO; hIndex++)
		{
			m_startLineIndex[hIndex] = 0;
			m_endLineIndex[hIndex] = 0;
			m_pantographmaxValue[hIndex] = 0;
			m_pantographmaxPosition[hIndex] = 0;
			m_pantographminValue[hIndex] = 0;
			m_pantographminPosition[hIndex] = 0;
			m_pantographpjValue[hIndex] = 0;
			m_pantographpyValue[hIndex] = 0;
			m_sdgstartLineIndex[hIndex] = 0;
			m_sdgendLineIndex[hIndex] = 0;
			for (int wIndex = 0; wIndex < 220; wIndex++)
			{
				m_pantographLineValue[hIndex][wIndex] = 0;
			}
			
		}
		m_taskMeasurePara.Init();
		
	}
}MeasureResult;


typedef struct tagMeasureTask
{
	MeasurePara m_taskMeasurePara;

	void Init()
	{
		m_taskMeasurePara.Init();
	}
}MeasureTask;

typedef struct tagDetectTask
{
	DetectPara m_taskDetectPara;
	int m_carriageNum;
	int m_channelNum;

	void Init()
	{
		m_taskDetectPara.Init();
		m_channelNum = 0;
		m_carriageNum = 0;
	}
}DetectTask;


typedef struct tagAnalyDeviceTask
{

	vector<MeasureTask>	m_MeasureTask;
	int m_MeasureTaskNum;
	int m_MeasurePicNum;
	bool m_MeasurePathStatus;
	vector<DetectTask>  m_DetectTask;
	int m_DetectTaskNum;
	int m_DetectPicNum;
	bool m_DetectPathStatus;
	bool m_taskStatus;
	bool m_chuliStatus;


	int  m_isConnect;             //�Ƿ�����
	
	char m_trainDate[20];         //�г����������
	char m_trainTime[20];         //�г����ʱ��

	char m_trainFirstNum[20];         //�г�1����
	char m_trainFirstType[20];        //�г�1����

	char m_trainLastNum[20];          //�г�2����
	char m_trainLastType[20];         //�г�2����

	char m_trainFirstDirection[20];          //�г�1����
	char m_trainLastDirection[20];         //�г�2����


	char m_dataDir[MAXFILEPATH];       //���ݵ�ַ
	
	char m_MeasurePath[MAXFILEPATH];
	char m_DetectPath[MAXFILEPATH];
	
	void Init()
	{
		m_taskStatus = false;
		m_MeasurePathStatus = false;
		m_DetectPathStatus = false;
		m_chuliStatus = false;

		m_DetectPicNum = 0;
		m_MeasurePicNum = 0;
		m_MeasureTask.clear();
		m_MeasureTaskNum = 0;
		m_DetectTask.clear();
		m_DetectTaskNum = 0;

		m_isConnect = 0;

		memset(m_trainDate, '\0', 20 * sizeof(unsigned char));
		memset(m_trainTime, '\0', 20 * sizeof(unsigned char));

		memset(m_trainFirstNum, '\0', 20 * sizeof(unsigned char));
		memset(m_trainFirstType, '\0', 20 * sizeof(unsigned char));

		memset(m_trainLastNum, '\0', 20 * sizeof(unsigned char));
		memset(m_trainLastType, '\0', 20 * sizeof(unsigned char));

		memset(m_trainFirstDirection, '\0', 20 * sizeof(unsigned char));
		memset(m_trainLastDirection, '\0', 20 * sizeof(unsigned char));

		memset(m_dataDir, '\0', MAXFILEPATH*sizeof(unsigned char));
	
		memset(m_MeasurePath, '\0', MAXFILEPATH*sizeof(unsigned char));

		memset(m_DetectPath, '\0', MAXFILEPATH*sizeof(unsigned char));
		

	}
}AnalyDeviceTask;

typedef struct tagAnalyGrateTask
{
	
	GlobalPara m_currDevicePara;
	char m_StandardPath[MAXFILEPATH];
	
	char m_CurrPath[MAXFILEPATH];
	char m_dataPath[MAXFILEPATH];
	char m_CurrSendMsg[MAXFILEPATH];	
	bool m_saveCtr;
	bool m_locateCtr;
	bool m_standardCtr;
	int m_grateIndex;

	void Init()
	{
		m_currDevicePara.Init();
		m_saveCtr = false;
		m_locateCtr = false;
		m_standardCtr = false;
		m_grateIndex = 0;
		memset(m_StandardPath, '\0', MAXFILEPATH*sizeof(unsigned char));
		memset(m_dataPath, '\0', MAXFILEPATH*sizeof(unsigned char));
		memset(m_CurrPath, '\0', MAXFILEPATH*sizeof(unsigned char));
	}
}AnalyGrateTask;


#endif//_AUTODETECTITEM_STRUCR_H_