
// gPrjDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "gPrj.h"
#include "gPrjDlg.h"
#include "afxdialogex.h"

#include <iostream>
using namespace std;


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CgPrjDlg 대화 상자



CgPrjDlg::CgPrjDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GPRJ_DIALOG, pParent)
	, m_nNum_Radius(0)
	, m_nNum_CircleCnt(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

void CgPrjDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CIRCLE_RADIUS, m_nNum_Radius);
	DDX_Text(pDX, IDC_CIRCLE_nCnt, m_nNum_CircleCnt);
}

BEGIN_MESSAGE_MAP(CgPrjDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_TEST, &CgPrjDlg::OnBnClickedBtnTest)
	ON_BN_CLICKED(IDC_BTN_PROCESS, &CgPrjDlg::OnBnClickedBtnProcess)
	ON_BN_CLICKED(IDC_BTN_MAKE_PATTERN, &CgPrjDlg::OnBnClickedBtnMakePattern)
	ON_BN_CLICKED(IDC_BTN_GET_DATA, &CgPrjDlg::OnBnClickedBtnGetData)
	ON_BN_CLICKED(IDC_BTN_THREAD, &CgPrjDlg::OnBnClickedBtnThread)
	ON_BN_CLICKED(IDC_BTN_CALC_CENTROID, &CgPrjDlg::OnBnClickedBtnCalcCentroid)
	ON_BN_CLICKED(IDC_BTN_RESET, &CgPrjDlg::OnBnClickedBtnReset)
	ON_BN_CLICKED(IDC_BTN_LINEAR, &CgPrjDlg::OnBnClickedBtnLinear)
END_MESSAGE_MAP()


// CgPrjDlg 메시지 처리기

BOOL CgPrjDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	//ShowWindow(SW_SHOWMAXIMIZED); // 윈도우를 최대화 하는 역할
	MoveWindow(0, 0, 1920, 1080);  // 크기 바꾸기
	//m_pDlgImage = new CDlgImage;
	//m_pDlgImage->Create(IDD_DLGIMAGE, this);
	//m_pDlgImage->ShowWindow(SW_SHOW);


	// 노란색 원을 그리기 위하여 24bit dlg를 생성
	m_pDlgImageColor = new DlgImageColor;
	m_pDlgImageColor->Create(IDD_DlgImageColor, this);
	m_pDlgImageColor->ShowWindow(SW_SHOW);

	//m_pDlgImgResult = new CDlgImage;
	//m_pDlgImgResult->Create(IDD_DLGIMAGE, this);
	//m_pDlgImgResult->ShowWindow(SW_SHOW);
	//m_pDlgImgResult->MoveWindow(640, 0, 640, 480);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CgPrjDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CgPrjDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CgPrjDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



//void CgPrjDlg::OnBnClickedBtnDlg()
//{
//	m_pDlgImage->ShowWindow(SW_SHOW);
//}


void CgPrjDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	//if(m_pDlgImage)		 delete m_pDlgImage;
	if(m_pDlgImageColor) delete m_pDlgImageColor;
	//if(m_pDlgImgResult)	 delete m_pDlgImgResult;
}

void CgPrjDlg::callFunc(int n)
{
	std::cout << n << std::endl;
}

