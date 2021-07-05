//�궨���ļ�---���幫�õĺ�
#ifndef _PUBLIC_FILE_H_
#define _PUBLIC_FILE_H_

#include <opencv2/opencv.hpp>

#include <string>
#include <malloc.h>
#include <string.h>
#include <vector>
#include <atltime.h>
#include <Windows.h>
#include <direct.h>
#include <io.h>
#include <iostream>

using namespace std;
using namespace cv;

#define VL_MIN(x,y) (((x)<(y))?(x):(y))
#define VL_MAX(x,y) (((x)>(y))?(x):(y))
#define VL_PI        3.1415926
#define RADIAN       0.017453292519943 // pi/180
#define DEGREE       57.29577951308232 // 180/pi
#define MAX_FILE     512

#define ANGLEERROR      1.6

#ifndef GenMsgLIB
#   if defined DLL_EXPORT
#       define GM_EXPORT __declspec(dllexport)
#   else
#       define GM_EXPORT __declspec(dllimport)
#   endif
#else
#    define  GM_EXPORT
#endif

#ifdef UPPROCESS
#define DLLAPI    extern "C"
#define STDCALL   _stdcall
#endif
//������ṹ��
typedef struct RectInfo {
	float x1;
	float y1;
	float x2;
	float y2;
	float score;
	int label;
} RectInfo;

typedef struct tagMomentInvariant
{
	int   EdgeNum;
	float MeanValue;
	float StdValue;
	float PeakValue;
}MomentInvariant;

typedef struct tagHuMoment
{
	float HuValue1;
	float HuValue2;
	float HuValue3;
	float HuValue4;
	float HuValue5;
	float HuValue6;
	float HuValue7;
}HuMoment;

typedef struct tagProjFeature 
{
	int Height;
	int Width;

	float* LeftProj;
	float* RightProj;

	float* UpProj;
	float* DownProj;
}ProjFeature;

typedef struct tagHole
{
	int Left;
	int Right;
}Hole;

typedef struct tagCvImage
{
	int height;
	int width;
	unsigned char* data;
}CvImage;

typedef struct tagCvPointF
{
	float x;
	float y;
}CvPointF;

//�ַ����������
typedef struct cvOCRObj
{
	int    ocrIndex;
	int    ocrMerge; 
	CvRect ocrRect;
}cvOCRObj;

//�߶ε�ֱ�߷����ǣ�ax+by+c=0
typedef struct cvLineObj
{
	float sinAValue;          //��ǰ�߶ε�������ֵ
	float cosBValue;

	float InterceptValue;     //����Cֵ

	float  LineLength;        //��ǰ�߶γ���

	CvPoint Point1;           //�߶ε������յ�ֵ
	CvPoint Point2;

	float   LineDegree;       //ֱ�߶Ȳ���
}cvLineObj;

typedef struct tagLinePair
{
	cvLineObj currLine;
	cvLineObj histLine;
}LinePair;

typedef struct cvCircleObj
{
	float Radius;            //Բ�ܰ뾶
	CvPointF CirclePoint;    //Բ��

	float CloseDegree;       //�պ϶�

	float SumValue[10];       //��ǰԲ�ܶ�Ӧ����ʱ����
}cvCircleObj;

typedef struct cvEllipseObj
{
	CvPointF center;  
	CvSize2D32f size;

	float angle;          
}cvEllipseObj;

typedef struct cvRectObj      //��������Ľṹ����
{
	CvPoint FirstPoint;
	CvPoint SecondPoint;
	CvPoint ThirdPoint;
	CvPoint FourthPoint;
}cvRectObj;

//�����ַ�����ʶ��Ķ�Ӧ�ṹ
typedef struct CharFeature
{
	int EdgeNum[3];              //�ַ��ı�Ե��Ŀ

	float* scMoment;

	int SCMomentSize;

	int EdgePointNum;

	MomentInvariant InvarMoment; //��Եͳ�Ʋ��������
}CharFeature;

typedef struct tagMatrixArray
{
	float* data;    //����Ĵ洢�ռ�
	int    Height;  //��ά����ĸ߶�
	int    Width;   //��ά����ĸ߶�
	int    EdgeNum; //���ڴ洢��ʱ����
}MatrixArray;

