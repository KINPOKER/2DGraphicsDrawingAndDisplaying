#include "pch.h"
#include "Ellipse.h"

float Ellipses::getArea() {
	a = currentPoint.x - m_startPoint.x;
	b = currentPoint.y - m_startPoint.y;
	area = a * b * PI;

	return area;
}

float Ellipses::getLength() {
	a = currentPoint.x - m_startPoint.x;
	b = currentPoint.y - m_startPoint.y;
	if (b<a)
	{
		length = 2 * PI * b + (a - b) * 4;
	}
	else
	{
		length = 2 * PI * a + (b - a) * 4;
	}

	return length;
}

CPoint Ellipses::getStartPoint() {
	return m_startPoint;
}

CPoint Ellipses::getOldPoint() {
	return m_OldPoint;
}

void Ellipses::setStartPoint(CPoint point) {
	m_startPoint = point;
}

void Ellipses::setOldPoint(CPoint point) {
	m_OldPoint = point;
}

void Ellipses::OnDraw(CDC* pDC)
{
	int* color = getColor();
	CPen cPen;
	cPen.CreatePen(getLinear(), getLineWidth(), RGB(color[0], color[1], color[2]));
	pDC->SelectObject(&cPen);

	pDC->Ellipse(CRect(m_startPoint, m_OldPoint));
	pDC->Ellipse(CRect(m_startPoint, currentPoint));

	m_OldPoint = currentPoint;

	//显示周长面积
	getLength();
	getArea();
	CString str;
	if (b < a)
	{
		str.Format(CString("长半轴 = %.2f  短半轴 = %.2f  周长 = %.2f  面积 = %.2f"), a, b, length, area);
	}
	else
	{
		str.Format(CString("长半轴 = %.2f  短半轴 = %.2f  周长 = %.2f  面积 = %.2f"), b, a, length, area);
	}
	pDC->SetTextColor(RGB(255, 0, 0));
	pDC->TextOutW(50, 300, str);
}
