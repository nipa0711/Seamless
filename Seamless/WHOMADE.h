#pragma once


// WHOMADE ��ȭ �����Դϴ�.

class WHOMADE : public CDialogEx
{
	DECLARE_DYNAMIC(WHOMADE)

public:
	WHOMADE(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~WHOMADE();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
