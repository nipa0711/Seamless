
// SeamlessDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "Seamless.h"
#include "SeamlessDlg.h"
#include "afxdialogex.h"
#include "WHOMADE.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSeamlessDlg 대화 상자



CSeamlessDlg::CSeamlessDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSeamlessDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSeamlessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, ID_ShowBG, ShowBGFrame);
	DDX_Control(pDX, ID_ShowInside, ShowInsideFrame);
	DDX_Control(pDX, ID_ShowResult, ShowResultFrame);
}

BEGIN_MESSAGE_MAP(CSeamlessDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_Exit, &CSeamlessDlg::OnExit)
	ON_COMMAND(ID_OpenBGimage, &CSeamlessDlg::OnOpenbgimage)
	ON_COMMAND(ID_OpenInsideImage, &CSeamlessDlg::OnOpeninsideimage)
	ON_COMMAND(ID_FileSave, &CSeamlessDlg::OnFilesave)
	ON_COMMAND(ID_REDRAW, &CSeamlessDlg::OnRedraw)
	ON_STN_CLICKED(ID_ShowResult, &CSeamlessDlg::OnStnClickedShowresult)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDCANCEL, &CSeamlessDlg::OnBnClickedCancel)
	ON_COMMAND(ID_WHOMADE, &CSeamlessDlg::OnWhomade)
END_MESSAGE_MAP()


// CSeamlessDlg 메시지 처리기

BOOL CSeamlessDlg::OnInitDialog()
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
	CStatic *staticSize = (CStatic *)GetDlgItem(ID_ShowBG);
	CStatic *staticSize2 = (CStatic *)GetDlgItem(ID_ShowInside);
	CStatic *staticSize3 = (CStatic *)GetDlgItem(ID_ShowResult);

	staticSize->GetClientRect(rect);
	staticSize2->GetClientRect(rect2);
	staticSize3->GetClientRect(rect3);

	showBGWidth = rect.Width();
	showBGHeight = rect.Height();

	showInsideWidth = rect2.Width();
	showInsideHeight = rect2.Height();

	showResultWidth = rect3.Width();
	showResultHeight = rect3.Height();



	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CSeamlessDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSeamlessDlg::OnPaint()
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
		rect = CRect(0, 0, showBGWidth, showBGHeight);
		pDC1 = ShowBGFrame.GetDC();
		hDC1 = pDC1->GetSafeHdc();

		rect2 = CRect(0, 0, showInsideWidth, showInsideHeight);
		pDC2 = ShowInsideFrame.GetDC();
		hDC2 = pDC2->GetSafeHdc();

		rect3 = CRect(0, 0, showResultWidth, showResultHeight);
		pDC3 = ShowResultFrame.GetDC();
		hDC3 = pDC3->GetSafeHdc();



		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CSeamlessDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSeamlessDlg::OnExit()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CSeamlessDlg::OnCancel();
}


void CSeamlessDlg::OnOpenbgimage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("Image(*.BMP,*.JPG,*.PNG)|*.BMP;*.JPG;*.PNG|All Files(*.*)|*.*||")); // 파일 다이얼로그를 이용한 파일 열기
	if (IDOK == dlg.DoModal())
	{
		CString strPathName = dlg.GetPathName();
		bgMat = imread(CStrToStr(strPathName));

		IplImage1 = bgMat;
		m_CVvImageObj1.CopyOf(&IplImage1);
		m_CVvImageObj1.DrawToHDC(hDC1, &rect);

		CMenu *menu = (CMenu*)GetMenu();
		// This will disable
		menu->EnableMenuItem(ID_OpenInsideImage /*your menu ID*/, MF_ENABLED);
	}
}

string CSeamlessDlg::CStrToStr(CString str)
{
	string outputStr = string(CT2CA(str.operator LPCWSTR()));
	return outputStr;
}

CBitmap* CSeamlessDlg::IplImageToCBitmap(IplImage* img)
{
	CDC dc;
	CDC memDC;

	if (!dc.CreateDC(L"DISPLAY", NULL, NULL, NULL))
		return NULL;

	if (!memDC.CreateCompatibleDC(&dc))
		return NULL;

	CBitmap* bmp = new CBitmap();
	CBitmap* pOldBitmap;

	bmp->CreateCompatibleBitmap(&dc, img->width, img->height);
	pOldBitmap = memDC.SelectObject(bmp);

	CvvImage cvImage; // you will need OpenCV_2.2.0- to use CvvImage 
	cvImage.CopyOf(img);
	cvImage.Show(memDC.m_hDC, 0, 0, img->width, img->height, 0, 0);
	cvImage.Destroy();

	memDC.SelectObject(pOldBitmap);
	memDC.DeleteDC();
	dc.DeleteDC();

	return bmp;
}

