#pragma once


// CScreen
#define MAX_POINT	20

class CScreen : public CWnd
{
	DECLARE_DYNAMIC(CScreen)

private:

	CRect   m_circleRect[MAX_POINT];
	CImage  m_image;

	int     m_nCircleSize;
	int		m_nThresHold;
	int	    m_nDataCount = 0;
	void	DrawData(CDC* pDC);
	void	CreateImage(int nWith, int nHeight);
	void	MakeData();
	bool    IsInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius);
	void    GetCenterXY(CRect rect, int nRadius, double* nCenterX, double* nCenterY);
	void    DrawCross(CDC* pDC, double dCenterX, double dCenterY);
	void	DrawCircle(CDC* pDC, CRect rect);
	
public:
	CScreen();
	virtual ~CScreen();
	void  SetCircleSize(int nSize);
	void  MakePattern(int nWidth, int nHeight);
	

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};


