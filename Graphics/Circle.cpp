#include "pch.h"
#include "Circle.h"

float Circle::getArea() {
	return area;
}

float Circle::getLength() {
	return length;
}

CPoint Circle::getStartPoint() {
	return m_startPoint;
}

CPoint Circle::getOldPoint() {
	return m_OldPoint;
}

void Circle::setStartPoint(CPoint point) {
	m_startPoint = point;
}

void Circle::setOldPoint(CPoint point) {
	m_OldPoint = point;
}

void Circle::OnDraw(CDC* pDC)
{
	int* color = getColor();
	CPen cPen;
	cPen.CreatePen(getLinear(), getLineWidth(), RGB(color[0], color[1], color[2]));

	//擦去上一次绘制的临时圆
	//设定该圆的y坐标，因为要保证两点的x之差等于y之差
	m_OldPoint.y = m_OldPoint.x - m_startPoint.x + m_startPoint.y;
	pDC->Ellipse(CRect(m_startPoint, m_OldPoint));
	
	//绘制临时圆
	currentPoint.y = currentPoint.x - m_startPoint.x + m_startPoint.y;
	pDC->Ellipse(CRect(m_startPoint, currentPoint));

	m_OldPoint = currentPoint;
}