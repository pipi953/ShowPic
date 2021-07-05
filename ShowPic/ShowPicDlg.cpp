
// ShowPicDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ShowPic.h"
#include "ShowPicDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "CvvImage.h"
#include <LogFile/LogFile.h>
#include <Utility/IniFile.h>
#include <Utility/Utility.h>

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
CLogFile  m_LogFile;
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CShowPicDlg 对话框



CShowPicDlg::CShowPicDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CShowPicDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CShowPicDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CShowPicDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_SHOWPIC, &CShowPicDlg::OnClickedButtonShowpic)
END_MESSAGE_MAP()


// CShowPicDlg 消息处理程序

BOOL CShowPicDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	CRect rect_curr; //矩形
	CvSize ImgSize;

	GetDlgItem(IDC_SHOWPIC)->GetClientRect(rect_curr);
	ImgSize.height = rect_curr.Height();
	ImgSize.width = rect_curr.Width();
	m_ShowPic = cvCreateImage(ImgSize, IPL_DEPTH_8U, IMAGE_CHANNELS);
	if (m_ShowPic)                                                           // 对上一幅显示的图片数据清零  
		cvZero(m_ShowPic);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CShowPicDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CShowPicDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
	CDialog::OnPaint();   // 重绘对话框        
	CDialog::UpdateWindow();   // 更新windows窗口，如果无这步调用，图片显示还会出现问题 
	ShowImage(m_ShowPic, IDC_SHOWPIC);     // 重绘图片函数
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CShowPicDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CShowPicDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO:  在此处添加消息处理程序代码
	cvReleaseImage(&m_ShowPic);
}
void CShowPicDlg::ShowImage(IplImage* img, UINT ID)// ID 是Picture Control控件的ID号  
{
	CDC* pDC = GetDlgItem(ID)->GetDC();// 获得显示控件的 DC  
	HDC hDC = pDC->GetSafeHdc();// 获取 HDC(设备句柄) 来进行绘图操作  

	CRect rect;
	GetDlgItem(ID)->GetClientRect(&rect);
	int rw = rect.right - rect.left;    // 求出picture control的宽和高  
	int rh = rect.bottom - rect.top;
	int iw = img->width;             // 读取图片的宽和高  
	int ih = img->height;
	int tx = (int)(rw - iw) / 2;                                       // 使图片的显示位置正好在控件的正中  
	int ty = (int)(rh - ih) / 2;
	SetRect(rect, tx, ty, tx + iw, ty + ih);

	CvvImage cimg;
	cimg.CopyOf(img);    // 复制图片  
	cimg.DrawToHDC(hDC, &rect);

	ReleaseDC(pDC);
}

void CShowPicDlg::OnClickedButtonShowpic()
{
	//清空窗口
	ShowImage(m_ShowPic, IDC_SHOWPIC);	
	CString filePath; //保存打开文件的路径	
	//选择文件对话框
	CString fileFilter = _T("文件(*.jpg;*.bmp)|*.jpg;*.bmp|All File (*.*)|*.*||"); //设置文件过滤	
	CFileDialog fileDlg(true, _T(""), _T(""), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, fileFilter, NULL); 	//弹出选择文件对话框	
	fileDlg.m_ofn.lpstrInitialDir = "C:\\";//设置默认打开文件夹
	if (fileDlg.DoModal() == IDOK)
	{
		filePath = fileDlg.GetPathName();//得到完整的文件名和目录名拓展名  				
	}
	//读取图片
	IplImage* currImage = cvLoadImage(filePath, 1);
	if (currImage != NULL)
	{
		//根据图片大小和控件大小对图片进行相应缩放
		CRect rect;
		GetDlgItem(IDC_SHOWPIC)->GetClientRect(&rect);
		double bx = double(currImage->width) / rect.Width();
		double by = double(currImage->height) / rect.Height();
		int bheight = 0, bwidth = 0;
		if (bx > by)
		{
			bwidth = rect.Width();
			bheight = currImage->height / bx;
			if (bheight > rect.Height())
			{
				bheight = rect.Height();
			}
		}
		else
		{
			bwidth = currImage->width/by;
			bheight = rect.Height();
			if (bwidth > rect.Width())
			{
				bwidth = rect.Width();
			}
		}
		//确定显示图片大小
		CvSize ImgSize;
		ImgSize.width = bwidth;
		ImgSize.height = bheight;
		IplImage* m_bShowPic = cvCreateImage(ImgSize, IPL_DEPTH_8U, currImage->nChannels);
		if (m_bShowPic)                                                           // 对上一幅显示的图片数据清零  
			cvZero(m_bShowPic);
		//缩放图片
		cvResize(currImage, m_bShowPic, INTER_LINEAR);
		m_LogFile.LogFormat(NULL, LOG_INFO, "图像打开成功!\n");
		ShowImage(m_bShowPic, IDC_SHOWPIC);     // 重绘图片函数
		cvReleaseImage(&m_bShowPic);
	}
	
	cvReleaseImage(&currImage);
}
