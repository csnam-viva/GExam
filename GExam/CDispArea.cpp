// CDispArea.cpp: 구현 파일
//

#include "pch.h"
#include "GExam.h"
#include "afxdialogex.h"
#include "CDispArea.h"


// CDispArea 대화 상자

IMPLEMENT_DYNAMIC(CDispArea, CDialogEx)

CDispArea::CDispArea(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CDispArea, pParent)
{

}

CDispArea::~CDispArea()
{
}

void CDispArea::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDispArea, CDialogEx)
END_MESSAGE_MAP()


// CDispArea 메시지 처리기


BOOL CDispArea::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	MoveWindow(0, 0, 640, 480);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
