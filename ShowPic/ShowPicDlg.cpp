
// ShowPicDlg.cpp : ʵ���ļ�
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

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
CLogFile  m_LogFile;
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CShowPicDlg �Ի���



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


// CShowPicDlg ��Ϣ�������

BOOL CShowPicDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	CRect rect_curr; //����
	CvSize ImgSize;

	GetDlgItem(IDC_SHOWPIC)->GetClientRect(rect_curr);
	ImgSize.height = rect_curr.Height();
	ImgSize.width = rect_curr.Width();
	m_ShowPic = cvCreateImage(ImgSize, IPL_DEPTH_8U, IMAGE_CHANNELS);
	if (m_ShowPic)                                                           // ����һ����ʾ��ͼƬ��������  
		cvZero(m_ShowPic);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CShowPicDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
	CDialog::OnPaint();   // �ػ�Ի���        
	CDialog::UpdateWindow();   // ����windows���ڣ�������ⲽ���ã�ͼƬ��ʾ����������� 
	ShowImage(m_ShowPic, IDC_SHOWPIC);     // �ػ�ͼƬ����
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CShowPicDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CShowPicDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO:  �ڴ˴������Ϣ����������
	cvReleaseImage(&m_ShowPic);
}
void CShowPicDlg::ShowImage(IplImage* img, UINT ID)// ID ��Picture Control�ؼ���ID��  
{
	CDC* pDC = GetDlgItem(ID)->GetDC();// �����ʾ�ؼ��� DC  
	HDC hDC = pDC->GetSafeHdc();// ��ȡ HDC(�豸���) �����л�ͼ����  

	CRect rect;
	GetDlgItem(ID)->GetClientRect(&rect);
	int rw = rect.right - rect.left;    // ���picture control�Ŀ�͸�  
	int rh = rect.bottom - rect.top;
	int iw = img->width;             // ��ȡͼƬ�Ŀ�͸�  
	int ih = img->height;
	int tx = (int)(rw - iw) / 2;                                       // ʹͼƬ����ʾλ�������ڿؼ�������  
	int ty = (int)(rh - ih) / 2;
	SetRect(rect, tx, ty, tx + iw, ty + ih);

	CvvImage cimg;
	cimg.CopyOf(img);    // ����ͼƬ  
	cimg.DrawToHDC(hDC, &rect);

	ReleaseDC(pDC);
}

void CShowPicDlg::OnClickedButtonShowpic()
{
	//��մ���
	ShowImage(m_ShowPic, IDC_SHOWPIC);	
	CString filePath; //������ļ���·��	
	//ѡ���ļ��Ի���
	CString fileFilter = _T("�ļ�(*.jpg;*.bmp)|*.jpg;*.bmp|All File (*.*)|*.*||"); //�����ļ�����	
	CFileDialog fileDlg(true, _T(""), _T(""), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, fileFilter, NULL); 	//����ѡ���ļ��Ի���	
	fileDlg.m_ofn.lpstrInitialDir = "C:\\";//����Ĭ�ϴ��ļ���
	if (fileDlg.DoModal() == IDOK)
	{
		filePath = fileDlg.GetPathName();//�õ��������ļ�����Ŀ¼����չ��  				
	}
	//��ȡͼƬ
	IplImage* currImage = cvLoadImage(filePath, 1);
	if (currImage != NULL)
	{
		//����ͼƬ��С�Ϳؼ���С��ͼƬ������Ӧ����
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
		//ȷ����ʾͼƬ��С
		CvSize ImgSize;
		ImgSize.width = bwidth;
		ImgSize.height = bheight;
		IplImage* m_bShowPic = cvCreateImage(ImgSize, IPL_DEPTH_8U, currImage->nChannels);
		if (m_bShowPic)                                                           // ����һ����ʾ��ͼƬ��������  
			cvZero(m_bShowPic);
		//����ͼƬ
		cvResize(currImage, m_bShowPic, INTER_LINEAR);
		m_LogFile.LogFormat(NULL, LOG_INFO, "ͼ��򿪳ɹ�!\n");
		ShowImage(m_bShowPic, IDC_SHOWPIC);     // �ػ�ͼƬ����
		cvReleaseImage(&m_bShowPic);
	}
	
	cvReleaseImage(&currImage);
}
