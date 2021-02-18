#include "pch.h"
#include "RTriangle.h"
#include "math.h"

float RTriangle::getArea() {
	float l1, l2;
	l1 = currentPoint.x - m_startPoint.x;
	l2 = currentPoint.y - m_startPoint.y;
	area = l1 * l2 / 2;
	return area;
}

float RTriangle::getLength() {
	float l1, l2, l3;
	l1 = currentPoint.x - m_startPoint.x;
	l2 = currentPoint.y - m_startPoint.y;
	l3 = sqrt(l1 * l1 + l2 * l2);
	length = l1 + l2 + l3;
	return length;
}

CPoint RTriangle::getStartPoint() {
	return m_startPoint;
}

CPoint RTriangle::getOldPoint() {
	return m_OldPoint;
}

void RTriangle::getDrawPoint() {
	pt[0] = m_startPoint;
	pt[1].x = m_startPoint.x;
	pt[1].y = currentPoint.y;
	pt[2] = currentPoint;
}

void RTriangle::setStartPoint(CPoint point) {
	m_startPoint = point;
}

void RTriangle::setOldPoint(CPoint point) {
	m_OldPoint = point;
}

void RTriangle::OnDraw(CDC* pDC)
{
	int* color = getColor();
	CPen cPen, * pOldPen;
	cPen.CreatePen(getLinear(), getLineWidth(), RGB(color[0], color[1], color[2]));
	pOldPen = pDC->SelectObject(&cPen);//设置新画笔

	pt[0] = m_startPoint;
	pt[1].x = m_startPoint.x;
	pt[1].y = m_OldPoint.y;
	pt[2] = m_OldPoint;
	pDC->Polygon(pt, 3);

	getDrawPoint();
	pDC->Polygon(pt, 3);

	nRTriangle++;	//画布中RTriangle数量+1

	m_OldPoint = currentPoint;

	//显示周长面积
	getLength();
	getArea();
	CString str;
	str.Format(CString("周长 = %.2f  面积 = %.2f"), length, area);
	pDC->SetTextColor(RGB(255, 0, 0));
	pDC->TextOutW(50, 300, str);

	pDC->SelectObject(pOldPen);//恢复旧画笔
}

void RTriangle::Echo(CDC* pDC)
{
	for (int i = 0; i < 3; i++)
	{
		CString str;
		str.Format(CString("x = %d, y = %d"), pt[i].x, pt[i].y);
		pDC->SetTextColor(RGB(255, 0, 0));
		pDC->TextOutW(pt[i].x, pt[i].y, str);	// 回显
		pDC->Rectangle(pt[i].x - 5, pt[i].y - 5, pt[i].x + 5, pt[i].y + 5);
	}
}
