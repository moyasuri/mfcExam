
// gPrjDlg.h : 헤더 파일
//
#include "DlgImage.h"
#include "DlgImageColor.h"
#pragma execution_character_set("utf-8")
#define MAX_CIRCLES 100000 // 임의 지정
#define SeedLimit 100000
#pragma once


// CgPrjDlg 대화 상자
class CgPrjDlg : public CDialogEx
{
// 생성입니다.
public:
	CgPrjDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

	CDlgImage *m_pDlgImage;
	CDlgImage *m_pDlgImgResult;
	DlgImageColor *m_pDlgImageColor;



private:
	struct Circle {
		int x;
		int y;
	};

	Circle circles[MAX_CIRCLES]; // 추가: 최대 원의 개수만큼 저장할 배열
	
	
	CSpinButtonCtrl m_spinControl;
	int m_nSpinValue;


// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GPRJ_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnBnClickedBtnDlg();
	afx_msg void OnDestroy();

	void callFunc(int n);
	afx_msg void OnBnClickedBtnTest();
	afx_msg void OnBnClickedBtnProcess();
	afx_msg void OnBnClickedBtnMakePattern();
	afx_msg void OnBnClickedBtnGetData();
	afx_msg void OnBnClickedBtnThread();
	int processImg(CRect rect);
	int m_nNum_Radius; // 원의 반지름
	int m_nNum_CircleCnt;
	void DrawFilledCircle(int nRadius, int nWidth, int nHeight, int nPitch, int x, int y, unsigned char* fm);
	void DrawCircumference(int nRadius, int nWidth, int nHeight, int nPitch, int x, int y, unsigned char* fm);
	void CalculateCentroid(int nRadius);
	void DrawLinearEquation(int slope);
	void ResetImage();
	

	afx_msg void OnBnClickedBtnCalcCentroid();
	afx_msg void OnBnClickedBtnReset();
	afx_msg void OnBnClickedBtnLinear();
};
