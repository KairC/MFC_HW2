
// MFC_HW1Dlg.h: 標頭檔
#include "cv.h"
#include "opencv2\highgui\highgui.hpp"
#include "opencv2\imgproc.hpp"
#pragma once

using namespace cv;
using namespace std;

// CMFCHW1Dlg 對話方塊
class CMFCHW1Dlg : public CDialogEx
{
// 建構
public:
	CMFCHW1Dlg(CWnd* pParent = nullptr);	// 標準建構函式

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_HW1_DIALOG };
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
	afx_msg void OnBnClickedButton1();
	static void drawHistImg(const cv::Mat &src, cv::Mat &dst);
	static void drawHistImg2(const cv::Mat &src, cv::Mat &dst);
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	
	
	

	afx_msg void OnBnClickedButton5();

	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton10();
	
	static void calcCircles(const cv::Mat &input, vector<cv::Vec3f> &circles);
	static void calcCircles2(const cv::Mat &input, vector<cv::Vec3f> &circles);
	static void drawCircle(cv::Mat &input, const vector<cv::Vec3f> &circles);

};
