// CScreen.cpp: 구현 파일
//

#include "pch.h"
#include "GExam.h"
#include "CScreen.h"
#include <iostream>
using namespace std;


#define COLOR_RED		RGB(0xff, 0x00, 0x00)
#define COLOR_GREEN		RGB(0x00, 0xff, 0x00)
#define COLOR_BLUE		RGB(0x00, 0x00, 0xff)
#define COLOR_WHITE		RGB(0xff, 0xff, 0xff)
#define COLOR_BLACK		RGB(0x00, 0x00, 0x00)
#define COLOR_YELLOW	RGB(0xff, 0xff, 0x00)

// CScreen

IMPLEMENT_DYNAMIC(CScreen, CWnd)

CScreen::CScreen()
{
	m_nCircleSize = 0;
	//memset(m_nCircleSize, 0, sizeof(m_nCircleSize));
}

CScreen::~CScreen()
{
}


BEGIN_MESSAGE_MAP(CScreen, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CScreen 메시지 처리기

void CScreen::OnPaint()
{
	CPaintDC dc(this);
	if (m_image) {
		m_image.Draw(dc, 0, 0);
		DrawData(&dc);

	//CPaintDC dc(this); // device context for painting
	 //   CBrush backBrush(COLOR_BLACK);
	 //   CBrush* pPrevBrush = dc.SelectObject(&backBrush);
	 //   CRect rect;
	 //   dc.GetClipBox(&rect);
		////TRACE("GetClipBox =%d, %d ,%d, %d \n ", rect.left, rect.top, rect.Width(), rect.Height());
		//dc.PatBlt(rect.left, rect.top, rect.Width(), rect.Height(), PATCOPY);
	 //   dc.SelectObject(backBrush);
	 //   
		//DrawCicle(&dc, 10);
		
	}
		
}

void CScreen::DrawData(CDC* pDC)
{
	double dCenterX = 0;
	double dCenterY = 0;


	for (int k = 0; k < MAX_POINT; k++) {

		DrawCircle(pDC, m_circleRect[k]);
		GetCenterXY(m_circleRect[k], m_nCircleSize, &dCenterX, &dCenterY);
		DrawCross(pDC, dCenterX, dCenterY);

	}


}
void CScreen::DrawCircle(CDC* pDC, CRect rect )
{
	CBrush blackBrush(RGB(0, 0, 0));
	CPen yellow_pen(PS_SOLID, 1, COLOR_YELLOW);
	CBrush* pOldBrush = pDC->SelectObject(&blackBrush);
	CPen* pOldPen = pDC->SelectObject(&yellow_pen);
	
		//rect.SetRect(m_ptData[i], m_ptData[i]);
		//rect.InflateRect(m_nCircleSize, m_nCircleSize);
	pDC->Ellipse(rect);
	pDC->SelectObject(&pOldBrush);
	pDC->SelectObject(&pOldPen);

}
void CScreen::DrawCross(CDC* pDC, double dCenterX, double dCenterY)
{
	CPen pen;
	pen.CreatePen(PS_SOLID, 2, COLOR_RED);
	
	CPen* pOldPen = pDC->SelectObject(&pen);
	pDC->MoveTo(dCenterX - 5, dCenterY);
	pDC->LineTo(dCenterX + 5, dCenterY);
	pDC->MoveTo(dCenterX, dCenterY - 5);
	pDC->LineTo(dCenterX, dCenterY + 5);
	pDC->SelectObject(pOldPen);

}
void CScreen::GetCenterXY(CRect rect, int nRadius, double* dCenterX, double* dCenterY)
{
	int nSumX = 0;
	int nSumY = 0;
	int nCount = 0;
	long nWeight = 0;
	int x, y = 0;
	int nTH = 0x80;
	unsigned char* fm = (unsigned char*)m_image.GetBits();
	int nPitch = m_image.GetPitch();

	for (int j = rect.top; j < rect.bottom; j++)
	{
		for (int i = rect.left; i < rect.right; i++)
		{
			
			x = i - rect.left;
			y = j - rect.top;
			if (IsInCircle(x, y, m_nCircleSize, m_nCircleSize, m_nCircleSize))
			{
				//if (fm[j * nPitch + i] > nTH)
				{
					nSumX += i;
					nSumY += j;
					nCount++;
				}
			}
		}
	}
	*dCenterX = (double)nSumX / nCount;
	*dCenterY = (double)nSumY / nCount;
	cout << "XY" << *dCenterX << "\t" << *dCenterY << endl;
}
bool CScreen::IsInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius)
{
	bool bRet = false;

	double dX = i - nCenterX;
	double dY = j - nCenterY;
	double dDist = dX * dX + dY * dY;

	if (dDist < nRadius * nRadius) {
		bRet = true;
	}

	return bRet;
}


