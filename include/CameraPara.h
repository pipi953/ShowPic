//宏定义文件---定义公用的宏
#ifndef _CAMERA_PARA_H_
#define _CAMERA_PARA_H_
/*******************************************************
      相机采集的相关参数
*********************************************************/
#define CAMERANUM     2

#define BIGCAMERA     0
#define SMALLCAMERA   1

#define IMAGEBUFFER 40

#define INITRESULT  -20
#define PRCERESULT  -2

typedef unsigned int        UINT;
typedef unsigned long       DWORD;
typedef wchar_t             WCHAR;
typedef unsigned char       BYTE;

//相机硬件的配置信息
typedef struct tagCameraGrabPara
{	
	UINT m_ImageWidth;        //图像宽度	
	UINT m_ImageHeight;       //图像高度
	UINT m_ImageChannel;      //图像通道
	UINT m_CameraChannel;     //相机通道
	
	void Init()             //设置相机信息的初值
	{
		m_ImageWidth = 0;        //图像宽度	
		m_ImageHeight = 0;       //图像高度
		m_ImageChannel = 1;      //图像通道

		m_CameraChannel = 0;
	};
}CameraGrabPara;

//图像结构类定义
typedef struct tagImageUnitBase
{
	//宽度
	UINT m_dwWidth;
	//高度
	UINT m_dwHeight;
	//图像格式
	UINT   m_dwImageFormat;
	//图像数据长度
	UINT  m_dwImageDataLen;
	//图像数据指针
	unsigned char* m_dwImageData;
}ImageUnitBase;

//分析结构类定义---针对输入输出获取对应信息
typedef struct tagAnalyUnitBase
{
	void*         pInPara;
	ImageUnitBase InImageUnit;
	void*         pOutPara;

	UINT          m_nImagePara;     //当前图像处理状态

	UINT          m_iImageResult;
	UINT          m_iImagePos;      //用于当前正在处理胶囊位置
	UINT          m_nPictureID;     //产生该处理任务时的PictrueID
}AnalyUnitBase;

/********************************************************
定义相机的各个状态
ceOpen-打开，相机连接 ceClose-关闭，相机断开
ceStart-启动采集线程  ceStop-关闭采集线程
ceGrabbing-正在采集   ceIdl-空闲，未采集
cePause-暂停采集      ceNoPause-非暂停，可采集
*********************************************************/
typedef enum CameraEvent {ceOpen = 0, ceClose, ceStart, ceStop, ceGrabbing, ceIdle, cePause, ceNoPause};

#endif//_CAMERA_PARA_H_