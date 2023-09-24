#pragma once
#include "afxdialogex.h"


// CDispArea 대화 상자

class CDispArea : public CDialogEx
{
	DECLARE_DYNAMIC(CDispArea)

public:
	CDispArea(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDispArea();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CDispArea };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
