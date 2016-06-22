
// AlgorithmTestDlg.cpp : ��@��
//

#include "stdafx.h"
#include "AlgorithmTest.h"
#include "AlgorithmTestDlg.h"
#include "afxdialogex.h"

#include <opencv2/opencv.hpp>  //�Y���
using namespace cv;  //�]�tcv�R�W�Ŷ�

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

char *title[10]={
"IMG_ORIGINAL",
"IMG_STEP1",	
"IMG_STEP2",	
"IMG_STEP3",	
"IMG_STEP4",	
"IMG_STEP5",	
};

// �� App About �ϥ� CAboutDlg ��ܤ��

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ܤ�����
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩

// �{���X��@
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CAlgorithmTestDlg ��ܤ��



CAlgorithmTestDlg::CAlgorithmTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ALGORITHMTEST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAlgorithmTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_EQUALIZER, m_Ctrl_Check_Equalizer);
	DDX_Control(pDX, IDC_CHECK_3X3, m_CB_3X3);
	DDX_Control(pDX, IDC_CHECK_5x5, m_CB_5X5);
	DDX_Control(pDX, IDC_CHECK_7X7, m_CB_7X7);
}

BEGIN_MESSAGE_MAP(CAlgorithmTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CAlgorithmTestDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CHECK_EQUALIZER, &CAlgorithmTestDlg::OnClickedCheckEqualizer)
	ON_BN_CLICKED(IDC_CHECK_3X3, &CAlgorithmTestDlg::OnBnClickedCheck3x3)
	ON_BN_CLICKED(IDC_CHECK_5x5, &CAlgorithmTestDlg::OnBnClickedCheck5x5)
	ON_BN_CLICKED(IDC_CHECK_7X7, &CAlgorithmTestDlg::OnBnClickedCheck7x7)
END_MESSAGE_MAP()


// CAlgorithmTestDlg �T���B�z�`��

BOOL CAlgorithmTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �N [����...] �\���[�J�t�Υ\���C

	// IDM_ABOUTBOX �����b�t�ΩR�O�d�򤧤��C
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

	// �]�w����ܤ�����ϥܡC�����ε{�����D�������O��ܤ���ɡA
	// �ج[�|�۰ʱq�Ʀ��@�~
	SetIcon(m_hIcon, TRUE);			// �]�w�j�ϥ�
	SetIcon(m_hIcon, FALSE);		// �]�w�p�ϥ�

	// TODO: �b���[�J�B�~����l�]�w

	InitialLayout();
	
	InitPreviewWindow(0);
	InitPreviewWindow(1);
	InitPreviewWindow(2);
	InitPreviewWindow(3);
	InitPreviewWindow(4);
	InitPreviewWindow(5);
	//LoadSrcImg();

	m_Ctrl_Check_Equalizer.SetCheck(TRUE);
	
	m_coreSize = 3;
	m_CB_3X3.SetCheck(TRUE);
	m_CB_5X5.SetCheck(FALSE);
	m_CB_7X7.SetCheck(FALSE);
	
	//Call image process flow
	Img_Update();

	return TRUE;  // �Ǧ^ TRUE�A���D�z�ﱱ��]�w�J�I
}

void CAlgorithmTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �p�G�N�̤p�ƫ��s�[�J�z����ܤ���A�z�ݭn�U�C���{���X�A
// �H�Kø�s�ϥܡC���ϥΤ��/�˵��Ҧ��� MFC ���ε{���A
// �ج[�|�۰ʧ������@�~�C

void CAlgorithmTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ø�s���˸m���e

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// �N�ϥܸm����Τ�ݯx��
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �yø�ϥ�
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//[Test for display image on CStatic object
		CDialog::OnPaint();
		// ��ø��ܮ�
		CDialog::UpdateWindow();
		// ��swindows�����A�p�G�L�o�B�եΡA�Ϥ�����ٷ|�X�{���D
		//ShowImage(TheImage, IDC_ShowImg);
		//cv::imshow("IDC_ShowImg", TheImage);
		//]
		
		CDialogEx::OnPaint();
	}
}

