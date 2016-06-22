
// AlgorithmTestDlg.h : ���Y��
//

#pragma once
#include "C:\OpenCV3.1\opencv\build\include\opencv2\core\mat.hpp"
#include <opencv2/opencv.hpp>  //�Y���
#include "afxwin.h"
using namespace cv;  //�]�tcv�R�W�Ŷ�

// CAlgorithmTestDlg ��ܤ��
class CAlgorithmTestDlg : public CDialogEx
{
// �غc
public:
	CAlgorithmTestDlg(CWnd* pParent = NULL);	// �зǫغc�禡

// ��ܤ�����
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ALGORITHMTEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �䴩


// �{���X��@
protected:
	HICON m_hIcon;

	// ���ͪ��T�������禡
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	Mat m_srcImage;
	Mat m_ImgStep1;
	Mat m_ImgStep2;
	Mat m_ImgStep3;
	Mat m_ImgStep4;
	Mat m_ImgStep5;
	
	unsigned char m_coreSize;
	
	void InitialLayout(void);
	void LoadSrcImg(void);
	//void DispImg(int controlID, Mat srcImg);
	void DispImg(int step, int controlID, Mat srcImg);
	
	CRect Img_Scale(CRect DispArea, unsigned int ImgWidth , unsigned int ImgHeight);

	void InitPreviewWindow(unsigned int Step);
	void LoadImg(unsigned int Step);
	void Img_Update(void);
	void Img_Process(unsigned int Step);

	afx_msg void OnBnClickedOk();
	CButton m_Ctrl_Check_Equalizer;
	afx_msg void OnClickedCheckEqualizer();
	
	CButton m_CB_3X3;
	CButton m_CB_5X5;
	CButton m_CB_7X7;
	afx_msg void OnBnClickedCheck3x3();
	afx_msg void OnBnClickedCheck5x5();
	afx_msg void OnBnClickedCheck7x7();
	
};
