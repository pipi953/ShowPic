//宏定义文件---定义公用的宏
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
//定义检测结构体
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

//字符对象的描述
typedef struct cvOCRObj
{
	int    ocrIndex;
	int    ocrMerge; 
	CvRect ocrRect;
}cvOCRObj;

//线段的直线方程是：ax+by+c=0
typedef struct cvLineObj
{
	float sinAValue;          //当前线段的正余弦值
	float cosBValue;

	float InterceptValue;     //参数C值

	float  LineLength;        //当前线段长度

	CvPoint Point1;           //线段的起点和终点值
	CvPoint Point2;

	float   LineDegree;       //直线度参量
}cvLineObj;

typedef struct tagLinePair
{
	cvLineObj currLine;
	cvLineObj histLine;
}LinePair;

typedef struct cvCircleObj
{
	float Radius;            //圆周半径
	CvPointF CirclePoint;    //圆心

	float CloseDegree;       //闭合度

	float SumValue[10];       //当前圆周对应的临时变量
}cvCircleObj;

typedef struct cvEllipseObj
{
	CvPointF center;  
	CvSize2D32f size;

	float angle;          
}cvEllipseObj;

typedef struct cvRectObj      //矩形区域的结构对象
{
	CvPoint FirstPoint;
	CvPoint SecondPoint;
	CvPoint ThirdPoint;
	CvPoint FourthPoint;
}cvRectObj;

//基于字符特征识别的对应结构
typedef struct CharFeature
{
	int EdgeNum[3];              //字符的边缘数目

	float* scMoment;

	int SCMomentSize;

	int EdgePointNum;

	MomentInvariant InvarMoment; //边缘统计不变矩特性
}CharFeature;

typedef struct tagMatrixArray
{
	float* data;    //数组的存储空间
	int    Height;  //二维数组的高度
	int    Width;   //二维数组的高度
	int    EdgeNum; //用于存储临时变量
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

	int    currId;      //当前故障位置Id
	
	int    currType;    //当前故障检测类型
	int    errorGrade;  //错误等级
	int    dibanType;
	int    bujianType;
}RectMsg;

#define ArrayRectMsg std::vector<RectMsg>
typedef struct ListRectMsg{
	ArrayRectMsg * Item;     //矢量指针的指针
}ListRectMsg;

#define ArrayPointPair std::vector<PointPair>
typedef struct ListPointPair{
	ArrayPointPair * Item;     //矢量指针的指针
}ListPointPair;

#define ArrayBlobInfo std::vector<BlobInfo>
typedef struct ListBlobInfo{
	ArrayBlobInfo * Item;
}ListBlobInfo;

#define ArrayInt std::vector<int>
typedef struct ListInt{
	ArrayInt * Item;     //矢量指针的指针
}ListInt;

#define ArrayChar std::vector<char*>
typedef struct ListChar{
	ArrayChar * Item;     //矢量指针的指针
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
//定义PointPair的二维数组
#define ArrayTwoPointPair std::vector<ArrayPointPair*>
typedef struct ListTwoPointPair{
	ArrayTwoPointPair * Item;
}ListTwoPointPair;

typedef struct tagMarkMsg
{
	int    markImageIndex;

	char   bigFileMsg[1024];
	char   smallFileMsg[1024];

	bool      ocrToolResult;   //字符识别结果
	cvRectObj ocrRectObj;      //用于记录字符区域
	char      ocrChar[20];
	float     ocrRectValue;    //用于记录当前字符区域面积

	bool      kiloToolResult;   //公里标识别结果
	cvRectObj kiloRectObj;      //用于记录公里标区域
	char      kiloChar[20];
	float     kiloRectValue;    //用于记录当前公里标区域面积

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
	ArrayMarkMsg * Item;     //矢量指针的指针
}ListMarkMsg;

#endif   //_PUBLIC_FILE_H_