//void CScreen::MakeCenter(, int radius)
//{
//	for (int x = centerX - radius; x <= centerX + radius; x++)
//	{
//		for (int y = centerY - radius; y <= centerY + radius; y++)
//		{
//			int distance = (x - centerX) * (x - centerX) + (y - centerY) * (y - centerY);
//			if (distance <= radius * radius)
//			{
//				TRACE("x =%d, y=%d ", x, y);
//				pDC->SetPixel(x, y, RGB(255, 0, 0));
//			}
//		}
//	}
//
//}

void CScreen::DrawCicle(CDC* pDC,int nSize)
{
	//CRect clientRect;
	//CPen* pOldPen;
	//CPen yellow_pen(PS_SOLID, 1, COLOR_YELLOW);
	//GetClientRect(&clientRect);

	//int centerX = clientRect.Width() / 2;
	//int centerY = clientRect.Height() / 2;
	//int radius = 30;

	//pOldPen = pDC->SelectObject(&yellow_pen);
	//pDC->Ellipse(centerX - radius, centerY - radius, centerX + radius, centerY + radius);

	//for (int x = centerX - radius; x <= centerX + radius; x++)
	//{
	//	for (int y = centerY - radius; y <= centerY + radius; y++)
	//	{
	//		int distance = (x - centerX) * (x - centerX) + (y - centerY) * (y - centerY);
	//		if (distance <= radius * radius)
	//		{
	//			/*CString str;
	//			str.Format(_T("(%d, %d)"), x, y);
	//			TRACE("x =%d, y=%d ",x, y);
	//			pDC->SetPixel(x, y, RGB(255, 0, 0));*/
	//		}
	//	}
	//}
}
void CScreen::SetCircleSize(int nSize)
{
	m_nCircleSize = nSize;
}
void CScreen::MakePattern(int nWidth, int nHeight)
{
	
	CreateImage(nWidth, nHeight);
	MakeData();
	Invalidate();

}

int CScreen::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	return 0;
}

void CScreen::CreateImage(int ww, int hh)
{
	int nWidth = ww;
	int nHeight = hh;
	int nBpp = 8;

	if (m_image)
		m_image.Destroy();
	m_image.Create(nWidth, -nHeight, nBpp);
	if (nBpp == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		m_image.SetColorTable(0, 256, rgb);
	}

	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	memset(fm, 0x00, nWidth * nHeight);

}

void CScreen::MakeData()
{
	int nIndex = 0;
	srand((unsigned int)(time(NULL)));

	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	for (int k = 0; k < MAX_POINT; k++) {
		int x = rand() % nWidth;
		int y = rand() % nHeight;
		int rectsize = m_nCircleSize * 2;

		x = (x + rectsize) > nWidth ? x - rectsize : x;
		y = (y + rectsize) > nHeight ? y - rectsize : y;
		m_nDataCount = ++nIndex;
		m_circleRect[k].SetRect(x,y, x+ rectsize, y + rectsize);

		//for (int j = y; j < y + rectsize; j++) {
		//	for (int i = x; i < x + rectsize; i++) {
		//		fm[j* nPitch + i] = 0x81; // rand() % 0xff;
		//	}
		//}
	
		//cout <<  x  << "," <<  y << ":" << fm[y * nWidth + x] << endl;
	}
	

}

void CScreen::OnDestroy()
{
	CWnd::OnDestroy();

	m_image.Destroy();
}


BOOL CScreen::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CBrush bgBrush(RGB(0, 0, 0));
	CRect rect;
	pDC->GetClipBox(&rect);
	pDC->FillRect(&rect, &bgBrush);
	return CWnd::OnEraseBkgnd(pDC);
}
