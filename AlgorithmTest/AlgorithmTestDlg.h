
// AlgorithmTestDlg.h : 標頭檔
//

#pragma once
#include "C:\OpenCV3.1\opencv\build\include\opencv2\core\mat.hpp"
#include <opencv2/opencv.hpp>  //頭文件
#include "afxwin.h"
using namespace cv;  //包含cv命名空間

// CAlgorithmTestDlg 對話方塊
class CAlgorithmTestDlg : public CDialogEx
{
// 建構
public:
	CAlgorithmTestDlg(CWnd* pParent = NULL);	// 標準建構函式

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ALGORITHMTEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支援


// 程式碼實作
protected:
	HICON m_hIcon;

	// 產生的訊息對應函式
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
