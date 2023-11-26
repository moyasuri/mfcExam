// DlgImageColor.cpp: 구현 파일
//

#include "stdafx.h"
#include "gPrj.h"
#include "afxdialogex.h"
#include "DlgImageColor.h"
#include "gPrjDlg.h"

// DlgImageColor 대화 상자

IMPLEMENT_DYNAMIC(DlgImageColor, CDialogEx)

DlgImageColor::DlgImageColor(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DlgImageColor, pParent)
{
	m_pParent = pParent;
}

DlgImageColor::~DlgImageColor()
{
}

void DlgImageColor::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DlgImageColor, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// DlgImageColor 메시지 처리기



BOOL DlgImageColor::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	MoveWindow(0, 0, 1000, 1000); // 창의크기 초기화
	InitImage();
	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void DlgImageColor::InitImage()
{
	//int nWidth = 4096;
	//int nHeight = 4096;
	// 너무 크면 화면에 안보이니까 줄이자.
	int nWidth = 1000;
	int nHeight = 1000;
	int nBpp = 24;

	m_image.Create(nWidth, -nHeight, nBpp);
	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();


	// 화이트 설정
	for (int j = 0; j < nHeight; j++) {
		for (int i = 0; i < nWidth; i++) {
			fm[j * nPitch + i * 3] = 255; // Blue
			fm[j * nPitch + i * 3 + 1] = 255; // Green
			fm[j * nPitch + i * 3 + 2] = 255; // Red
		}
	}

}

void DlgImageColor::OnPaint()
{	
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
	if (m_image)
		m_image.Draw(dc, 0, 0);

}