void CSeamlessDlg::OnOpeninsideimage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("Image(*.BMP,*.JPG,*.PNG)|*.BMP;*.JPG;*.PNG|All Files(*.*)|*.*||"));
	if (IDOK == dlg.DoModal())
	{
		CString strPathName = dlg.GetPathName();
		insideMat = imread(CStrToStr(strPathName));

		IplImage2 = insideMat;
		m_CVvImageObj2.CopyOf(&IplImage2);
		m_CVvImageObj2.DrawToHDC(hDC2, &rect2);

		CMenu *menu = (CMenu*)GetMenu();
		// This will disable
		menu->EnableMenuItem(ID_FileSave /*your menu ID*/, MF_ENABLED);

		//pt = { 0 };

		doSeamless();
	}
}

void CSeamlessDlg::doSeamless()
{
	// Create an all white mask
	Mat src_mask = 255 * Mat::ones(insideMat.rows, insideMat.cols, insideMat.depth());

	// The location of the center of the src in the dst
	Point center(bgMat.cols / 2, bgMat.rows / 2);
	//Point center(insideMat.cols/2, insideMat.rows/2);

	// Seamlessly clone src into dst and put the results in output
	seamlessClone(insideMat, bgMat, src_mask, center, resultMat, MIXED_CLONE);

	IplImage3 = resultMat;
	m_CVvImageObj2.CopyOf(&IplImage3);
	m_CVvImageObj2.DrawToHDC(hDC3, &rect3);
}


void CSeamlessDlg::OnFilesave()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CFileDialog dlg(FALSE, _T("*.jpg"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("JPG(*.jpg)|*.jpg|BMP(*.bmp)|*.bmp|PNG(*.png)|*.png|All Files(*.*)|*.*||"));

	if (IDOK == dlg.DoModal())
	{
		CString strFolderPath = dlg.GetFolderPath();
		CString strFileName = dlg.GetFileName();
		CString strFileExtension = dlg.GetFileExt();
		imwrite(CStrToStr(strFolderPath) + "\\" + CStrToStr(strFileName), resultMat);
	}
}


void CSeamlessDlg::OnRedraw()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	doSeamless();
}


void CSeamlessDlg::OnStnClickedShowresult()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString info;
	GetCursorPos(&pt);

	CRect rt;
	// 픽쳐 컨트롤의 사각형 좌표를 구함
	// GetClientRect 는 크기를 구하니 GetWindowRect 이용...
	((CStatic*)GetDlgItem(ID_ShowResult))->GetWindowRect(&rt);

	// GetWindowRect 로 얻은 좌표는 스크린 좌표(물리적) 이니 이를
	// 화면 좌표(논리적, 클라이언트 좌표)로 변환
	ScreenToClient(&rt);

	Mat src_mask = 255 * Mat::ones(insideMat.rows, insideMat.cols, insideMat.depth());

	seamlessClone(insideMat, bgMat, src_mask, Point(0, 0), resultMat, MIXED_CLONE);

	IplImage3 = resultMat;
	m_CVvImageObj2.CopyOf(&IplImage3);
	m_CVvImageObj2.DrawToHDC(hDC3, &rect3);

	info.Format(L"mouse point(x / y): %d / %d", (pt.x - rt.left), (pt.y - 16));
	MessageBox(info);
}


void CSeamlessDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnMouseMove(nFlags, point);
}


void CSeamlessDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CRect rt;
	// 픽쳐 컨트롤의 사각형 좌표를 구함
	// GetClientRect 는 크기를 구하니 GetWindowRect 이용...
	((CStatic*)GetDlgItem(ID_ShowResult))->GetWindowRect(&rt);

	// GetWindowRect 로 얻은 좌표는 스크린 좌표(물리적) 이니 이를
	// 화면 좌표(논리적, 클라이언트 좌표)로 변환
	ScreenToClient(&rt);

	float Xratio = (float)bgMat.cols / (float)showResultWidth;
	float Yratio = (float)bgMat.rows / (float)showResultHeight;

	CString info;


	if ((point.x >= rt.left  && point.x <= rt.right) && (point.y >= rt.top && point.y <= rt.bottom))
	{
		int currentX = ((point.x - rt.left)*Xratio) + (insideMat.cols / 2);
		int currentY = ((point.y - rt.top)*Yratio) + (insideMat.rows / 2);

		Mat src_mask = 255 * Mat::ones(insideMat.rows, insideMat.cols, insideMat.depth());

		if (currentX < (insideMat.cols / 2))
		{
			currentX = insideMat.cols / 2 + 1;
		}

		if (currentY < (insideMat.rows / 2))
		{
			currentY = insideMat.cols / 2 + 1;
		}

		if (currentX > bgMat.cols - (insideMat.cols / 2))
		{
			currentX = bgMat.cols - (insideMat.cols / 2) - 1;
		}

		if (currentY > bgMat.rows - (insideMat.rows / 2))
		{
			currentY = bgMat.rows - (insideMat.rows / 2) - 1;
		}

		seamlessClone(insideMat, bgMat, src_mask, Point(currentX, currentY), resultMat, MIXED_CLONE);


		IplImage3 = resultMat;
		m_CVvImageObj2.CopyOf(&IplImage3);
		m_CVvImageObj2.DrawToHDC(hDC3, &rect3);
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CSeamlessDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}


void CSeamlessDlg::OnWhomade()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	WHOMADE dlg;
	dlg.DoModal();
}
