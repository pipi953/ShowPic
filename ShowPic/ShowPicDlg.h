
// ShowPicDlg.h : ͷ�ļ�
//

#pragma once
#include "AutoDetectItemStruct.h"
#define IMAGE_CHANNELS 3
// CShowPicDlg �Ի���
class CShowPicDlg : public CDialogEx
{
// ����
public:
	CShowPicDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SHOWPIC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	IplImage* m_ShowPic;
	afx_msg void OnDestroy();
	void ShowImage(IplImage* img, UINT ID);
	afx_msg void OnClickedButtonShowpic();
};
