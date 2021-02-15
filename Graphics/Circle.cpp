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

	//��ȥ��һ�λ��Ƶ���ʱԲ
	//�趨��Բ��y���꣬��ΪҪ��֤�����x֮�����y֮��
	m_OldPoint.y = m_OldPoint.x - m_startPoint.x + m_startPoint.y;
	pDC->Ellipse(CRect(m_startPoint, m_OldPoint));
	
	//������ʱԲ
	currentPoint.y = currentPoint.x - m_startPoint.x + m_startPoint.y;
	pDC->Ellipse(CRect(m_startPoint, currentPoint));

	m_OldPoint = currentPoint;
}