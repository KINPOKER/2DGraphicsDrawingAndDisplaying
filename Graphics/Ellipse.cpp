#include "pch.h"
#include "Ellipse.h"

Ellipses::Ellipses() {
	setName("Õ÷‘≤");
	m_startPoint = 0;
	m_OldPoint = 0;
	area = 0;
	length = 0;
	a = 0;
	b = 0;
}

float Ellipses::getArea(CPoint m_startPoint, CPoint currentPoint)
{
	a = abs(currentPoint.x - m_startPoint.x);
	b = abs(currentPoint.y - m_startPoint.y);
	area = a * b * PI;

	return fabs(area);
}

float Ellipses::getLength(CPoint m_startPoint, CPoint currentPoint)
{
	a = abs(currentPoint.x - m_startPoint.x);
	b = abs(currentPoint.y - m_startPoint.y);
	if (b < a)
	{
		length = 2 * PI * b + (a - b) * 4;
	}
	else
	{
		length = 2 * PI * a + (b - a) * 4;
	}
	return fabs(length);
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
	CPen* pOldPen = pDC->SelectObject(&cPen);

	pDC->Ellipse(CRect(m_startPoint, m_OldPoint));
	pDC->Ellipse(CRect(m_startPoint, currentPoint));

	m_OldPoint = currentPoint;

	pDC->SelectObject(pOldPen);


//…Ë÷√±ﬂΩÁµ„
	CPoint point2, point4;
	point2.x = currentPoint.x;
	point2.y = m_startPoint.y;
	point4.x = m_startPoint.x;
	point4.y = currentPoint.y;
	setBorderPoint(m_startPoint, point2, currentPoint, point4);
}

float Ellipses::getmaxaxit(CPoint m_startPoint, CPoint currentPoint)
{
	a = currentPoint.x - m_startPoint.x;
	b = currentPoint.y - m_startPoint.y;
	return a > b ? fabs(a) : fabs(b);
}

float Ellipses::getminaxit(CPoint m_startPoint, CPoint currentPoint)
{
	a = currentPoint.x - m_startPoint.x;
	b = currentPoint.y - m_startPoint.y;
	return a > b ? fabs(b) : fabs(a);
}

void Ellipses::OnDraw(CDC* pDC, CPoint newStartPoint, CPoint NewEndPoint)
{
	int* color = getColor();
	CPen cPen, * pOldPen;
	cPen.CreatePen(getLinear(), getLineWidth(), RGB(color[0], color[1], color[2]));
	pOldPen = pDC->SelectObject(&cPen);//…Ë÷√–¬ª≠± 


	pDC->Ellipse(CRect(m_startPoint, m_OldPoint));

	pDC->Ellipse(CRect(newStartPoint, NewEndPoint));

	m_startPoint = newStartPoint;
	m_OldPoint = NewEndPoint;

	pDC->SelectObject(pOldPen);//ª÷∏¥æ…ª≠± 
}

void Ellipses::OnDraw(CPoint newStartPoint, CPoint NewEndPoint, CDC* pDC)
{
	int* color = getColor();
	CPen cPen, * pOldPen;
	cPen.CreatePen(getLinear(), getLineWidth(), RGB(color[0], color[1], color[2]));
	pOldPen = pDC->SelectObject(&cPen);//…Ë÷√–¬ª≠± 


	pDC->Ellipse(CRect(m_startPoint, m_OldPoint));

	pDC->Ellipse(CRect(newStartPoint, NewEndPoint));

	m_startPoint = newStartPoint;
	m_OldPoint = NewEndPoint;

	//…Ë÷√±ﬂΩÁµ„
	CPoint point2, point4;
	point2.x = m_startPoint.x;
	point2.y = m_OldPoint.y;
	point4.x = m_OldPoint.x;
	point4.y = m_startPoint.y;
	setBorderPoint(point2, m_OldPoint, point4, m_startPoint);

	pDC->SelectObject(pOldPen);//ª÷∏¥æ…ª≠± 
}
