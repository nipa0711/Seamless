// WHOMADE.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Seamless.h"
#include "WHOMADE.h"
#include "afxdialogex.h"


// WHOMADE 대화 상자입니다.

IMPLEMENT_DYNAMIC(WHOMADE, CDialogEx)

WHOMADE::WHOMADE(CWnd* pParent /*=NULL*/)
	: CDialogEx(WHOMADE::IDD, pParent)
{

}

WHOMADE::~WHOMADE()
{
}

void WHOMADE::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(WHOMADE, CDialogEx)
END_MESSAGE_MAP()


// WHOMADE 메시지 처리기입니다.
