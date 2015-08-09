
// SeamlessDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "Seamless.h"
#include "SeamlessDlg.h"
#include "afxdialogex.h"
#include "WHOMADE.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	// �����Դϴ�.
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


// CSeamlessDlg ��ȭ ����



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


// CSeamlessDlg �޽��� ó����

BOOL CSeamlessDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
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



	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CSeamlessDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
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

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CSeamlessDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSeamlessDlg::OnExit()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CSeamlessDlg::OnCancel();
}


void CSeamlessDlg::OnOpenbgimage()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("Image(*.BMP,*.JPG,*.PNG)|*.BMP;*.JPG;*.PNG|All Files(*.*)|*.*||")); // ���� ���̾�α׸� �̿��� ���� ����
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
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	doSeamless();
}


void CSeamlessDlg::OnStnClickedShowresult()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString info;
	GetCursorPos(&pt);

	CRect rt;
	// ���� ��Ʈ���� �簢�� ��ǥ�� ����
	// GetClientRect �� ũ�⸦ ���ϴ� GetWindowRect �̿�...
	((CStatic*)GetDlgItem(ID_ShowResult))->GetWindowRect(&rt);

	// GetWindowRect �� ���� ��ǥ�� ��ũ�� ��ǥ(������) �̴� �̸�
	// ȭ�� ��ǥ(����, Ŭ���̾�Ʈ ��ǥ)�� ��ȯ
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CDialogEx::OnMouseMove(nFlags, point);
}


void CSeamlessDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CRect rt;
	// ���� ��Ʈ���� �簢�� ��ǥ�� ����
	// GetClientRect �� ũ�⸦ ���ϴ� GetWindowRect �̿�...
	((CStatic*)GetDlgItem(ID_ShowResult))->GetWindowRect(&rt);

	// GetWindowRect �� ���� ��ǥ�� ��ũ�� ��ǥ(������) �̴� �̸�
	// ȭ�� ��ǥ(����, Ŭ���̾�Ʈ ��ǥ)�� ��ȯ
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialogEx::OnCancel();
}


void CSeamlessDlg::OnWhomade()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	WHOMADE dlg;
	dlg.DoModal();
}
