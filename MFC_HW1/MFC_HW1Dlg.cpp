
// MFC_HW1Dlg.cpp: 實作檔案
//

#include "stdafx.h"
#include "iostream"
#include "stdlib.h"
#include "math.h"
#include "windows.h"
#include "MFC_HW1.h"
#include "MFC_HW1Dlg.h"
#include "afxdialogex.h"
#include "cv.h"
#include "opencv2\highgui\highgui.hpp"
#include "opencv2\imgproc.hpp"
#include "opencv2\opencv.hpp"

using namespace std;
using namespace cv;

int DELAY_CAPTION = 1500;
int DELAY_BLUR = 100;
int MAX_KERNEL_LENGTH = 31;



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 對 App About 使用 CAboutDlg 對話方塊

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

// 程式碼實作
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


// CMFCHW1Dlg 對話方塊



CMFCHW1Dlg::CMFCHW1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC_HW1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCHW1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCHW1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCHW1Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCHW1Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCHW1Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCHW1Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CMFCHW1Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CMFCHW1Dlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CMFCHW1Dlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CMFCHW1Dlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CMFCHW1Dlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CMFCHW1Dlg::OnBnClickedButton10)
END_MESSAGE_MAP()


// CMFCHW1Dlg 訊息處理常式

BOOL CMFCHW1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 將 [關於...] 功能表加入系統功能表。

	// IDM_ABOUTBOX 必須在系統命令範圍之中。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 設定此對話方塊的圖示。當應用程式的主視窗不是對話方塊時，
	// 框架會自動從事此作業
	SetIcon(m_hIcon, TRUE);			// 設定大圖示
	SetIcon(m_hIcon, FALSE);		// 設定小圖示

	// TODO: 在此加入額外的初始設定
	AllocConsole();
	freopen("CONOUT$", "w", stdout);

	CComboBox* pCB = (CComboBox*)GetDlgItem(IDC_COMBO1);
	CString str;
	for (int i = 1; i < 16; i++)
	{
		str.Format(_T("%d.bmp"), i);
		pCB->AddString(str);
	}

	return TRUE;  // 傳回 TRUE，除非您對控制項設定焦點
}

void CMFCHW1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果將最小化按鈕加入您的對話方塊，您需要下列的程式碼，
// 以便繪製圖示。對於使用文件/檢視模式的 MFC 應用程式，
// 框架會自動完成此作業。

void CMFCHW1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 繪製的裝置內容

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 將圖示置中於用戶端矩形
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 描繪圖示
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 當使用者拖曳最小化視窗時，
// 系統呼叫這個功能取得游標顯示。
HCURSOR CMFCHW1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCHW1Dlg::OnBnClickedButton1()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	
	Mat src = imread("plant.jpg",IMREAD_GRAYSCALE);
	int histSize = 256;
	float range[] = { 0, 255 };
	const float* histRange = { range };
	Mat histImg;
	calcHist(&src, 1, 0, Mat(), histImg, 1, &histSize, &histRange);

	Mat showHistImg(256, 256, CV_8UC3, Scalar(255,255,255));  //把直方圖秀在一個256*256大的影像上
	drawHistImg(histImg, showHistImg);
	
	imshow("1.1 Origin", src);
	imshow("1.1 Histogram", showHistImg);
	waitKey(0);
	cvDestroyWindow("1.1 Origin");
	cvDestroyWindow("1.1 Histogram");
	
}

void CMFCHW1Dlg::OnBnClickedButton2()
{
	// TODO: 在此加入控制項告知處理常式程式碼

	Mat src = imread("plant.jpg", IMREAD_GRAYSCALE);
	Mat dst;
	equalizeHist(src, dst);

	int histSize = 256;
	float range[] = { 0, 255 };
	const float* histRange = { range };
	Mat histImg;
	calcHist(&dst, 1, 0, Mat(), histImg, 1, &histSize, &histRange);

	Mat showHistImg(256, 256, CV_8UC3, Scalar(255, 255, 255));  //把直方圖秀在一個256*256大的影像上
	drawHistImg(histImg, showHistImg);

	imshow("1.2 Origin", dst);
	imshow("1.2 Histogram", showHistImg);
	waitKey(0);
	cvDestroyWindow("1.2 Origin");
	cvDestroyWindow("1.2 Histogram");
}

void CMFCHW1Dlg::OnBnClickedButton3()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	Mat img = imread("q2_train.jpg");
	Mat result = imread("q2_train.jpg", CV_LOAD_IMAGE_COLOR);

	vector<Vec3f> circles;
	calcCircles(img, circles);
	drawCircle(result, circles);

	
	imshow("2.1 Input", img);
	imshow("2.1 Output", result);
	waitKey(0);
	cvDestroyWindow("2.1 Input");
	cvDestroyWindow("2.1 Output");
}

void CMFCHW1Dlg::OnBnClickedButton4()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	Mat src = imread("q2_train.jpg");
	Mat hsv;
	Mat hue;
	int histSize = 180;
	float range[] = { 0, 179 };
	const float* histRange = { range };

	Mat img = imread("q2_train.jpg");
	Mat result = Mat::zeros(img.size(),img.type());

	vector<Vec3f> circles;
	calcCircles(img, circles);
	

	for (int i = 0; i<circles.size(); i++) {
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		//circle(result, center, 1, Scalar(0, 0, 255), 3, 8, 0);
		circle(result, center, radius, Scalar(1, 1, 1), CV_FILLED, 8, 0);
	}

	bitwise_and(img, result, result);
	Mat dst = Mat::zeros(img.size(), img.type());
	img.copyTo(dst, result);
	
	cvtColor(dst, hsv, COLOR_BGR2HSV);
	
	int ch[] = { 0,0 };
	hue.create(hsv.size(), hsv.depth());
	mixChannels(&hsv, 1, &hue, 1,ch, 1);
	 
	//MatND histImg;
	Mat histImg;
	calcHist(&hue, 1,0, Mat(), histImg, 1, &histSize, &histRange);
	Mat showHistImg(256, 180, CV_8UC3, Scalar(255, 255, 255));  //把直方圖秀在一個256*256大的影像上
//	normalize(histImg, histImg, 1, 0, CV_MINMAX);

	float histMaxValue = 0;
	for (int i = 90; i<130; i++) {
		float tempValue = histImg.at<float>(i);
		if (histMaxValue < tempValue) {
			histMaxValue = tempValue;
		}
	}

	float scale =0.9* 256/histMaxValue;
	for (int i = 90; i<130; i++) {
		int intensity = static_cast<int>(histImg.at<float>(i)*scale);
		line(showHistImg, Point(i, 255), Point(i, 255 - intensity), Scalar(0, 0, 255));
	}

	/*

	normalize(histImg, histImg, 0, 255, CV_MINMAX);

	Mat histimg = Mat::zeros(200, 640, CV_8UC3);
	histimg = Scalar::all(255);
	int binW = histimg.cols / 180;
	Mat buf(1, 180, CV_8UC3);
	//Set RGB color
	for (int i = 0; i < 180; i++)
		buf.at< Vec3b>(i) = Vec3b(saturate_cast<uchar>(i*180. / 180), 255, 255);
	cvtColor(buf, buf, CV_HSV2BGR);
	//drawing routine
	for (int i = 30; i <180; i++)
	{
		int val = saturate_cast<int>(histImg.at< float>(i)*histimg.rows / 255);

		rectangle(histimg, Point(i*binW, histimg.rows),
			Point((i + 1)*binW, histimg.rows - val),
			Scalar(buf.at< Vec3b>(i)), -1, 8);
		int r, g, b;
		b = buf.at< Vec3b>(i)[0];
		g = buf.at< Vec3b>(i)[1];
		r = buf.at< Vec3b>(i)[2];

		//show bin and RGB value
		//printf("[%d] r=%d, g=%d, b=%d , bins = %d \n", i, r, g, b, val);
	}
	*/
	
	//imshow("2.2 Origin", hsv);
