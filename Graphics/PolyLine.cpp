#include "pch.h"
#include "PolyLine.h"
#include "math.h"
#include "afxtempl.h"
#include "afxwin.h"

#define MAX 50

using namespace std;

PolyLine::PolyLine()
{
	setName("多折线");
	m_startPoint = 0;
	m_OldPoint = 0;
	ax = 0.00;
	ay = 0.00;
	bx = 0.00;
	by = 0.00;
	cx = 0.00;
	cy = 0.00;
	if ((PtLine = new CPoint[MAX]) == NULL)
	{
		exit(0);
	}
	numPoint = 0;
}

PolyLine::~PolyLine()
{
	delete[] PtLine;
}

float PolyLine::getLength()
{
	float length = 0.00;
	for (int i = 1; i < numPoint; i++)
	{
		length = length + sqrt(pow((PtLine[i - 1].x - PtLine[i].x), 2) + pow((PtLine[i - 1].y - PtLine[i].y), 2));
	}
	return length;
}

void PolyLine::SetPoint(CPoint& point)
{
	PtLine[numPoint] = point;
	numPoint++;
}

//int PolyLine::getPointNumber() {
//	return numPoint;
//}

void PolyLine::OnDraw(CDC* pDC) {
	int* color = getColor();
	CPen cPen;
	cPen.CreatePen(getLinear(), getLineWidth(), RGB(color[0], color[1], color[2]));
	CPen* pOldPen = pDC->SelectObject(&cPen);

	pDC->MoveTo(PtLine[numPoint - 2]);
	pDC->LineTo(PtLine[numPoint - 1]);
	
	pDC->SelectObject(pOldPen);
}

////////////////新增//////////////////

CPoint PolyLine::getStartPoint() {
	return m_startPoint;
}

CPoint PolyLine::getOldPoint() {
	return m_OldPoint;
}

CPoint* PolyLine::FindBorderpoint()
{
	CPoint* brpoint = getBorderPoint();
	int xmin = 9999, xmax = 0, ymin = 9999, ymax = 0;
	for (int i = 0; i < numPoint; i++)
	{
		if (PtLine[i].x < xmin) { xmin = PtLine[i].x; }
		if (PtLine[i].x > xmax) { xmax = PtLine[i].x; }
		if (PtLine[i].y < ymin) { ymin = PtLine[i].y; }
		if (PtLine[i].y > ymax) { ymax = PtLine[i].y; }
	}
	brpoint[0].x = xmin; brpoint[0].y = ymin;
	brpoint[1].x = xmax; brpoint[1].y = ymin;
	brpoint[2].x = xmax; brpoint[2].y = ymax;
	brpoint[3].x = xmin; brpoint[3].y = ymax;

	m_startPoint = brpoint[0];
	m_OldPoint = brpoint[2];

	return brpoint;
}

void PolyLine::OnDraw(CDC* pDC, CPoint newStartPoint, CPoint NewEndPoint)
{
	int* color = getColor();
	CPen cPen, * pOldPen;
	cPen.CreatePen(getLinear(), getLineWidth(), RGB(color[0], color[1], color[2]));
	pOldPen = pDC->SelectObject(&cPen);//设置新画笔

	pDC->Polygon(PtLine, numPoint);
	pDC->MoveTo(PtLine[0]);
	pDC->LineTo(PtLine[numPoint-1]);

	for (int i = 0; i < numPoint; i++)
	{
		PtLine[i].x += newStartPoint.x - m_startPoint.x;
		PtLine[i].y += newStartPoint.y - m_startPoint.y;
	}

	pDC->Polygon(PtLine, numPoint);
	pDC->MoveTo(PtLine[0]);
	pDC->LineTo(PtLine[numPoint - 1]);

	m_startPoint = newStartPoint;
	m_OldPoint = NewEndPoint;

	pDC->SelectObject(pOldPen);//恢复旧画笔
}