void CgPrjDlg::OnBnClickedBtnTest()
{
	unsigned char* fm = (unsigned char*)m_pDlgImage->m_image.GetBits();
	int nWidth = m_pDlgImage->m_image.GetWidth();
	int nHeight = m_pDlgImage->m_image.GetHeight();
	int nPitch = m_pDlgImage->m_image.GetPitch();
	memset(fm, 0, nWidth*nHeight);

	for (int k = 0; k < 10000; k++) {
		int x = rand() % nWidth;
		int y = rand() % nHeight;
		fm[y * nPitch + x] = rand()%0xff;

		//m_pDlgImgResult->m_nDataCount = k;
		//m_pDlgImgResult->m_ptData[k].x = x;
		//m_pDlgImgResult->m_ptData[k].y = y;
	}

	int nIndex = 0;
	int nTh = 100;
	for (int j = 0; j < nHeight; j++) {
		for (int i = 0; i < nWidth; i++) {
			if (fm[j*nPitch + i] > nTh) {
				if (m_pDlgImgResult->m_nDataCount < MAX_POINT) {
					//cout << nIndex << ":" << i << "," << j << endl;
					m_pDlgImgResult->m_ptData[nIndex].x = i;
					m_pDlgImgResult->m_ptData[nIndex].y = j;
					m_pDlgImgResult->m_nDataCount = ++nIndex;
				}
			}
		}
	}

	m_pDlgImage->Invalidate();
	m_pDlgImgResult->Invalidate();

}

#include "Process.h"
#include <chrono>
#include <thread>
using namespace std;
using namespace chrono;

void CgPrjDlg::OnBnClickedBtnProcess()
{
	auto start = system_clock::now();

	CProcess process;
	int nTh = 0;
	int nRet = process.getStarInfo(&m_pDlgImage->m_image, nTh);
//	Sleep(1000);
//	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	
	auto end = system_clock::now();
	auto millisec = duration_cast<milliseconds>(end - start);

	cout << nRet << "\t"<< millisec.count()*0.001 << "sec" <<endl;
}

void CgPrjDlg::ResetImage()
{

	unsigned char* fm = (unsigned char*)m_pDlgImageColor->m_image.GetBits();
	int nWidth = m_pDlgImageColor->m_image.GetWidth();
	int nHeight = m_pDlgImageColor->m_image.GetHeight();
	int nPitch = m_pDlgImageColor->m_image.GetPitch();

	// 화이트로 초기화
	for (int j = 0; j < nHeight; j++) {
		for (int i = 0; i < nWidth; i++) {
			fm[j * nPitch + i * 3] = 255; // Blue
			fm[j * nPitch + i * 3 + 1] = 255; // Green
			fm[j * nPitch + i * 3 + 2] = 255; // Red
		}
	}

	m_pDlgImageColor->Invalidate();
}


void CgPrjDlg::OnBnClickedBtnMakePattern()
{
	UpdateData(true);

	unsigned char* fm = (unsigned char*)m_pDlgImageColor->m_image.GetBits();
	int nWidth = m_pDlgImageColor->m_image.GetWidth();
	int nHeight = m_pDlgImageColor->m_image.GetHeight();
	int nPitch = m_pDlgImageColor->m_image.GetPitch();

	
	int nCount = m_nNum_CircleCnt;
	int nRadius = m_nNum_Radius;
	int nLimit = 0;

	ResetImage();

	// 두 중점사이의 거리
	int minDistance = 2 * nRadius;

	// Generate non-overlapping circles
	for (int k = 0; k < nCount; k++) {
		int x, y;
		bool isOverlapping;

		do {
			// Generate random position for the circle
			x = rand() % (nWidth - 2 * nRadius) + nRadius;
			y = rand() % (nHeight - 2 * nRadius) + nRadius;

			// Check if the new circle overlaps with any existing circle
			isOverlapping = false;

			for (int i = 0; i < k; i++) {
				int dx = abs(x - circles[i].x);
				int dy = abs(y - circles[i].y);
				int distanceSquared = dx * dx + dy * dy;

				if (distanceSquared < minDistance * minDistance) {
					isOverlapping = true;
					break;
				}
			}
			if (nLimit++ > SeedLimit) // 만약 원의 반지름이 너무커서 화면에 nCount만큼 원을 채우지 못하는 경우, 무한루프 방지
			{
				AfxMessageBox(_T("Radius is too large to fill the screen"));
				
				// 이 경우 circle을 초기화시켜줘야함
				memset(circles, 0, sizeof(circles));

				return;
			}
		} while (isOverlapping);

		DrawFilledCircle(nRadius, nWidth, nHeight, nPitch, x, y, fm);

		// 중심점 배열에 추가
		circles[k].x = x;
		circles[k].y = y;
	}

	m_pDlgImageColor->Invalidate();

}