typedef struct tagBlobInfo
{
	CvRect blobRect;

	int    nEdgeNum;
	int    nAreaNum;
	CvPoint CirclePoint;
}BlobInfo;

typedef struct tagPointPair
{
	CvPoint histPoint;
	CvPoint currPoint;
}PointPair;

typedef struct tagRectMsg
{
	CvRect currRect;
	CvRect histRect;

	int    currId;      //��ǰ����λ��Id
	
	int    currType;    //��ǰ���ϼ������
	int    errorGrade;  //����ȼ�
	int    dibanType;
	int    bujianType;
}RectMsg;

#define ArrayRectMsg std::vector<RectMsg>
typedef struct ListRectMsg{
	ArrayRectMsg * Item;     //ʸ��ָ���ָ��
}ListRectMsg;

#define ArrayPointPair std::vector<PointPair>
typedef struct ListPointPair{
	ArrayPointPair * Item;     //ʸ��ָ���ָ��
}ListPointPair;

#define ArrayBlobInfo std::vector<BlobInfo>
typedef struct ListBlobInfo{
	ArrayBlobInfo * Item;
}ListBlobInfo;

#define ArrayInt std::vector<int>
typedef struct ListInt{
	ArrayInt * Item;     //ʸ��ָ���ָ��
}ListInt;

#define ArrayChar std::vector<char*>
typedef struct ListChar{
	ArrayChar * Item;     //ʸ��ָ���ָ��
}ListChar;

#define ArrayFloat std::vector<float>
typedef struct ListFloat{
	ArrayFloat * Item;
}ListFloat;

#define ArrayPoint std::vector<CvPoint>
typedef struct ListPoint{
	ArrayPoint * Item;
}ListPoint;

#define ArrayPointF std::vector<CvPointF>
typedef struct ListPointF{
	ArrayPointF * Item;
}ListPointF;

#define ArrayRect std::vector<CvRect>
typedef struct ListRect{
	ArrayRect * Item;
}ListRect;

#define ArrayLine std::vector<cvLineObj>
typedef struct ListLine{
	ArrayLine * Item;
}ListLine;

#define ArrayOCR std::vector<cvOCRObj>
typedef struct ListOCR{
	ArrayOCR * Item;
}ListOCR;

#define ArrayRectObj std::vector<cvRectObj>
typedef struct ListRectObj{
	ArrayRectObj * Item;
}ListRectObj;

#define ArrayCircle std::vector<cvCircleObj>
typedef struct ListCircle{
	ArrayCircle * Item;
}ListCircle;


#define ArrayString std::vector<CString>
typedef struct ListCString
{
	ArrayString * Item;
}ListCString;
//����PointPair�Ķ�ά����
#define ArrayTwoPointPair std::vector<ArrayPointPair*>
typedef struct ListTwoPointPair{
	ArrayTwoPointPair * Item;
}ListTwoPointPair;

typedef struct tagMarkMsg
{
	int    markImageIndex;

	char   bigFileMsg[1024];
	char   smallFileMsg[1024];

	bool      ocrToolResult;   //�ַ�ʶ����
	cvRectObj ocrRectObj;      //���ڼ�¼�ַ�����
	char      ocrChar[20];
	float     ocrRectValue;    //���ڼ�¼��ǰ�ַ��������

	bool      kiloToolResult;   //�����ʶ����
	cvRectObj kiloRectObj;      //���ڼ�¼���������
	char      kiloChar[20];
	float     kiloRectValue;    //���ڼ�¼��ǰ������������

	void Init()
	{
		memset(bigFileMsg, '\0', 1024*sizeof(char));
		memset(smallFileMsg, '\0', 1024*sizeof(char));

		memset(ocrChar, '\0', 20*sizeof(char));
		memset(kiloChar, '\0', 20*sizeof(char));

		ocrToolResult = false; kiloToolResult = false; 

		memset(&ocrRectObj, 0, sizeof(cvRectObj));
		memset(&kiloRectObj, 0, sizeof(cvRectObj));

		ocrRectValue = 0; kiloRectValue = 0; markImageIndex = 0; 
	}
}MarkMsg;

#define ArrayMarkMsg std::vector<MarkMsg>
typedef struct ListMarkMsg{
	ArrayMarkMsg * Item;     //ʸ��ָ���ָ��
}ListMarkMsg;

#endif   //_PUBLIC_FILE_H_