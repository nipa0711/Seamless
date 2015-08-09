
// SeamlessDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"


// CSeamlessDlg ��ȭ ����
class CSeamlessDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CSeamlessDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SEAMLESS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnExit();
	afx_msg void OnOpenbgimage();
	Mat bgMat, insideMat, resultMat;
	CStatic ShowBGFrame;
	CDC *pDC1, *pDC2, *pDC3;
	HDC hDC1, hDC2, hDC3;
	CvvImage m_CVvImageObj1, m_CVvImageObj2, m_CVvImageObj3;
	IplImage IplImage1, IplImage2, IplImage3;
	CRect rect, rect2, rect3;
	int showBGWidth;
	int showBGHeight;

	int showInsideWidth;
	int showInsideHeight;

	int showResultWidth;
	int showResultHeight;

	string CStrToStr(CString str);
	CBitmap* IplImageToCBitmap(IplImage* img);
	CStatic ShowInsideFrame;
	CStatic ShowResultFrame;
	afx_msg void OnOpeninsideimage();

	void doSeamless();
	afx_msg void OnFilesave();
	afx_msg void OnRedraw();
	afx_msg void OnStnClickedShowresult();

	POINT pt;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedCancel();
	afx_msg void OnWhomade();
};