// 무게 중심 구하기
void CgPrjDlg::CalculateCentroid(int nRadius)
{

	unsigned char* fm = (unsigned char*)m_pDlgImageColor->m_image.GetBits();
	int nWidth = m_pDlgImageColor->m_image.GetWidth();
	int nHeight = m_pDlgImageColor->m_image.GetHeight();
	int nPitch = m_pDlgImageColor->m_image.GetPitch();
	int nCount = m_nNum_CircleCnt;
	int crossLen = nRadius / 2;

	int xSum = 0 , ySum = 0;
	int xCpos, yCpos;
	bool isOverlapping;

	for (int k = 0; k < nCount; k++) {

		xSum += circles[k].x;
		ySum += circles[k].y;
	}
	
	xCpos = xSum / nCount;
	yCpos = ySum / nCount;

	// 중심선 긋기
	for (int j = -crossLen; j <= crossLen; j++) {
		for (int i = -crossLen; i <= crossLen; i++) {
				if (j == 0 || i == 0) {
					int index = ((yCpos + j) * nPitch + (xCpos + i) * 3);

					fm[index] = 0x00;       // Blue
					fm[index + 1] = 0x00;   // Green
					fm[index + 2] = 255;   // Red
				}
		}
	}

	DrawCircumference(nRadius, nWidth, nHeight, nPitch, xCpos, yCpos, fm);

	m_pDlgImageColor->Invalidate();

}

// 내부를 포함한 원 그리기
void CgPrjDlg::DrawFilledCircle(int nRadius, int nWidth, int nHeight, int nPitch, int x, int y, unsigned char* fm)
{
	for (int j = -nRadius; j <= nRadius; j++) {
		for (int i = -nRadius; i <= nRadius; i++) {
			
			// 이미 중심 좌표가 벗어나지 않는 x,y값을 인수로 가지고 있기는 함.
			if (x + i >= 0 && x + i < nWidth && y + j >= 0 && y + j < nHeight) { 
				int distanceSquared = i * i + j * j;
				if (distanceSquared <= nRadius * nRadius) {
					//fm[(y + j) * nPitch + (x + i)] = 0x00;
					int index = (y + j) * nPitch + (x + i) * 3;
					fm[index] = 0;         // Blue
					fm[index + 1] = 0;     // Green
					fm[index + 2] = 0;     // Red
				}
			}
		}
	}
}

// 원호그리기
void CgPrjDlg::DrawCircumference(int nRadius, int nWidth, int nHeight, int nPitch, int x, int y, unsigned char* fm)
{
	UpdateData(true);
	
	
	for (int angle = 0; angle < 360; angle++) {
		int newX = x + static_cast<int>(nRadius * cos(angle * 3.141592 / 180.0));
		int newY = y + static_cast<int>(nRadius * sin(angle * 3.141592 / 180.0));

		if (newX >= 0 && newX < nWidth && newY >= 0 && newY < nHeight) {
			int index = (newY * nPitch + newX * 3);

			fm[index] = 0x00;       // Blue
			fm[index + 1] = 255;   // Green
			fm[index + 2] = 255;   // Red
		}
	}

	m_pDlgImageColor->Invalidate();
}

