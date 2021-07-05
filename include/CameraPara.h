//�궨���ļ�---���幫�õĺ�
#ifndef _CAMERA_PARA_H_
#define _CAMERA_PARA_H_
/*******************************************************
      ����ɼ�����ز���
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

//���Ӳ����������Ϣ
typedef struct tagCameraGrabPara
{	
	UINT m_ImageWidth;        //ͼ����	
	UINT m_ImageHeight;       //ͼ��߶�
	UINT m_ImageChannel;      //ͼ��ͨ��
	UINT m_CameraChannel;     //���ͨ��
	
	void Init()             //���������Ϣ�ĳ�ֵ
	{
		m_ImageWidth = 0;        //ͼ����	
		m_ImageHeight = 0;       //ͼ��߶�
		m_ImageChannel = 1;      //ͼ��ͨ��

		m_CameraChannel = 0;
	};
}CameraGrabPara;

//ͼ��ṹ�ඨ��
typedef struct tagImageUnitBase
{
	//���
	UINT m_dwWidth;
	//�߶�
	UINT m_dwHeight;
	//ͼ���ʽ
	UINT   m_dwImageFormat;
	//ͼ�����ݳ���
	UINT  m_dwImageDataLen;
	//ͼ������ָ��
	unsigned char* m_dwImageData;
}ImageUnitBase;

//�����ṹ�ඨ��---������������ȡ��Ӧ��Ϣ
typedef struct tagAnalyUnitBase
{
	void*         pInPara;
	ImageUnitBase InImageUnit;
	void*         pOutPara;

	UINT          m_nImagePara;     //��ǰͼ����״̬

	UINT          m_iImageResult;
	UINT          m_iImagePos;      //���ڵ�ǰ���ڴ�����λ��
	UINT          m_nPictureID;     //�����ô�������ʱ��PictrueID
}AnalyUnitBase;

/********************************************************
��������ĸ���״̬
ceOpen-�򿪣�������� ceClose-�رգ�����Ͽ�
ceStart-�����ɼ��߳�  ceStop-�رղɼ��߳�
ceGrabbing-���ڲɼ�   ceIdl-���У�δ�ɼ�
cePause-��ͣ�ɼ�      ceNoPause-����ͣ���ɲɼ�
*********************************************************/
typedef enum CameraEvent {ceOpen = 0, ceClose, ceStart, ceStop, ceGrabbing, ceIdle, cePause, ceNoPause};

#endif//_CAMERA_PARA_H_