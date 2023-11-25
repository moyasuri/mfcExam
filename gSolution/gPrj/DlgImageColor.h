#pragma once
#include "afxdialogex.h"


// DlgImageColor 대화 상자

class DlgImageColor : public CDialogEx
{
	DECLARE_DYNAMIC(DlgImageColor)

public:
	DlgImageColor(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~DlgImageColor();
	CImage m_image;
	CWnd* m_pParent;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DlgImageColor };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	void DlgImageColor::InitImage();

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
};