// 일차함수 나타내보기
void CgPrjDlg::DrawLinearEquation(int slope)
{

	unsigned char* fm = (unsigned char*)m_pDlgImageColor->m_image.GetBits();
	int nWidth = m_pDlgImageColor->m_image.GetWidth();
	int nHeight = m_pDlgImageColor->m_image.GetHeight();
	int nPitch = m_pDlgImageColor->m_image.GetPitch();
	
	// 직선을 그릴 범위 설정
	int startX = 0;
	int endX = nWidth;
	

	// 직선을 그리는 반복문
	for (int x = startX; x <= endX; x++)
	{
		// 직선 상의 해당 x에 대한 y값 계산
		// 기울기가 - 인 이유는, 화면상에서 아래로 가면 y값이 + 이다.


		int y = - slope * x + nHeight;

		// 좌표가 이미지 범위 내에 있는지 확인
		if (x >= 0 && x < nWidth && y >= 0 && y < nHeight)
		{
			// 해당 좌표에 색상 설정
			int index = (y * nPitch + x * 3);
			fm[index] = 0;         // Blue
			fm[index + 1] = 0;     // Green
			fm[index + 2] = 0;   // Red
		}
	}

	// 이미지 갱신
	m_pDlgImageColor->Invalidate();
}

void CgPrjDlg::OnBnClickedBtnGetData()
{
	unsigned char* fm = (unsigned char*)m_pDlgImage->m_image.GetBits();
	int nWidth = m_pDlgImage->m_image.GetWidth();
	int nHeight = m_pDlgImage->m_image.GetHeight();
	int nPitch = m_pDlgImage->m_image.GetPitch();

	int nTh = 0x80;
	int nSumX = 0;
	int nSumY = 0;
	int nCount = 0;
	CRect rect(0, 0, nWidth, nHeight);
	for (int j = rect.top; j < rect.bottom; j++) {
		for (int i = rect.left; i < rect.right; i++) {
			if (fm[j*nPitch + i] > nTh) {
				nSumX += i;
				nSumY += j;
				nCount++;
			}
		}
	}
	double dCenterX = (double)nSumX / nCount;
	double dCenterY = (double)nSumY / nCount;

	cout << dCenterX << "\t" << dCenterY << endl;

	m_pDlgImage->Invalidate();
}

void threadProcess(CWnd* pParent, CRect rect, int *nRet)
{
	CgPrjDlg *pWnd = (CgPrjDlg*)pParent;
	*nRet = pWnd->processImg(rect);
}

void CgPrjDlg::OnBnClickedBtnThread()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	auto start = system_clock::now();

	int nImgSize = 4096 * 4;
	CRect rect(0, 0, nImgSize, nImgSize);
	CRect rt[4];
	int nRet[4];
	for (int k = 0; k < 4; k++) {
		rt[k] = rect;
		rt[k].OffsetRect(nImgSize*(k % 2), nImgSize*int(k / 2));
	}
	thread _thread0(threadProcess, this, rt[0], &nRet[0]);
	thread _thread1(threadProcess, this, rt[1], &nRet[1]);
	thread _thread2(threadProcess, this, rt[2], &nRet[2]);
	thread _thread3(threadProcess, this, rt[3], &nRet[3]);

	_thread0.join();
	_thread1.join();
	_thread2.join();
	_thread3.join();

	int nSum;
	for (int k = 0; k < 4; k++)
		nSum += nRet[k];

	auto end = system_clock::now();
	auto millisec = duration_cast<milliseconds>(end - start);

	cout << nSum << "\t" << millisec.count()*0.001 << "sec" << endl;

}

int CgPrjDlg::processImg(CRect rect)
{
	auto start = system_clock::now();

	CProcess process;
	int nTh = 0;
	int nRet = process.getStarInfo(&m_pDlgImage->m_image, nTh, rect);

	auto end = system_clock::now();
	auto millisec = duration_cast<milliseconds>(end - start);

	cout << nRet << "\t" << millisec.count()*0.001 << "sec" << endl;
	return nRet;
}


void CgPrjDlg::OnBnClickedBtnCalcCentroid()
{
	CalculateCentroid(m_nNum_Radius);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CgPrjDlg::OnBnClickedBtnReset()
{
	ResetImage();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CgPrjDlg::OnBnClickedBtnLinear()
{
	DrawLinearEquation(1);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
