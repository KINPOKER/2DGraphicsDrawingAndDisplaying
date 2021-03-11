#include "pch.h"
#include "RTriangle.h"
#include "math.h"

RTriangle::RTriangle() {
	setName("直角三角形");
	m_startPoint = 0;
	m_OldPoint = 0;
	area = 0;
	length = 0;
}

float RTriangle::getArea(CPoint m_startPoint, CPoint currentPoint)
{
	float l1, l2;
	l1 = abs(currentPoint.x - m_startPoint.x);
	l2 = abs(currentPoint.y - m_startPoint.y);
	area = l1 * l2 / 2;
	return fabs(area);
}

float RTriangle::getLength(CPoint m_startPoint, CPoint currentPoint)
{
	float l1, l2, l3;
	l1 = abs(currentPoint.x - m_startPoint.x);
	l2 = abs(currentPoint.y - m_startPoint.y);
	l3 = sqrt(l1 * l1 + l2 * l2);
	length = l1 + l2 + l3;
	return fabs(length);
}

CPoint RTriangle::getStartPoint() {
	return m_startPoint;
}

CPoint RTriangle::getOldPoint() {
	return m_OldPoint;
}

void RTriangle::setStartPoint(CPoint point) {
	m_startPoint = point;
}

void RTriangle::setOldPoint(CPoint point) {
	m_OldPoint = point;
}

void RTriangle::setDrawPoint(CPoint p1, CPoint p2) {
	pt[0] = p1;
	pt[1].x = p1.x;
	pt[1].y = p2.y;
	pt[2] = p2;
}

void RTriangle::OnDraw(CDC* pDC)
{
	int* color = getColor();
	CPen cPen, * pOldPen;
	cPen.CreatePen(getLinear(), getLineWidth(), RGB(color[0], color[1], color[2]));
	pOldPen = pDC->SelectObject(&cPen);//设置新画笔

	setDrawPoint(m_startPoint, m_OldPoint);
	pDC->Polygon(pt, 3);

	setDrawPoint(m_startPoint, currentPoint);
	pDC->Polygon(pt, 3);

	m_OldPoint = currentPoint;

/*	//显示周长面积
	getLength(m_startPoint, currentPoint);
	getArea(m_startPoint, currentPoint);
	CString str;
	str.Format(CString("周长 = %.2f  面积 = %.2f"), length, area);
	pDC->SetTextColor(RGB(255, 0, 0));
	pDC->TextOutW(50, 300, str);
*/

//设置边界点
	CPoint point2, point4;
	point2.x = currentPoint.x;
	point2.y = m_startPoint.y;
	point4.x = m_startPoint.x;
	point4.y = currentPoint.y;
	setBorderPoint(m_startPoint, point2, currentPoint, point4);
	
	pDC->SelectObject(pOldPen);//恢复旧画笔
}

void RTriangle::OnDraw(CDC* pDC, CPoint newStartPoint, CPoint NewEndPoint)
{
	int* color = getColor();
	CPen cPen, * pOldPen;
	cPen.CreatePen(getLinear(), getLineWidth(), RGB(color[0], color[1], color[2]));
	pOldPen = pDC->SelectObject(&cPen);//设置新画笔

	setDrawPoint(m_startPoint, m_OldPoint);
	pDC->Polygon(pt, 3);
//	Echo(pDC, m_startPoint, m_OldPoint);

	setDrawPoint(newStartPoint, NewEndPoint);
	pDC->Polygon(pt, 3);

	m_startPoint = newStartPoint;
	m_OldPoint = NewEndPoint;

	//显示周长面积
	/*
	getLength(newStartPoint, NewEndPoint);
	getArea(newStartPoint, NewEndPoint);
	CString str;
	str.Format(CString("周长 = %.2f  面积 = %.2f"), length, area);
	pDC->SetTextColor(RGB(255, 0, 0));
	pDC->TextOutW(50, 300, str);
	*/
//	Echo(pDC, newStartPoint, NewEndPoint);

	pDC->SelectObject(pOldPen);//恢复旧画笔
}

void RTriangle::OnDraw(CPoint newStartPoint, CPoint NewEndPoint, CDC* pDC)
{
	int* color = getColor();
	CPen cPen, * pOldPen;
	cPen.CreatePen(getLinear(), getLineWidth(), RGB(color[0], color[1], color[2]));
	pOldPen = pDC->SelectObject(&cPen);//设置新画笔

	setDrawPoint(m_startPoint, m_OldPoint);
	pDC->Polygon(pt, 3);

	setDrawPoint(newStartPoint, NewEndPoint);
	pDC->Polygon(pt, 3);

	m_startPoint = newStartPoint;
	m_OldPoint = NewEndPoint;

	//设置边界点
	CPoint point2, point4;
	point2.x = m_OldPoint.x;
	point2.y = m_startPoint.y;
	point4.x = m_startPoint.x;
	point4.y = m_OldPoint.y;
	setBorderPoint(m_startPoint, point2, m_OldPoint, point4);//

	pDC->SelectObject(pOldPen);//恢复旧画笔
}