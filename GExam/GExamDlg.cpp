
// GExamDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "GExam.h"
#include "GExamDlg.h"
#include "afxdialogex.h"
#include <iostream>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

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


// CGExamDlg 대화 상자



CGExamDlg::CGExamDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GEXAM_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_pScreen = NULL;
}

void CGExamDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGExamDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDOK, &CGExamDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BtnDraw, &CGExamDlg::OnBnClickedBtndraw)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CGExamDlg 메시지 처리기

BOOL CGExamDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	CRect rc(0, 0,640, 480);
	m_pScreen = new CScreen();
	m_pScreen->Create(NULL,_T(""), WS_CHILD | WS_VISIBLE | WS_BORDER, rc, this, 0);
	
	nCircleSize = 30;
	SetDlgItemInt(IDC_EDIT_CIRCLE_SIZE, nCircleSize);
	MoveWindow(0, 0, 1280, 800);
	SetWindowText(_T("Draw Example"));
	
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CGExamDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CGExamDlg::OnPaint()
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
HCURSOR CGExamDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CGExamDlg::OnDestroy()
{
	CDialogEx::OnDestroy();


	if (m_pScreen) {
		delete m_pScreen;
	}
	
}


void CGExamDlg::OnBnClickedOk()
{

	CDialogEx::OnOK();
}

bool  CGExamDlg::CheckEditValue(int nValue)
{
	if (nValue >= 10 && nValue <= 100) {
		return true;
	}
	return false;
}
void CGExamDlg::OnBnClickedBtndraw()
{
	CRect rect;

	int nCircleSize = GetDlgItemInt(IDC_EDIT_CIRCLE_SIZE);

	if (!CheckEditValue(nCircleSize)) {
		AfxMessageBox(_T("10에서 100사이 값을 입력하세요 "));
		return;
	}
	if (m_pScreen) {
		m_pScreen->GetWindowRect(&rect);
		m_pScreen->SetCircleSize(nCircleSize);
		m_pScreen->MakePattern(rect.Width(), rect.Height());
	}

}

void CGExamDlg::AdjustPostionControl(UINT nCtrlID, int x, int y, int w,int h, int Gap = 0 )
{
	CRect rect;
	rect.left = x + Gap ;
	rect.top = y;
	rect.right = rect.left + w;
	rect.bottom = rect.top + h;
	GetDlgItem(nCtrlID)->MoveWindow(rect);

}
void CGExamDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	CRect rect;
	
	if (m_pScreen)
	{
	// Screen Area		
		rect.left = 10;
		rect.top = 10;
		rect.right = cx - 10;
		rect.bottom = cy - (20 * 4);
		m_pScreen->MoveWindow(&rect);

		int nTop = rect.bottom + 10;
		int nLeft = rect.left ;
	// Adjust 			
		AdjustPostionControl(IDC_BtnDraw, nLeft, nTop, 200, 40);
		nLeft = nLeft + 200;	
		AdjustPostionControl(IDC_LBL_CIRCLE_SIZE, nLeft, nTop, 100, 40, 10);
		nLeft = nLeft + 100;
		AdjustPostionControl(IDC_EDIT_CIRCLE_SIZE, nLeft, nTop, 100, 40, 10);

	}
	
}