//	imshow("2.2 Histogram", showHistImg);
	imshow("2.2 Histogram", showHistImg);
	waitKey(0);
	//cvDestroyWindow("2.2 Origin");
	cvDestroyWindow("2.2 Histogram");


}

void CMFCHW1Dlg::OnBnClickedButton5()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	Mat img = imread("q2_test.jpg");
//	Mat result = imread("q2_test.jpg", CV_LOAD_IMAGE_COLOR);

	vector<Vec3f> circles;
	calcCircles2(img, circles);
//	drawCircle(result, circles);

//	Mat hue;
	int h_histSize = 180; int s_histSize = 256;
	int histSize[] = { h_histSize, s_histSize };
	float h_range[] = { 103, 121 };
	float s_range[] = { 0, 256};
	const float* histRange[] = { h_range, s_range };


	
	Mat result = Mat::zeros(img.size(), img.type());

	
	for (int i = 0; i<circles.size(); i++) {
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		//circle(result, center, 1, Scalar(0, 0, 255), 3, 8, 0);
		circle(result, center, radius, Scalar(1, 1, 1), CV_FILLED, 8, 0);
	}

	bitwise_and(img, result, result);
	Mat dst = Mat::zeros(img.size(), img.type());
	img.copyTo(dst, result);
	
	Mat hsv;
	cvtColor(dst, hsv, COLOR_BGR2HSV);

	int ch[] = { 0,1 };
//	hue.create(hsv.size(), hsv.depth());
//	mixChannels(&hsv, 1, &hue, 1, ch, 1);

	MatND histImg;
	
	calcHist(&hsv, 1, ch, Mat(), histImg, 2, histSize, histRange,true,false);

	normalize(histImg, histImg, 0, 255, NORM_MINMAX, -1, Mat());

	Mat backproj;
	calcBackProject(&hsv, 1, ch, histImg, backproj, histRange, 1, true);

	

	Mat after;
	threshold(backproj, after, 0, 255, THRESH_BINARY);


	imshow("2.1 Input", img);
	imshow("2.1 Output", after);
	waitKey(0);
	cvDestroyWindow("2.1 Input");
	cvDestroyWindow("2.1 Output");
}