// ��ϥΪ̩즲�̤p�Ƶ����ɡA
// �t�ΩI�s�o�ӥ\����o�����ܡC
HCURSOR CAlgorithmTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CAlgorithmTestDlg::InitialLayout(void)
{
	//Step1. Set window size to 1366x768
	this->MoveWindow(0,0,1366,768);

}

void CAlgorithmTestDlg::LoadSrcImg(void)
{
	Mat dstSize;
	Mat dispArea;
	
	m_srcImage = imread("SolarPanel.png");

	if (m_srcImage.empty())
		return;
	

	//[ �o�@�q�ΨӨ��oMFC�إߪ�CStatic����j�p�P��m, 
	CRect DispRect, targetRect;
	CWnd *pWnd = GetDlgItem(IDC_IMG_ORIGINAL);

	pWnd->GetWindowRect(&DispRect);
	ScreenToClient(&DispRect); 	

	/*
	//Clear background first
	Mat mat_Bg(DispRect.Height(), DispRect.Width(),  CV_8UC3, Scalar(0,0,0));
	imshow("IMG_ORIGINAL", mat_Bg);
	//]
	*/
	
	Mat targetImage(DispRect.Height(), DispRect.Width(), CV_8UC3, Scalar(0,0,0));
	imshow("IMG_ORIGINAL", targetImage);
	
	//[Get display area for current preview window
	targetRect = Img_Scale(DispRect, m_srcImage.cols, m_srcImage.rows);
	dispArea = targetImage(Rect(targetRect.left, targetRect.top, targetRect.Width(), targetRect.Height()));
	//]

	//�N�v���Y�p����ܰϰ줺���j�p
	resize(m_srcImage, dispArea, dispArea.size(), 0.0, 0.0, INTER_LINEAR);
	
	//�e�X�Ϥ�
	//imshow("IMG_ORIGINAL", targetImage);
	imshow(title[0], targetImage);
	
	//cvNamedWindow("IMG_ORIGINAL_SIZE", WINDOW_AUTOSIZE);
	//imshow("IMG_ORIGINAL_SIZE", m_srcImage);

}

void CAlgorithmTestDlg::DispImg(int step, int controlID, Mat srcImg)
{
	Mat dstSize;
	Mat dispArea;
	
	//[ �o�@�q�ΨӨ��oMFC�إߪ�CStatic����j�p�P��m, 
	CRect DispRect, targetRect;
	CWnd *pWnd = GetDlgItem(controlID);

	pWnd->GetWindowRect(&DispRect);
	ScreenToClient(&DispRect); 	

	/*
	//Clear background first
	Mat mat_Bg(DispRect.Height(), DispRect.Width(),  CV_8UC3, Scalar(0,0,0));
	imshow("IMG_ORIGINAL", mat_Bg);
	//]
	*/
	
	//Mat targetImage(DispRect.Height(), DispRect.Width(), CV_8UC3, Scalar(0,0,0));
	Mat targetImage(DispRect.Height(), DispRect.Width(), srcImg.type(), Scalar(0,0,0));
	//imshow(title[step], targetImage);
	
	//[Get display area for current preview window
	targetRect = Img_Scale(DispRect, srcImg.cols, srcImg.rows);
	//targetRect = Img_Scale(DispRect, m_ImgStep1.cols, m_ImgStep1.rows);
	
	dispArea = targetImage(Rect(targetRect.left, targetRect.top, targetRect.Width(), targetRect.Height()));
	//]

	//�N�v���Y�p����ܰϰ줺���j�p
	//resize(srcImg, dispArea, dispArea.size(), 0.0, 0.0, INTER_LINEAR);
	resize(srcImg, dispArea, dispArea.size(), 0.0, 0.0, INTER_LINEAR);
	
	//�e�X�Ϥ�
	imshow(title[step], targetImage);
	//imshow("IMG_STEP1", targetImage);
	
	//cvNamedWindow("IMG_ORIGINAL_SIZE", WINDOW_AUTOSIZE);
	//imshow("IMG_ORIGINAL_SIZE", srcImage);
	
}

