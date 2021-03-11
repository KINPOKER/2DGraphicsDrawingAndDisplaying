#include "pch.h"
#include "Rectangle.h"

Rectangles::Rectangles() {
	setName("¾ØÐÎ");
	m_startPoint = 0;
	m_OldPoint = 0;
	area = 0;
	length = 0;
	width = 0;
	extent = 0;
}

float Rectangles::getArea(CPoint m_startPoint, CPoint currentPoint)
{
	width = abs(currentPoint.x - m_startPoint.x);
	extent = abs(currentPoint.y - m_startPoint.y);
	area = width * extent;

	return fabs(area);
}

float Rectangles::getLength(CPoint m_startPoint, CPoint currentPoint)
{
	width = abs(currentPoint.x - m_startPoint.x);
	extent = abs(currentPoint.y - m_startPoint.y);
	length = (width + extent) * 2;
		
	return fabs(length);
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
	CPen* pOldPen = pDC->SelectObject(&cPen);

	pDC->Rectangle(CRect(m_startPoint, m_OldPoint));
	pDC->Rectangle(CRect(m_startPoint, currentPoint));
	m_OldPoint = currentPoint;
	
	pDC->SelectObject(pOldPen);

	CPoint point2, point4;
	point2.x = currentPoint.x;
	point2.y = m_startPoint.y;
	point4.x = m_startPoint.x;
	point4.y = currentPoint.y;
	setBorderPoint(m_startPoint, point2, currentPoint, point4);
}

void Rectangles::OnDraw(CDC* pDC, CPoint newStartPoint, CPoint NewEndPoint)
{
	int* color = getColor();
	CPen cPen, * pOldPen;
	cPen.CreatePen(getLinear(), getLineWidth(), RGB(color[0], color[1], color[2]));
	pOldPen = pDC->SelectObject(&cPen);//ÉèÖÃÐÂ»­±Ê

	pDC->Rectangle(CRect(m_startPoint, m_OldPoint));

	pDC->Rectangle(CRect(newStartPoint, NewEndPoint));

	m_startPoint = newStartPoint;
	m_OldPoint = NewEndPoint;

	pDC->SelectObject(pOldPen);//»Ö¸´¾É»­±Ê
}

void Rectangles::OnDraw(CPoint newStartPoint, CPoint NewEndPoint, CDC* pDC)
{
	int* color = getColor();
	CPen cPen, * pOldPen;
	cPen.CreatePen(getLinear(), getLineWidth(), RGB(color[0], color[1], color[2]));
	pOldPen = pDC->SelectObject(&cPen);//ÉèÖÃÐÂ»­±Ê

	pDC->Rectangle(CRect(m_startPoint, m_OldPoint));

	pDC->Rectangle(CRect(newStartPoint, NewEndPoint));

	m_startPoint = newStartPoint;
	m_OldPoint = NewEndPoint;

	//ÉèÖÃ±ß½çµã
	CPoint point2, point4;
	point2.x = m_startPoint.x;
	point2.y = m_OldPoint.y;
	point4.x = m_OldPoint.x;
	point4.y = m_startPoint.y;
	setBorderPoint(point2, m_OldPoint, point4, m_startPoint);

	pDC->SelectObject(pOldPen);//»Ö¸´¾É»­±Ê

}