void CMFCHW1Dlg::OnBnClickedButton6()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	Mat img1 = imread("./CameraCalibration/1.bmp",IMREAD_COLOR);
	Mat img2 = imread("./CameraCalibration/2.bmp", IMREAD_COLOR);
	Mat img3 = imread("./CameraCalibration/3.bmp", IMREAD_COLOR);
	Mat img4 = imread("./CameraCalibration/4.bmp", IMREAD_COLOR);
	Mat img5 = imread("./CameraCalibration/5.bmp", IMREAD_COLOR);
	Mat img6 = imread("./CameraCalibration/6.bmp", IMREAD_COLOR);
	Mat img7 = imread("./CameraCalibration/7.bmp", IMREAD_COLOR);
	Mat img8 = imread("./CameraCalibration/8.bmp", IMREAD_COLOR);
	Mat img9 = imread("./CameraCalibration/9.bmp", IMREAD_COLOR);
	Mat img10 = imread("./CameraCalibration/10.bmp", IMREAD_COLOR);
	Mat img11 = imread("./CameraCalibration/11.bmp", IMREAD_COLOR);
	Mat img12 = imread("./CameraCalibration/12.bmp", IMREAD_COLOR);
	Mat img13 = imread("./CameraCalibration/13.bmp", IMREAD_COLOR);
	Mat img14 = imread("./CameraCalibration/14.bmp", IMREAD_COLOR);
	Mat img15 = imread("./CameraCalibration/15.bmp", IMREAD_COLOR);
	
	Mat img_gray;
	bool ret;
	vector<cv::Point2f> corners;
	TermCriteria criteria;

	cvtColor(img1, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray,cv::Size(11, 8),corners,CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS,40,0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);
	
	cv::drawChessboardCorners(img1, cv::Size(11, 8), corners, ret);
	
	cvtColor(img2, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);
	
	cv::drawChessboardCorners(img2, cv::Size(11, 8), corners, ret);
	
	cvtColor(img3, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

	cv::drawChessboardCorners(img3, cv::Size(11, 8), corners, ret);
	
	cvtColor(img4, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, 0);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);
	
	cv::drawChessboardCorners(img4, cv::Size(11, 8), corners, ret);
	
	cvtColor(img5, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

	cv::drawChessboardCorners(img5, cv::Size(11, 8), corners, ret);

	cvtColor(img6, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

	cv::drawChessboardCorners(img6, cv::Size(11, 8), corners, ret);

	cvtColor(img7, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

	cv::drawChessboardCorners(img7, cv::Size(11, 8), corners, ret);

	cvtColor(img8, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

	cv::drawChessboardCorners(img8, cv::Size(11, 8), corners, ret);

	cvtColor(img9, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

	cv::drawChessboardCorners(img9, cv::Size(11, 8), corners, ret);

	cvtColor(img10, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

	cv::drawChessboardCorners(img10, cv::Size(11, 8), corners, ret);

	cvtColor(img11, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

	cv::drawChessboardCorners(img11, cv::Size(11, 8), corners, ret);

	cvtColor(img12, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

	cv::drawChessboardCorners(img12, cv::Size(11, 8), corners, ret);

	cvtColor(img13, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

	cv::drawChessboardCorners(img13, cv::Size(11, 8), corners, ret);

	cvtColor(img14, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

	cv::drawChessboardCorners(img14, cv::Size(11, 8), corners, ret);

	cvtColor(img15, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

	cv::drawChessboardCorners(img15, cv::Size(11, 8), corners, ret);
	
	cvNamedWindow("3.1 img1", 0);
	cvResizeWindow("3.1 img1", 500, 500);
	imshow("3.1 img1",img1);
	waitKey(0);
	cvDestroyWindow("3.1 img1");
	cvNamedWindow("3.1 img2", 0);
	cvResizeWindow("3.1 img2", 500, 500);
	imshow("3.1 img2", img2);
	waitKey(0);
	cvDestroyWindow("3.1 img2");
	cvNamedWindow("3.1 img3", 0);
	cvResizeWindow("3.1 img3", 500, 500);
	imshow("3.1 img3", img3);
	waitKey(0);
	cvDestroyWindow("3.1 img3");
	cvNamedWindow("3.1 img4", 0);
	cvResizeWindow("3.1 img4", 500, 500);
	imshow("3.1 img4", img4);
	waitKey(0);
	cvDestroyWindow("3.1 img4");
	cvNamedWindow("3.1 img5", 0);
	cvResizeWindow("3.1 img5", 500, 500);
	imshow("3.1 img5", img5);
	waitKey(0);
	cvDestroyWindow("3.1 img5");
	cvNamedWindow("3.1 img6", 0);
	cvResizeWindow("3.1 img6", 500, 500);
	imshow("3.1 img6", img6);
	waitKey(0);
	cvDestroyWindow("3.1 img6");
	cvNamedWindow("3.1 img7", 0);
	cvResizeWindow("3.1 img7", 500, 500);
	imshow("3.1 img7", img7);
	waitKey(0);
	cvDestroyWindow("3.1 img7");
	cvNamedWindow("3.1 img8", 0);
	cvResizeWindow("3.1 img8", 500, 500);
	imshow("3.1 img8", img8);
	waitKey(0);
	cvDestroyWindow("3.1 img8");
	cvNamedWindow("3.1 img9", 0);
	cvResizeWindow("3.1 img9", 500, 500);
	imshow("3.1 img9", img9);
	waitKey(0);
	cvDestroyWindow("3.1 img9");
	cvNamedWindow("3.1 img10", 0);
	cvResizeWindow("3.1 img10", 500, 500);
	imshow("3.1 img10", img10);
	waitKey(0);
	cvDestroyWindow("3.1 img10");
	cvNamedWindow("3.1 img11", 0);
	cvResizeWindow("3.1 img11", 500, 500);
	imshow("3.1 img11", img11);
	waitKey(0);
	cvDestroyWindow("3.1 img11");
	cvNamedWindow("3.1 img12", 0);
	cvResizeWindow("3.1 img12", 500, 500);
	imshow("3.1 img12", img12);
	waitKey(0);
	cvDestroyWindow("3.1 img12");
	cvNamedWindow("3.1 img13", 0);
	cvResizeWindow("3.1 img13", 500, 500);
	imshow("3.1 img13", img13);
	waitKey(0);
	cvDestroyWindow("3.1 img13");
	cvNamedWindow("3.1 img14", 0);
	cvResizeWindow("3.1 img14", 500, 500);
	imshow("3.1 img14", img14);
	waitKey(0);
	cvDestroyWindow("3.1 img14");
	cvNamedWindow("3.1 img15", 0);
	cvResizeWindow("3.1 img15", 500, 500);
	imshow("3.1 img15", img15);
	waitKey(0);
	cvDestroyWindow("3.1 img15");

	
	
	
	
	
	
	
	
	
	
	
	
	
	


	

}

void CMFCHW1Dlg::OnBnClickedButton7()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	Mat img1 = imread("./CameraCalibration/1.bmp", IMREAD_COLOR);
	Mat img2 = imread("./CameraCalibration/2.bmp", IMREAD_COLOR);
	Mat img3 = imread("./CameraCalibration/3.bmp", IMREAD_COLOR);
	Mat img4 = imread("./CameraCalibration/4.bmp", IMREAD_COLOR);
	Mat img5 = imread("./CameraCalibration/5.bmp", IMREAD_COLOR);
	Mat img6 = imread("./CameraCalibration/6.bmp", IMREAD_COLOR);
	Mat img7 = imread("./CameraCalibration/7.bmp", IMREAD_COLOR);
	Mat img8 = imread("./CameraCalibration/8.bmp", IMREAD_COLOR);
	Mat img9 = imread("./CameraCalibration/9.bmp", IMREAD_COLOR);
	Mat img10 = imread("./CameraCalibration/10.bmp", IMREAD_COLOR);
	Mat img11 = imread("./CameraCalibration/11.bmp", IMREAD_COLOR);
	Mat img12 = imread("./CameraCalibration/12.bmp", IMREAD_COLOR);
	Mat img13 = imread("./CameraCalibration/13.bmp", IMREAD_COLOR);
	Mat img14 = imread("./CameraCalibration/14.bmp", IMREAD_COLOR);
	Mat img15 = imread("./CameraCalibration/15.bmp", IMREAD_COLOR);

	Mat img_gray;
	bool ret;
	vector<cv::Point2f> corners;
	vector<cv::Point3f> dstcorners;
	vector<vector<Point2f> > m_srcPoints;
	vector<vector<Point3f> > m_dstPoints;
	TermCriteria criteria;


	for (int i = 0; i<8; i++) {
		for (int j = 0; j<11; j++) {
			dstcorners.push_back(Point3f(i, j, 0.0f));
		}
	}

	cvtColor(img1, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

	cv::drawChessboardCorners(img1, cv::Size(11, 8), corners, ret);
	if (corners.size() == 88) {
		m_srcPoints.push_back(corners);
		m_dstPoints.push_back(dstcorners);
	}
	////

	cvtColor(img2, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

	cv::drawChessboardCorners(img2, cv::Size(11, 8), corners, ret);

	if (corners.size() == 88) {
		m_srcPoints.push_back(corners);
		m_dstPoints.push_back(dstcorners);
	}
	//////

	cvtColor(img3, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

	cv::drawChessboardCorners(img3, cv::Size(11, 8), corners, ret);

	if (corners.size() == 88) {
		m_srcPoints.push_back(corners);
		m_dstPoints.push_back(dstcorners);
	}
	/////

	cvtColor(img4, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, 0);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

	cv::drawChessboardCorners(img4, cv::Size(11, 8), corners, ret);

	if (corners.size() == 88) {
		m_srcPoints.push_back(corners);
		m_dstPoints.push_back(dstcorners);
	}
	////////

	cvtColor(img5, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

	cv::drawChessboardCorners(img5, cv::Size(11, 8), corners, ret);

	if (corners.size() == 88) {
		m_srcPoints.push_back(corners);
		m_dstPoints.push_back(dstcorners);
	}
	////////

	cvtColor(img6, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

	cv::drawChessboardCorners(img6, cv::Size(11, 8), corners, ret);

	if (corners.size() == 88) {
		m_srcPoints.push_back(corners);
		m_dstPoints.push_back(dstcorners);
	}
	/////////

	cvtColor(img7, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

	cv::drawChessboardCorners(img7, cv::Size(11, 8), corners, ret);

	if (corners.size() == 88) {
		m_srcPoints.push_back(corners);
		m_dstPoints.push_back(dstcorners);
	}
	/////////

	cvtColor(img8, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

	cv::drawChessboardCorners(img8, cv::Size(11, 8), corners, ret);

	if (corners.size() == 88) {
		m_srcPoints.push_back(corners);
		m_dstPoints.push_back(dstcorners);
	}
	/////////

	cvtColor(img9, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

	cv::drawChessboardCorners(img9, cv::Size(11, 8), corners, ret);

	if (corners.size() == 88) {
		m_srcPoints.push_back(corners);
		m_dstPoints.push_back(dstcorners);
	}
	///////

	cvtColor(img10, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

	cv::drawChessboardCorners(img10, cv::Size(11, 8), corners, ret);

	if (corners.size() == 88) {
		m_srcPoints.push_back(corners);
		m_dstPoints.push_back(dstcorners);
	}
	////////

	cvtColor(img11, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

	cv::drawChessboardCorners(img11, cv::Size(11, 8), corners, ret);

	if (corners.size() == 88) {
		m_srcPoints.push_back(corners);
		m_dstPoints.push_back(dstcorners);
	}
	//////////

	cvtColor(img12, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

	cv::drawChessboardCorners(img12, cv::Size(11, 8), corners, ret);

	if (corners.size() == 88) {
		m_srcPoints.push_back(corners);
		m_dstPoints.push_back(dstcorners);
	}
	/////////

	cvtColor(img13, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

	cv::drawChessboardCorners(img13, cv::Size(11, 8), corners, ret);

	if (corners.size() == 88) {
		m_srcPoints.push_back(corners);
		m_dstPoints.push_back(dstcorners);
	}
	////////

	cvtColor(img14, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

	cv::drawChessboardCorners(img14, cv::Size(11, 8), corners, ret);

	if (corners.size() == 88) {
		m_srcPoints.push_back(corners);
		m_dstPoints.push_back(dstcorners);
	}
	////////

	cvtColor(img15, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

	cv::drawChessboardCorners(img15, cv::Size(11, 8), corners, ret);

	if (corners.size() == 88) {
		m_srcPoints.push_back(corners);
		m_dstPoints.push_back(dstcorners);
	}
	////////

	Mat intrinsic_matrix, distortion_matrix;
	vector<Mat> rvecs, tvecs;
	Size imageSize = img1.size();
	calibrateCamera(m_dstPoints, m_srcPoints, imageSize, intrinsic_matrix, distortion_matrix, rvecs, tvecs);
	cout << intrinsic_matrix << endl;

}

void CMFCHW1Dlg::OnBnClickedButton8()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	int index;
	CString strTemp,dir;
	dir = "./CameraCalibration/";

	index = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();
	((CComboBox*)GetDlgItem(IDC_COMBO1))->GetLBText(index,strTemp);

	strTemp = dir + strTemp;

	Mat img1 = imread("./CameraCalibration/1.bmp", IMREAD_COLOR);
	Mat img2 = imread("./CameraCalibration/2.bmp", IMREAD_COLOR);
	Mat img3 = imread("./CameraCalibration/3.bmp", IMREAD_COLOR);
	Mat img4 = imread("./CameraCalibration/4.bmp", IMREAD_COLOR);
	Mat img5 = imread("./CameraCalibration/5.bmp", IMREAD_COLOR);
	Mat img6 = imread("./CameraCalibration/6.bmp", IMREAD_COLOR);
	Mat img7 = imread("./CameraCalibration/7.bmp", IMREAD_COLOR);
	Mat img8 = imread("./CameraCalibration/8.bmp", IMREAD_COLOR);
	Mat img9 = imread("./CameraCalibration/9.bmp", IMREAD_COLOR);
	Mat img10 = imread("./CameraCalibration/10.bmp", IMREAD_COLOR);
	Mat img11 = imread("./CameraCalibration/11.bmp", IMREAD_COLOR);
	Mat img12 = imread("./CameraCalibration/12.bmp", IMREAD_COLOR);
	Mat img13 = imread("./CameraCalibration/13.bmp", IMREAD_COLOR);
	Mat img14 = imread("./CameraCalibration/14.bmp", IMREAD_COLOR);
	Mat img15 = imread("./CameraCalibration/15.bmp", IMREAD_COLOR);

	Mat img_gray;
	bool ret;
	vector<cv::Point2f> corners;
	vector<cv::Point3f> dstcorners;
	vector<vector<Point2f> > m_srcPoints;
	vector<vector<Point3f> > m_dstPoints;
	TermCriteria criteria;


	for (int i = 0; i<8; i++) {
		for (int j = 0; j<11; j++) {
			dstcorners.push_back(Point3f(i, j, 0.0f));
		}
	}

	cvtColor(img1, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

	cv::drawChessboardCorners(img1, cv::Size(11, 8), corners, ret);
	if (corners.size() == 88) {
		m_srcPoints.push_back(corners);
		m_dstPoints.push_back(dstcorners);
	}
	////

	cvtColor(img2, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

	cv::drawChessboardCorners(img2, cv::Size(11, 8), corners, ret);

	if (corners.size() == 88) {
		m_srcPoints.push_back(corners);
		m_dstPoints.push_back(dstcorners);
	}
	//////

	cvtColor(img3, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

	cv::drawChessboardCorners(img3, cv::Size(11, 8), corners, ret);

	if (corners.size() == 88) {
		m_srcPoints.push_back(corners);
		m_dstPoints.push_back(dstcorners);
	}
	/////

	cvtColor(img4, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, 0);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

	cv::drawChessboardCorners(img4, cv::Size(11, 8), corners, ret);

	if (corners.size() == 88) {
		m_srcPoints.push_back(corners);
		m_dstPoints.push_back(dstcorners);
	}
	////////

	cvtColor(img5, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

	cv::drawChessboardCorners(img5, cv::Size(11, 8), corners, ret);

	if (corners.size() == 88) {
		m_srcPoints.push_back(corners);
		m_dstPoints.push_back(dstcorners);
	}
	////////

	cvtColor(img6, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

	cv::drawChessboardCorners(img6, cv::Size(11, 8), corners, ret);

	if (corners.size() == 88) {
		m_srcPoints.push_back(corners);
		m_dstPoints.push_back(dstcorners);
	}
	/////////

	cvtColor(img7, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

	cv::drawChessboardCorners(img7, cv::Size(11, 8), corners, ret);

	if (corners.size() == 88) {
		m_srcPoints.push_back(corners);
		m_dstPoints.push_back(dstcorners);
	}
	/////////

	cvtColor(img8, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

	cv::drawChessboardCorners(img8, cv::Size(11, 8), corners, ret);

	if (corners.size() == 88) {
		m_srcPoints.push_back(corners);
		m_dstPoints.push_back(dstcorners);
	}
	/////////

	cvtColor(img9, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

	cv::drawChessboardCorners(img9, cv::Size(11, 8), corners, ret);

	if (corners.size() == 88) {
		m_srcPoints.push_back(corners);
		m_dstPoints.push_back(dstcorners);
	}
	///////

	cvtColor(img10, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

	cv::drawChessboardCorners(img10, cv::Size(11, 8), corners, ret);

	if (corners.size() == 88) {
		m_srcPoints.push_back(corners);
		m_dstPoints.push_back(dstcorners);
	}
	////////

	cvtColor(img11, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

	cv::drawChessboardCorners(img11, cv::Size(11, 8), corners, ret);

	if (corners.size() == 88) {
		m_srcPoints.push_back(corners);
		m_dstPoints.push_back(dstcorners);
	}
	//////////

	cvtColor(img12, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

	cv::drawChessboardCorners(img12, cv::Size(11, 8), corners, ret);

	if (corners.size() == 88) {
		m_srcPoints.push_back(corners);
		m_dstPoints.push_back(dstcorners);
	}
	/////////

	cvtColor(img13, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

	cv::drawChessboardCorners(img13, cv::Size(11, 8), corners, ret);

	if (corners.size() == 88) {
		m_srcPoints.push_back(corners);
		m_dstPoints.push_back(dstcorners);
	}
	////////

	cvtColor(img14, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

	cv::drawChessboardCorners(img14, cv::Size(11, 8), corners, ret);

	if (corners.size() == 88) {
		m_srcPoints.push_back(corners);
		m_dstPoints.push_back(dstcorners);
	}
	////////

	cvtColor(img15, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

	cv::drawChessboardCorners(img15, cv::Size(11, 8), corners, ret);

	if (corners.size() == 88) {
		m_srcPoints.push_back(corners);
		m_dstPoints.push_back(dstcorners);
	}
	////////

	Mat intrinsic_matrix, distortion_matrix;
	Mat rotation_matrix,extrinsic_matrix,translation_matrix;
	vector<Mat> rvecs, tvecs;
	Size imageSize = img1.size();
	extrinsic_matrix = Mat(3, 4, CV_8UC3);
	rotation_matrix = Mat(3, 3,CV_8UC3);
	translation_matrix = Mat(3, 1, CV_8UC3);

	
	calibrateCamera(m_dstPoints, m_srcPoints, imageSize, intrinsic_matrix, distortion_matrix, rvecs, tvecs);
	Rodrigues(rvecs[index], rotation_matrix);
	hconcat(rotation_matrix,tvecs[index],extrinsic_matrix);
	cout << extrinsic_matrix << endl;

	
	
	/*
	for (int idx = 0; idx < 3; idx++) {
		for (int jdx = 0; jdx < 3; jdx++) {
			extrinsic_matrix.at<double>(idx, jdx) = rotation_side.at<double>(idx, jdx);
		}
	}
	for (int idx = 0; idx<3; idx++)
		translation_matrix.at<double>(idx) = tvecs[0][idx];
	for (int idx = 0; idx<3; idx++)
		extrinsic_matrix.at<double>(idx, 3) = translation_matrix.at<double>(idx);

	cout << extrinsic_matrix << endl;
	*/
}


void CMFCHW1Dlg::OnBnClickedButton9()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	Mat img1 = imread("./CameraCalibration/1.bmp", IMREAD_COLOR);
	Mat img2 = imread("./CameraCalibration/2.bmp", IMREAD_COLOR);
	Mat img3 = imread("./CameraCalibration/3.bmp", IMREAD_COLOR);
	Mat img4 = imread("./CameraCalibration/4.bmp", IMREAD_COLOR);
	Mat img5 = imread("./CameraCalibration/5.bmp", IMREAD_COLOR);
	Mat img6 = imread("./CameraCalibration/6.bmp", IMREAD_COLOR);
	Mat img7 = imread("./CameraCalibration/7.bmp", IMREAD_COLOR);
	Mat img8 = imread("./CameraCalibration/8.bmp", IMREAD_COLOR);
	Mat img9 = imread("./CameraCalibration/9.bmp", IMREAD_COLOR);
	Mat img10 = imread("./CameraCalibration/10.bmp", IMREAD_COLOR);
	Mat img11 = imread("./CameraCalibration/11.bmp", IMREAD_COLOR);
	Mat img12 = imread("./CameraCalibration/12.bmp", IMREAD_COLOR);
	Mat img13 = imread("./CameraCalibration/13.bmp", IMREAD_COLOR);
	Mat img14 = imread("./CameraCalibration/14.bmp", IMREAD_COLOR);
	Mat img15 = imread("./CameraCalibration/15.bmp", IMREAD_COLOR);

	Mat img_gray;
	bool ret;
	vector<cv::Point2f> corners;
	vector<cv::Point3f> dstcorners;
	vector<vector<Point2f> > m_srcPoints;
	vector<vector<Point3f> > m_dstPoints;
	TermCriteria criteria;


	for (int i = 0; i<8; i++) {
		for (int j = 0; j<11; j++) {
			dstcorners.push_back(Point3f(i, j, 0.0f));
		}
	}

	cvtColor(img1, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

	cv::drawChessboardCorners(img1, cv::Size(11, 8), corners, ret);
	if (corners.size() == 88) {
		m_srcPoints.push_back(corners);
		m_dstPoints.push_back(dstcorners);
	}
	////

	cvtColor(img2, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

	cv::drawChessboardCorners(img2, cv::Size(11, 8), corners, ret);

	if (corners.size() == 88) {
		m_srcPoints.push_back(corners);
		m_dstPoints.push_back(dstcorners);
	}
	//////

	cvtColor(img3, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

	cv::drawChessboardCorners(img3, cv::Size(11, 8), corners, ret);

	if (corners.size() == 88) {
		m_srcPoints.push_back(corners);
		m_dstPoints.push_back(dstcorners);
	}
	/////

	cvtColor(img4, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, 0);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

	cv::drawChessboardCorners(img4, cv::Size(11, 8), corners, ret);

	if (corners.size() == 88) {
		m_srcPoints.push_back(corners);
		m_dstPoints.push_back(dstcorners);
	}
	////////

	cvtColor(img5, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

	cv::drawChessboardCorners(img5, cv::Size(11, 8), corners, ret);

	if (corners.size() == 88) {
		m_srcPoints.push_back(corners);
		m_dstPoints.push_back(dstcorners);
	}
	////////

	cvtColor(img6, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

	cv::drawChessboardCorners(img6, cv::Size(11, 8), corners, ret);

	if (corners.size() == 88) {
		m_srcPoints.push_back(corners);
		m_dstPoints.push_back(dstcorners);
	}
	/////////

	cvtColor(img7, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

	cv::drawChessboardCorners(img7, cv::Size(11, 8), corners, ret);

	if (corners.size() == 88) {
		m_srcPoints.push_back(corners);
		m_dstPoints.push_back(dstcorners);
	}
	/////////

	cvtColor(img8, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

	cv::drawChessboardCorners(img8, cv::Size(11, 8), corners, ret);

	if (corners.size() == 88) {
		m_srcPoints.push_back(corners);
		m_dstPoints.push_back(dstcorners);
	}
	/////////

	cvtColor(img9, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

	cv::drawChessboardCorners(img9, cv::Size(11, 8), corners, ret);

	if (corners.size() == 88) {
		m_srcPoints.push_back(corners);
		m_dstPoints.push_back(dstcorners);
	}
	///////

	cvtColor(img10, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

	cv::drawChessboardCorners(img10, cv::Size(11, 8), corners, ret);

	if (corners.size() == 88) {
		m_srcPoints.push_back(corners);
		m_dstPoints.push_back(dstcorners);
	}
	////////

	cvtColor(img11, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

	cv::drawChessboardCorners(img11, cv::Size(11, 8), corners, ret);

	if (corners.size() == 88) {
		m_srcPoints.push_back(corners);
		m_dstPoints.push_back(dstcorners);
	}
	//////////

	cvtColor(img12, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

	cv::drawChessboardCorners(img12, cv::Size(11, 8), corners, ret);

	if (corners.size() == 88) {
		m_srcPoints.push_back(corners);
		m_dstPoints.push_back(dstcorners);
	}
	/////////

	cvtColor(img13, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

	cv::drawChessboardCorners(img13, cv::Size(11, 8), corners, ret);

	if (corners.size() == 88) {
		m_srcPoints.push_back(corners);
		m_dstPoints.push_back(dstcorners);
	}
	////////

	cvtColor(img14, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

	cv::drawChessboardCorners(img14, cv::Size(11, 8), corners, ret);

	if (corners.size() == 88) {
		m_srcPoints.push_back(corners);
		m_dstPoints.push_back(dstcorners);
	}
	////////

	cvtColor(img15, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

	cv::drawChessboardCorners(img15, cv::Size(11, 8), corners, ret);

	if (corners.size() == 88) {
		m_srcPoints.push_back(corners);
		m_dstPoints.push_back(dstcorners);
	}
	////////

	Mat intrinsic_matrix, distortion_matrix;
	vector<Mat> rvecs, tvecs;
	Size imageSize = img1.size();
	calibrateCamera(m_dstPoints, m_srcPoints, imageSize, intrinsic_matrix, distortion_matrix, rvecs, tvecs);
	cout << distortion_matrix << endl;


}

void CMFCHW1Dlg::OnBnClickedButton10()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	Mat img1 = imread("./CameraCalibration/1.bmp", IMREAD_COLOR);
	Mat img2 = imread("./CameraCalibration/2.bmp", IMREAD_COLOR);
	Mat img3 = imread("./CameraCalibration/3.bmp", IMREAD_COLOR);
	Mat img4 = imread("./CameraCalibration/4.bmp", IMREAD_COLOR);
	Mat img5 = imread("./CameraCalibration/5.bmp", IMREAD_COLOR);
	Mat img6 = imread("./CameraCalibration/6.bmp", IMREAD_COLOR);
	Mat img7 = imread("./CameraCalibration/7.bmp", IMREAD_COLOR);
	Mat img8 = imread("./CameraCalibration/8.bmp", IMREAD_COLOR);
	Mat img9 = imread("./CameraCalibration/9.bmp", IMREAD_COLOR);
	Mat img10 = imread("./CameraCalibration/10.bmp", IMREAD_COLOR);
	Mat img11 = imread("./CameraCalibration/11.bmp", IMREAD_COLOR);
	Mat img12 = imread("./CameraCalibration/12.bmp", IMREAD_COLOR);
	Mat img13 = imread("./CameraCalibration/13.bmp", IMREAD_COLOR);
	Mat img14 = imread("./CameraCalibration/14.bmp", IMREAD_COLOR);
	Mat img15 = imread("./CameraCalibration/15.bmp", IMREAD_COLOR);

	Mat img_gray;
	bool ret;
	vector<cv::Point2f> corners;
	vector<cv::Point3f> dstcorners;
	vector<vector<Point2f> > m_srcPoints;
	vector<vector<Point3f> > m_dstPoints;
	TermCriteria criteria;


	for (int i = 0; i<8; i++) {
		for (int j = 0; j<11; j++) {
			dstcorners.push_back(Point3f(i, j, 0.0f));
		}
	}

	cvtColor(img1, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

	//cv::drawChessboardCorners(img1, cv::Size(11, 8), corners, ret);
	if (corners.size() == 88) {
		m_srcPoints.push_back(corners);
		m_dstPoints.push_back(dstcorners);
	}
	////

	cvtColor(img2, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

//	cv::drawChessboardCorners(img2, cv::Size(11, 8), corners, ret);

	if (corners.size() == 88) {
		m_srcPoints.push_back(corners);
		m_dstPoints.push_back(dstcorners);
	}
	//////

	cvtColor(img3, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

//	cv::drawChessboardCorners(img3, cv::Size(11, 8), corners, ret);

	if (corners.size() == 88) {
		m_srcPoints.push_back(corners);
		m_dstPoints.push_back(dstcorners);
	}
	/////

	cvtColor(img4, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners,0);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

//	cv::drawChessboardCorners(img4, cv::Size(11, 8), corners, ret);

	if (corners.size() == 88) {
		m_srcPoints.push_back(corners);
		m_dstPoints.push_back(dstcorners);
	}
	////////

	cvtColor(img5, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

//	cv::drawChessboardCorners(img5, cv::Size(11, 8), corners, ret);

	if (corners.size() == 88) {
		m_srcPoints.push_back(corners);
		m_dstPoints.push_back(dstcorners);
	}
	////////

	cvtColor(img6, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

//	cv::drawChessboardCorners(img6, cv::Size(11, 8), corners, ret);

	if (corners.size() == 88) {
		m_srcPoints.push_back(corners);
		m_dstPoints.push_back(dstcorners);
	}
	/////////

	cvtColor(img7, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

//	cv::drawChessboardCorners(img7, cv::Size(11, 8), corners, ret);

	if (corners.size() == 88) {
		m_srcPoints.push_back(corners);
		m_dstPoints.push_back(dstcorners);
	}
	/////////

	cvtColor(img8, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

//	cv::drawChessboardCorners(img8, cv::Size(11, 8), corners, ret);

	if (corners.size() == 88) {
		m_srcPoints.push_back(corners);
		m_dstPoints.push_back(dstcorners);
	}
	/////////

	cvtColor(img9, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

//	cv::drawChessboardCorners(img9, cv::Size(11, 8), corners, ret);

	if (corners.size() == 88) {
		m_srcPoints.push_back(corners);
		m_dstPoints.push_back(dstcorners);
	}
	///////

	cvtColor(img10, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

//	cv::drawChessboardCorners(img10, cv::Size(11, 8), corners, ret);

	if (corners.size() == 88) {
		m_srcPoints.push_back(corners);
		m_dstPoints.push_back(dstcorners);
	}
	////////

	cvtColor(img11, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

//	cv::drawChessboardCorners(img11, cv::Size(11, 8), corners, ret);

	if (corners.size() == 88) {
		m_srcPoints.push_back(corners);
		m_dstPoints.push_back(dstcorners);
	}
	//////////

	cvtColor(img12, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

//	cv::drawChessboardCorners(img12, cv::Size(11, 8), corners, ret);

	if (corners.size() == 88) {
		m_srcPoints.push_back(corners);
		m_dstPoints.push_back(dstcorners);
	}
	/////////

	cvtColor(img13, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

//	cv::drawChessboardCorners(img13, cv::Size(11, 8), corners, ret);

	if (corners.size() == 88) {
		m_srcPoints.push_back(corners);
		m_dstPoints.push_back(dstcorners);
	}
	////////

	cvtColor(img14, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

//	cv::drawChessboardCorners(img14, cv::Size(11, 8), corners, ret);

	if (corners.size() == 88) {
		m_srcPoints.push_back(corners);
		m_dstPoints.push_back(dstcorners);
	}
	////////

	cvtColor(img15, img_gray, cv::COLOR_BGR2GRAY);
	ret = findChessboardCorners(img_gray, cv::Size(11, 8), corners, CALIB_CB_ADAPTIVE_THRESH);
	criteria = cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 40, 0.1);
	cv::cornerSubPix(img_gray, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);

//	cv::drawChessboardCorners(img15, cv::Size(11, 8), corners, ret);

	if (corners.size() == 88) {
		m_srcPoints.push_back(corners);
		m_dstPoints.push_back(dstcorners);
	}
	////////

	Mat intrinsic_matrix, distortion_matrix;
	vector<Mat> rvecs, tvecs;
	Size imageSize = img1.size();
	calibrateCamera(m_dstPoints, m_srcPoints, imageSize, intrinsic_matrix, distortion_matrix, rvecs, tvecs);
	cout << distortion_matrix << endl;
	Mat objectPoints, imagePoints;
	objectPoints.push_back(Point3f(2, 2, 2));
	objectPoints.push_back(Point3f(2, 0, 2));
	objectPoints.push_back(Point3f(0, 0, 2));
	objectPoints.push_back(Point3f(0, 2, 2));
	objectPoints.push_back(Point3f(2, 2, 0));
	objectPoints.push_back(Point3f(2, 0, 0));
	objectPoints.push_back(Point3f(0, 0, 0));
	objectPoints.push_back(Point3f(0, 2, 0));
	cvNamedWindow("result", 0);
	cvResizeWindow("result", 500, 500);

	projectPoints(objectPoints,rvecs[0],tvecs[0],intrinsic_matrix,distortion_matrix,imagePoints);
	Mat contoursImg1 = img1.clone();
	line(contoursImg1, Point(imagePoints.at<float>(0, 0), imagePoints.at<float>(0, 1)), Point(imagePoints.at<float>(1, 0), imagePoints.at<float>(1, 1)), Scalar(0, 0, 255), 3);
	line(contoursImg1, Point(imagePoints.at<float>(0, 0), imagePoints.at<float>(0, 1)), Point(imagePoints.at<float>(3, 0), imagePoints.at<float>(3, 1)), Scalar(0, 0, 255), 3);
	line(contoursImg1, Point(imagePoints.at<float>(0, 0), imagePoints.at<float>(0, 1)), Point(imagePoints.at<float>(4, 0), imagePoints.at<float>(4, 1)), Scalar(0, 0, 255), 3);
	line(contoursImg1, Point(imagePoints.at<float>(1, 0), imagePoints.at<float>(1, 1)), Point(imagePoints.at<float>(2, 0), imagePoints.at<float>(2, 1)), Scalar(0, 0, 255), 3);
	line(contoursImg1, Point(imagePoints.at<float>(5, 0), imagePoints.at<float>(5, 1)), Point(imagePoints.at<float>(1, 0), imagePoints.at<float>(1, 1)), Scalar(0, 0, 255), 3);
	line(contoursImg1, Point(imagePoints.at<float>(2, 0), imagePoints.at<float>(2, 1)), Point(imagePoints.at<float>(3, 0), imagePoints.at<float>(3, 1)), Scalar(0, 0, 255), 3);
	line(contoursImg1, Point(imagePoints.at<float>(2, 0), imagePoints.at<float>(2, 1)), Point(imagePoints.at<float>(6, 0), imagePoints.at<float>(6, 1)), Scalar(0, 0, 255), 3);
	line(contoursImg1, Point(imagePoints.at<float>(6, 0), imagePoints.at<float>(6, 1)), Point(imagePoints.at<float>(5, 0), imagePoints.at<float>(5, 1)), Scalar(0, 0, 255), 3);
	line(contoursImg1, Point(imagePoints.at<float>(4, 0), imagePoints.at<float>(4, 1)), Point(imagePoints.at<float>(5, 0), imagePoints.at<float>(5, 1)), Scalar(0, 0, 255), 3);
	line(contoursImg1, Point(imagePoints.at<float>(7, 0), imagePoints.at<float>(7, 1)), Point(imagePoints.at<float>(6, 0), imagePoints.at<float>(6, 1)), Scalar(0, 0, 255), 3);
	line(contoursImg1, Point(imagePoints.at<float>(3, 0), imagePoints.at<float>(3, 1)), Point(imagePoints.at<float>(7, 0), imagePoints.at<float>(7, 1)), Scalar(0, 0, 255), 3);
	line(contoursImg1, Point(imagePoints.at<float>(7, 0), imagePoints.at<float>(7, 1)), Point(imagePoints.at<float>(4, 0), imagePoints.at<float>(4, 1)), Scalar(0, 0, 255), 3);


	projectPoints(objectPoints, rvecs[1], tvecs[1], intrinsic_matrix, distortion_matrix, imagePoints);
	Mat contoursImg2 = img2.clone();
	line(contoursImg2, Point(imagePoints.at<float>(0, 0), imagePoints.at<float>(0, 1)), Point(imagePoints.at<float>(1, 0), imagePoints.at<float>(1, 1)), Scalar(0, 0, 255), 3);
	line(contoursImg2, Point(imagePoints.at<float>(0, 0), imagePoints.at<float>(0, 1)), Point(imagePoints.at<float>(3, 0), imagePoints.at<float>(3, 1)), Scalar(0, 0, 255), 3);
	line(contoursImg2, Point(imagePoints.at<float>(0, 0), imagePoints.at<float>(0, 1)), Point(imagePoints.at<float>(4, 0), imagePoints.at<float>(4, 1)), Scalar(0, 0, 255), 3);
	line(contoursImg2, Point(imagePoints.at<float>(1, 0), imagePoints.at<float>(1, 1)), Point(imagePoints.at<float>(2, 0), imagePoints.at<float>(2, 1)), Scalar(0, 0, 255), 3);
	line(contoursImg2, Point(imagePoints.at<float>(5, 0), imagePoints.at<float>(5, 1)), Point(imagePoints.at<float>(1, 0), imagePoints.at<float>(1, 1)), Scalar(0, 0, 255), 3);
	line(contoursImg2, Point(imagePoints.at<float>(2, 0), imagePoints.at<float>(2, 1)), Point(imagePoints.at<float>(3, 0), imagePoints.at<float>(3, 1)), Scalar(0, 0, 255), 3);
	line(contoursImg2, Point(imagePoints.at<float>(2, 0), imagePoints.at<float>(2, 1)), Point(imagePoints.at<float>(6, 0), imagePoints.at<float>(6, 1)), Scalar(0, 0, 255), 3);
	line(contoursImg2, Point(imagePoints.at<float>(6, 0), imagePoints.at<float>(6, 1)), Point(imagePoints.at<float>(5, 0), imagePoints.at<float>(5, 1)), Scalar(0, 0, 255), 3);
	line(contoursImg2, Point(imagePoints.at<float>(4, 0), imagePoints.at<float>(4, 1)), Point(imagePoints.at<float>(5, 0), imagePoints.at<float>(5, 1)), Scalar(0, 0, 255), 3);
	line(contoursImg2, Point(imagePoints.at<float>(7, 0), imagePoints.at<float>(7, 1)), Point(imagePoints.at<float>(6, 0), imagePoints.at<float>(6, 1)), Scalar(0, 0, 255), 3);
	line(contoursImg2, Point(imagePoints.at<float>(3, 0), imagePoints.at<float>(3, 1)), Point(imagePoints.at<float>(7, 0), imagePoints.at<float>(7, 1)), Scalar(0, 0, 255), 3);
	line(contoursImg2, Point(imagePoints.at<float>(7, 0), imagePoints.at<float>(7, 1)), Point(imagePoints.at<float>(4, 0), imagePoints.at<float>(4, 1)), Scalar(0, 0, 255), 3);
	

	projectPoints(objectPoints, rvecs[2], tvecs[2], intrinsic_matrix, distortion_matrix, imagePoints);
	Mat contoursImg3 = img3.clone();
	line(contoursImg3, Point(imagePoints.at<float>(0, 0), imagePoints.at<float>(0, 1)), Point(imagePoints.at<float>(1, 0), imagePoints.at<float>(1, 1)), Scalar(0, 0, 255), 3);
	line(contoursImg3, Point(imagePoints.at<float>(0, 0), imagePoints.at<float>(0, 1)), Point(imagePoints.at<float>(3, 0), imagePoints.at<float>(3, 1)), Scalar(0, 0, 255), 3);
	line(contoursImg3, Point(imagePoints.at<float>(0, 0), imagePoints.at<float>(0, 1)), Point(imagePoints.at<float>(4, 0), imagePoints.at<float>(4, 1)), Scalar(0, 0, 255), 3);
	line(contoursImg3, Point(imagePoints.at<float>(1, 0), imagePoints.at<float>(1, 1)), Point(imagePoints.at<float>(2, 0), imagePoints.at<float>(2, 1)), Scalar(0, 0, 255), 3);
	line(contoursImg3, Point(imagePoints.at<float>(5, 0), imagePoints.at<float>(5, 1)), Point(imagePoints.at<float>(1, 0), imagePoints.at<float>(1, 1)), Scalar(0, 0, 255), 3);
	line(contoursImg3, Point(imagePoints.at<float>(2, 0), imagePoints.at<float>(2, 1)), Point(imagePoints.at<float>(3, 0), imagePoints.at<float>(3, 1)), Scalar(0, 0, 255), 3);
	line(contoursImg3, Point(imagePoints.at<float>(2, 0), imagePoints.at<float>(2, 1)), Point(imagePoints.at<float>(6, 0), imagePoints.at<float>(6, 1)), Scalar(0, 0, 255), 3);
	line(contoursImg3, Point(imagePoints.at<float>(6, 0), imagePoints.at<float>(6, 1)), Point(imagePoints.at<float>(5, 0), imagePoints.at<float>(5, 1)), Scalar(0, 0, 255), 3);
	line(contoursImg3, Point(imagePoints.at<float>(4, 0), imagePoints.at<float>(4, 1)), Point(imagePoints.at<float>(5, 0), imagePoints.at<float>(5, 1)), Scalar(0, 0, 255), 3);
	line(contoursImg3, Point(imagePoints.at<float>(7, 0), imagePoints.at<float>(7, 1)), Point(imagePoints.at<float>(6, 0), imagePoints.at<float>(6, 1)), Scalar(0, 0, 255), 3);
	line(contoursImg3, Point(imagePoints.at<float>(3, 0), imagePoints.at<float>(3, 1)), Point(imagePoints.at<float>(7, 0), imagePoints.at<float>(7, 1)), Scalar(0, 0, 255), 3);
	line(contoursImg3, Point(imagePoints.at<float>(7, 0), imagePoints.at<float>(7, 1)), Point(imagePoints.at<float>(4, 0), imagePoints.at<float>(4, 1)), Scalar(0, 0, 255), 3);
	

	projectPoints(objectPoints, rvecs[3], tvecs[3], intrinsic_matrix, distortion_matrix, imagePoints);
	Mat contoursImg4 = img4.clone();
	line(contoursImg4, Point(imagePoints.at<float>(0, 0), imagePoints.at<float>(0, 1)), Point(imagePoints.at<float>(1, 0), imagePoints.at<float>(1, 1)), Scalar(0, 0, 255), 3);
	line(contoursImg4, Point(imagePoints.at<float>(0, 0), imagePoints.at<float>(0, 1)), Point(imagePoints.at<float>(3, 0), imagePoints.at<float>(3, 1)), Scalar(0, 0, 255), 3);
	line(contoursImg4, Point(imagePoints.at<float>(0, 0), imagePoints.at<float>(0, 1)), Point(imagePoints.at<float>(4, 0), imagePoints.at<float>(4, 1)), Scalar(0, 0, 255), 3);
	line(contoursImg4, Point(imagePoints.at<float>(1, 0), imagePoints.at<float>(1, 1)), Point(imagePoints.at<float>(2, 0), imagePoints.at<float>(2, 1)), Scalar(0, 0, 255), 3);
	line(contoursImg4, Point(imagePoints.at<float>(5, 0), imagePoints.at<float>(5, 1)), Point(imagePoints.at<float>(1, 0), imagePoints.at<float>(1, 1)), Scalar(0, 0, 255), 3);
	line(contoursImg4, Point(imagePoints.at<float>(2, 0), imagePoints.at<float>(2, 1)), Point(imagePoints.at<float>(3, 0), imagePoints.at<float>(3, 1)), Scalar(0, 0, 255), 3);
	line(contoursImg4, Point(imagePoints.at<float>(2, 0), imagePoints.at<float>(2, 1)), Point(imagePoints.at<float>(6, 0), imagePoints.at<float>(6, 1)), Scalar(0, 0, 255), 3);
	line(contoursImg4, Point(imagePoints.at<float>(6, 0), imagePoints.at<float>(6, 1)), Point(imagePoints.at<float>(5, 0), imagePoints.at<float>(5, 1)), Scalar(0, 0, 255), 3);
	line(contoursImg4, Point(imagePoints.at<float>(4, 0), imagePoints.at<float>(4, 1)), Point(imagePoints.at<float>(5, 0), imagePoints.at<float>(5, 1)), Scalar(0, 0, 255), 3);
	line(contoursImg4, Point(imagePoints.at<float>(7, 0), imagePoints.at<float>(7, 1)), Point(imagePoints.at<float>(6, 0), imagePoints.at<float>(6, 1)), Scalar(0, 0, 255), 3);
	line(contoursImg4, Point(imagePoints.at<float>(3, 0), imagePoints.at<float>(3, 1)), Point(imagePoints.at<float>(7, 0), imagePoints.at<float>(7, 1)), Scalar(0, 0, 255), 3);
	line(contoursImg4, Point(imagePoints.at<float>(7, 0), imagePoints.at<float>(7, 1)), Point(imagePoints.at<float>(4, 0), imagePoints.at<float>(4, 1)), Scalar(0, 0, 255), 3);


	projectPoints(objectPoints, rvecs[4], tvecs[4], intrinsic_matrix, distortion_matrix, imagePoints);
	Mat contoursImg5 = img5.clone();
	line(contoursImg5, Point(imagePoints.at<float>(0, 0), imagePoints.at<float>(0, 1)), Point(imagePoints.at<float>(1, 0), imagePoints.at<float>(1, 1)), Scalar(0, 0, 255), 3);
	line(contoursImg5, Point(imagePoints.at<float>(0, 0), imagePoints.at<float>(0, 1)), Point(imagePoints.at<float>(3, 0), imagePoints.at<float>(3, 1)), Scalar(0, 0, 255), 3);
	line(contoursImg5, Point(imagePoints.at<float>(0, 0), imagePoints.at<float>(0, 1)), Point(imagePoints.at<float>(4, 0), imagePoints.at<float>(4, 1)), Scalar(0, 0, 255), 3);
	line(contoursImg5, Point(imagePoints.at<float>(1, 0), imagePoints.at<float>(1, 1)), Point(imagePoints.at<float>(2, 0), imagePoints.at<float>(2, 1)), Scalar(0, 0, 255), 3);
	line(contoursImg5, Point(imagePoints.at<float>(5, 0), imagePoints.at<float>(5, 1)), Point(imagePoints.at<float>(1, 0), imagePoints.at<float>(1, 1)), Scalar(0, 0, 255), 3);
	line(contoursImg5, Point(imagePoints.at<float>(2, 0), imagePoints.at<float>(2, 1)), Point(imagePoints.at<float>(3, 0), imagePoints.at<float>(3, 1)), Scalar(0, 0, 255), 3);
	line(contoursImg5, Point(imagePoints.at<float>(2, 0), imagePoints.at<float>(2, 1)), Point(imagePoints.at<float>(6, 0), imagePoints.at<float>(6, 1)), Scalar(0, 0, 255), 3);
	line(contoursImg5, Point(imagePoints.at<float>(6, 0), imagePoints.at<float>(6, 1)), Point(imagePoints.at<float>(5, 0), imagePoints.at<float>(5, 1)), Scalar(0, 0, 255), 3);
	line(contoursImg5, Point(imagePoints.at<float>(4, 0), imagePoints.at<float>(4, 1)), Point(imagePoints.at<float>(5, 0), imagePoints.at<float>(5, 1)), Scalar(0, 0, 255), 3);
	line(contoursImg5, Point(imagePoints.at<float>(7, 0), imagePoints.at<float>(7, 1)), Point(imagePoints.at<float>(6, 0), imagePoints.at<float>(6, 1)), Scalar(0, 0, 255), 3);
	line(contoursImg5, Point(imagePoints.at<float>(3, 0), imagePoints.at<float>(3, 1)), Point(imagePoints.at<float>(7, 0), imagePoints.at<float>(7, 1)), Scalar(0, 0, 255), 3);
	line(contoursImg5, Point(imagePoints.at<float>(7, 0), imagePoints.at<float>(7, 1)), Point(imagePoints.at<float>(4, 0), imagePoints.at<float>(4, 1)), Scalar(0, 0, 255), 3);
	
	VideoWriter writer;
	writer.open("VideoTest.avi", CV_FOURCC('M', 'J', 'P', 'G'), 2, Size(2048,2048));

	
	
	writer.write(contoursImg1);
	writer.write(contoursImg2);
	writer.write(contoursImg3);
	writer.write(contoursImg4);
	writer.write(contoursImg5);

	imshow("result", contoursImg1);
	waitKey(500);
	imshow("result", contoursImg2);
	waitKey(500);
	imshow("result", contoursImg3);
	waitKey(500);
	imshow("result", contoursImg4);
	waitKey(500);
	imshow("result", contoursImg5);
	waitKey(500);


	cvDestroyWindow("result");
	
	



}

void CMFCHW1Dlg::drawHistImg(const Mat &src, Mat &dst) {
	int histSize = 256;
	float histMaxValue = 0;
	for (int i = 0; i<histSize; i++) {
		float tempValue = src.at<float>(i);
		if (histMaxValue < tempValue) {
			histMaxValue = tempValue;
		}
	}

	float scale = 256 / histMaxValue;
	for (int i = 0; i<histSize; i++) {
		int intensity = static_cast<int>(src.at<float>(i)*scale);
		line(dst, Point(i, 255), Point(i, 255 - intensity), Scalar(0, 0, 255));
	}
}

void CMFCHW1Dlg::drawHistImg2(const Mat &src, Mat &dst) {
	int histSize = 180;
	float histMaxValue = 0;
	for (int i = 0; i<histSize; i++) {
		float tempValue = src.at<float>(i);
		if (histMaxValue < tempValue) {
			histMaxValue = tempValue;
		}
	}

	float scale = 256 / histMaxValue;
	for (int i = 0; i<180; i++) {
		int intensity = static_cast<int>(src.at<float>(i)*scale);
		line(dst, Point(i, 255), Point(i, 255 - intensity), Scalar(0, 0, 255));
	}
}

void CMFCHW1Dlg::calcCircles(const Mat &input, vector<Vec3f> &circles) {
	Mat contours;
	Canny(input, contours, 180, 220);
	HoughCircles(contours, circles, CV_HOUGH_GRADIENT, 2, 50, 220, 50,10,20);
}

void CMFCHW1Dlg::calcCircles2(const Mat &input, vector<Vec3f> &circles) {
	Mat contours;
	Canny(input, contours, 100, 240);
	HoughCircles(contours, circles, CV_HOUGH_GRADIENT, 2, 25, 240, 40, 8, 14);
}

void CMFCHW1Dlg::drawCircle(Mat &input, const vector<Vec3f> &circles) {
	for (int i = 0; i<circles.size(); i++) {
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		circle(input, center, 1, Scalar(0, 0,255), 3, 8, 0);
		circle(input, center, radius, Scalar(0, 255, 0), 3, 8, 0);
	}
}