void PolyLine::UpdatePtLine() {
	for (int i = 0; i < numPoint; i++)
	{
		PtLine[i].x = newPtLine[i].x;
		PtLine[i].y = newPtLine[i].y;
	}
}

void PolyLine::ScaleOnDraw(CDC* pDC, CPoint newStartPoint, CPoint NewEndPoint)
{
	int* color = getColor();
	CPen cPen, * pOldPen;
	cPen.CreatePen(getLinear(), getLineWidth(), RGB(color[0], color[1], color[2]));
	pOldPen = pDC->SelectObject(&cPen);

	CPoint* brpoint = getBorderPoint();
	float x[999] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	float y[999] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	ax = brpoint[2].x - brpoint[0].x;
	ay = brpoint[2].y - brpoint[0].y;
	bx = NewEndPoint.x - newStartPoint.x;
	by = NewEndPoint.y - newStartPoint.y;
	cx = m_OldPoint.x - m_startPoint.x;
	cy = m_OldPoint.y - m_startPoint.y;

	for (int i = 0; i < numPoint; i++)
	{
		x[i] = (float)(PtLine[i].x - brpoint[0].x) * cx / ax + m_startPoint.x;
		y[i] = (float)(PtLine[i].y - brpoint[0].y) * cy / ay + m_startPoint.y;
		newPtLine[i].x = x[i];
		newPtLine[i].y = y[i];
	}

	pDC->Polygon(newPtLine, numPoint);
	pDC->MoveTo(newPtLine[0]);
	pDC->LineTo(newPtLine[numPoint - 1]);

	for (int i = 0; i < numPoint; i++)
	{
		x[i] = (float)(PtLine[i].x - brpoint[0].x) * bx / ax + newStartPoint.x;
		y[i] = (float)(PtLine[i].y - brpoint[0].y) * by / ay + newStartPoint.y;
		newPtLine[i].x = x[i];
		newPtLine[i].y = y[i];
	}

	pDC->Polygon(newPtLine, numPoint);
	pDC->MoveTo(newPtLine[0]);
	pDC->LineTo(newPtLine[numPoint - 1]);

	m_startPoint = newStartPoint;
	m_OldPoint = NewEndPoint;

	//Echo( pDC, brpoint[0], brpoint[2]);

	pDC->SelectObject(pOldPen);
}

void PolyLine::Rotate(CDC* pDC)
{
	int* color = getColor();
	CPen cPen, * pOldPen;
	cPen.CreatePen(getLinear(), getLineWidth(), RGB(color[0], color[1], color[2]));
	pOldPen = pDC->SelectObject(&cPen);//设置新画笔

	pDC->Polygon(PtLine, numPoint);
	pDC->MoveTo(PtLine[0]);
	pDC->LineTo(PtLine[numPoint - 1]);

	CPoint* borderPoint1 = getBorderPoint();
	CPoint CenterPoint;
	CPoint newPtLine[50];
	CenterPoint.x = abs(borderPoint1[0].x + borderPoint1[2].x) / 2;
	CenterPoint.y = abs(borderPoint1[0].y + borderPoint1[2].y) / 2;//计算旋转中心

	for (int i = 0; i < numPoint; i++)
	{
		newPtLine[i].x = PtLine[i].y - CenterPoint.y + CenterPoint.x;
		newPtLine[i].y = CenterPoint.x - PtLine[i].x + CenterPoint.y;
	}	//计算旋转后的点
	for (int i = 0; i < numPoint; i++)
	{
		PtLine[i] = newPtLine[i];
	}  
	pDC->Polygon(PtLine, numPoint);
	pDC->MoveTo(PtLine[0]);
	pDC->LineTo(PtLine[numPoint - 1]);//画出旋转后的图形

	//CPoint* brpoint = FindBorderpoint();
	//setBorderPoint(brpoint[0], brpoint[1], brpoint[2], brpoint[3]);
	setBorderPoint(borderPoint1[0], borderPoint1[1], borderPoint1[2], borderPoint1[3]);
	pDC->SelectObject(pOldPen);
}