CRect CAlgorithmTestDlg ::Img_Scale(CRect DispArea, unsigned int ImgWidth , unsigned int ImgHeight)
{             
	float dScaleX = 0.0;
	float dScaleY = 0.0;
	int iSizeX, iSizeY, iOffsetX, iOffsetY;

	dScaleX = ( float)((float )(DispArea.Width()) / (float)( ImgWidth));
	dScaleY = ( float)((float )(DispArea.Height()) /(float)( ImgHeight));
	              
	if(dScaleX < dScaleY){
		iSizeX = DispArea.Width();
		iSizeY = ImgHeight * dScaleX;
		iOffsetX = 0;
		iOffsetY = (DispArea.Height() - iSizeY)/2;
	}
	else{
		iSizeX = ImgWidth * dScaleY;
		iSizeY = DispArea.Height();
		iOffsetX = (DispArea.Width() - iSizeX)/2;
		iOffsetY = 0;
	}

	DispArea.left = iOffsetX;
	DispArea.top= iOffsetY;
	DispArea.right = iOffsetX + iSizeX;
	DispArea.bottom = iOffsetY + iSizeY;

	return DispArea;
}

void CAlgorithmTestDlg::InitPreviewWindow(unsigned int Step)
{
	HWND hWnd;
	HWND hParent;
	int controlID;

	//Create image display window for OpenCV
	//cvNamedWindow(title[Step], WINDOW_NORMAL);
	cvNamedWindow(title[Step], WINDOW_AUTOSIZE);
	
	switch(Step){
		case 0:	//Original
			//Set original picture
			controlID = IDC_IMG_ORIGINAL;
		break;

		case 1:	//Step1
			controlID = IDC_IMG_STEP1;
			break;

		case 2:	//Step2
			controlID = IDC_IMG_STEP2;
			break;

		case 3:	//Step3
			controlID = IDC_IMG_STEP3;
			break;

		case 4:	//Step4
			controlID = IDC_IMG_STEP4;
			break;

		case 5:	//Step5
			controlID = IDC_IMG_STEP5;
			break;
			
		default:
			break;
	}
	
	//Change parent
	hWnd = (HWND)cvGetWindowHandle(title[Step]);
	hParent = ::GetParent(hWnd);
	
	::SetParent(hWnd, GetDlgItem(controlID)->m_hWnd);
	::ShowWindow(hParent, SW_HIDE);

	//Get window size
	CRect DispRect, targetRect;
	CWnd *pWnd = GetDlgItem(controlID);

	pWnd->GetWindowRect(&DispRect);
	ScreenToClient(&DispRect); 	

	//Clear window background first
	//if(Step != 1){
		Mat mat_Bg(DispRect.Height(), DispRect.Width(),  CV_8UC3, Scalar(0,0,0));
		imshow(title[Step], mat_Bg);
	//}
}

void CAlgorithmTestDlg::LoadImg(unsigned int Step)
{
	HWND hWnd;
	HWND hParent;
	int controlID;
	
	switch(Step){
		case 0:	//Original
			//Set original picture
			cvNamedWindow(title[0], WINDOW_AUTOSIZE);
			controlID = IDC_IMG_ORIGINAL;
			
		break;

		case 1:	//Step1
			cvNamedWindow(title[1], WINDOW_AUTOSIZE);
			controlID = IDC_IMG_STEP1;
			break;
			
		default:
			break;
	}
	
	if (m_srcImage.empty())
		return;
	
	//[ �o�@�q�ΨӨ��oMFC�إߪ�CStatic����j�p�P��m, 
	CRect DispRect, targetRect;
	CWnd *pWnd = GetDlgItem(controlID);

	pWnd->GetWindowRect(&DispRect);
	ScreenToClient(&DispRect); 	

	//Clear background first
	Mat mat_Bg(DispRect.Height(), DispRect.Width(),  CV_8UC3, Scalar(0,0,0));
	imshow("IMG_ORIGINAL", mat_Bg);
	//]
	
	//Adjust display windows size that created by openCV
	cvResizeWindow("IMG_ORIGINAL", DispRect.Width(), DispRect.Height());

	//Mat dstVideoFrame = Mat::zeros(DispRect.Height(), DispRect.Width(),  CV_8UC3);
	Mat dstVideoFrame(DispRect.Height(), DispRect.Width(), CV_8UC3, Scalar(0,0,0));
	

	//[Get display area for current video
	targetRect = Img_Scale(DispRect, m_srcImage.cols, m_srcImage.rows);

	Mat imageROI;
	imageROI = dstVideoFrame(Rect(targetRect.left, targetRect.top, targetRect.Width(), targetRect.Height()));
	//]

	//�N�v���Y�p����ܰϰ줺���j�p
	//resize(videoFrame, imageROI, imageROI.size(), 0.0, 0.0, INTER_AREA);
	resize(m_srcImage, imageROI, imageROI.size(), 0.0, 0.0, INTER_LINEAR);
	
	//�e�X�Ϥ�
	imshow(title[0], m_srcImage);

}

