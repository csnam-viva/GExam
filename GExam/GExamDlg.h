
// GExamDlg.h: 헤더 파일
//

#pragma once

#include "CScreen.h"

// CGExamDlg 대화 상자
class CGExamDlg : public CDialogEx
{
// 생성입니다.
public:
	CGExamDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GEXAM_DIALOG };
#endif

	CScreen* m_pScreen;
	int		nCircleSize;

	void   AdjustPostionControl(UINT nType, int x, int y, int w, int h, int Gap);
	bool   CheckEditValue(int nValue);

	
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBtndraw();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
