#include "pch.h"
#include "Rectangle.h"


float Rectangles::getArea() {
	width = currentPoint.x - m_startPoint.x;
	extent = currentPoint.y - m_startPoint.y;
	area = width * extent;

	return area;
}

float Rectangles::getLength() {
	width = currentPoint.x - m_startPoint.x;
	extent = currentPoint.y - m_startPoint.y;
	length = (width + extent) * 2;
		
	return length;
}

CPoint Rectangles::getStartPoint() {
	return m_startPoint;
}

CPoint Rectangles::getOldPoint() {
	return m_OldPoint;
}

void Rectangles::setStartPoint(CPoint point) {
	m_startPoint = point;
}

void Rectangles::setOldPoint(CPoint point) {
	m_OldPoint = point;
}

void Rectangles::OnDraw(CDC* pDC)
{
	int* color = getColor();
	CPen cPen;
	cPen.CreatePen(getLinear(), getLineWidth(), RGB(color[0], color[1], color[2]));

	pDC->Rectangle(CRect(m_startPoint, m_OldPoint));
	pDC->Rectangle(CRect(m_startPoint, currentPoint));
	m_OldPoint = currentPoint;

	//显示周长面积
	getLength();
	getArea();
	CString str;
	str.Format(CString("长度 = %.2f  宽度 = %.2f 周长 = %.2f  面积 = %.2f"), extent, width, length, area);
	pDC->SetTextColor(RGB(255, 0, 0));
	pDC->TextOutW(50, 300, str);

}