void CAlgorithmTestDlg ::Img_Update(void)
{         
	Img_Process(0);
	Img_Process(1);
	Img_Process(2);
	Img_Process(3);
	Img_Process(4);
	Img_Process(5);
}

void CAlgorithmTestDlg ::Img_Process(unsigned int Step)
{         

	CButton *ptr;
	Size gaussionCore(3, 3);
	
	switch(Step){
		case 0:	//
			m_srcImage = imread("SolarPanel.png");

			if (m_srcImage.empty())
				return;
			
			DispImg(Step, IDC_IMG_ORIGINAL, m_srcImage);
		break;

		case 1:	//equalizeHist
			if (m_Ctrl_Check_Equalizer.GetCheck()){
				//m_ImgStep1 = m_srcImage.clone();
				cvtColor(m_srcImage, m_ImgStep1, COLOR_BGR2GRAY);
				//cvNamedWindow("Gray", WINDOW_AUTOSIZE);
				//imshow("Gray", m_ImgStep1);	
			
				equalizeHist(m_ImgStep1, m_ImgStep1);
				//cvNamedWindow("After equalizeHist", WINDOW_AUTOSIZE);
				//imshow("After equalizeHist", m_ImgStep1);
			}
			else{
				m_ImgStep1 = m_srcImage.clone();
			}
				//cvNamedWindow("STEP1", WINDOW_AUTOSIZE);
				//imshow("STEP1", m_ImgStep1);
				DispImg(Step, IDC_IMG_STEP1, m_ImgStep1);
				
		break;

		case 2:	//Gaussion Blur
			
			//m_ImgStep2 = m_ImgStep1.clone();
			gaussionCore.width = m_coreSize;
			gaussionCore.height= m_coreSize;
			
			GaussianBlur(m_ImgStep1, m_ImgStep2, gaussionCore, 0, 0, BORDER_DEFAULT);
			DispImg(Step, IDC_IMG_STEP2, m_ImgStep2);
			
			//cvNamedWindow("GaussionBlur", WINDOW_AUTOSIZE);
			//imshow("GaussionBlur", m_ImgStep2);
			break;

		case 3:
			m_ImgStep3 = m_ImgStep2.clone();
			DispImg(Step, IDC_IMG_STEP3, m_ImgStep3);
			break;

		case 4:
			m_ImgStep4 = m_ImgStep3.clone();
			DispImg(Step, IDC_IMG_STEP4, m_ImgStep4);
			break;

		case 5:
			m_ImgStep5 = m_ImgStep4.clone();
			DispImg(Step, IDC_IMG_STEP5, m_ImgStep5);
			break;

		default:
			break;
	}


}



void CAlgorithmTestDlg::OnBnClickedOk()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	Img_Update();
	
	//CDialogEx::OnOK();
}

void CAlgorithmTestDlg::OnClickedCheckEqualizer()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	Img_Update();
}

void CAlgorithmTestDlg::OnBnClickedCheck3x3()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	m_CB_3X3.SetCheck(TRUE);
	m_CB_5X5.SetCheck(FALSE);
	m_CB_7X7.SetCheck(FALSE);
	m_coreSize = 3;
	Img_Update();
}

void CAlgorithmTestDlg::OnBnClickedCheck5x5()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	m_CB_3X3.SetCheck(FALSE);
	m_CB_5X5.SetCheck(TRUE);
	m_CB_7X7.SetCheck(FALSE);
	m_coreSize = 5;
	Img_Update();
}

void CAlgorithmTestDlg::OnBnClickedCheck7x7()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	m_CB_3X3.SetCheck(FALSE);
	m_CB_5X5.SetCheck(FALSE);
	m_CB_7X7.SetCheck(TRUE);
	m_coreSize = 7;
	Img_Update();
}

