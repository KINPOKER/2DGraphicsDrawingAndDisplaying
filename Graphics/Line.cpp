#include "pch.h"
#include "Line.h"
#include "math.h"

Line::Line() {
	setName("Ïß¶Î");
	firstPoint = 0;
	endPoint = 0;
	length = 0.0;
}

float Line::getLength() {
	length = sqrt(pow((currentPoint.x - firstPoint.x), 2) + pow((currentPoint.y - firstPoint.y), 2));
	return length;
}

CPoint Line::getFirstPoint() {
	return firstPoint;
}

CPoint Line::getEndPoint() {
	return endPoint;
}

//CPoint Line::getCurrentPoint()
//{
//	return currentPoint;
//}

void Line::setFirstPoint(CPoint point) 
{
	
	firstPoint = point;

}
void Line::setEndPoint(CPoint point) 
{
	endPoint = point;
}

void Line::OnDraw(CDC* pDC) {
	int* color = getColor();
	CPen cPen;
	cPen.CreatePen(getLinear(), getLineWidth(), RGB(color[0], color[1], color[2]));
	CPen* pOldPen = pDC->SelectObject(&cPen);

	pDC->MoveTo(firstPoint);
	pDC->LineTo(endPoint);
	pDC->MoveTo(firstPoint);
	pDC->LineTo(currentPoint);

	endPoint = currentPoint;

	//ÉèÖÃ±ß½çµã
	CPoint point2, point4;
	point2.x = currentPoint.x;
	point2.y = firstPoint.y;
	point4.x = firstPoint.x;
	point4.y = currentPoint.y;
	setBorderPoint(firstPoint, point2, currentPoint, point4);
	
	pDC->SelectObject(pOldPen);
}

void Line::OnDraw(CDC* pDC, CPoint newStartPoint, CPoint NewEndPoint)
{
	int* color = getColor();
	CPen cPen, * pOldPen;
	cPen.CreatePen(getLinear(), getLineWidth(), RGB(color[0], color[1], color[2]));
	pOldPen = pDC->SelectObject(&cPen);//ÉèÖÃÐÂ»­±Ê

	pDC->MoveTo(firstPoint);
	pDC->LineTo(endPoint);

	pDC->MoveTo(newStartPoint);
	pDC->LineTo(NewEndPoint);

	firstPoint = newStartPoint;
	endPoint = NewEndPoint;

	pDC->SelectObject(pOldPen);//»Ö¸´¾É»­±Ê
}

void Line::OnDraw(CPoint newStartPoint, CPoint NewEndPoint, CDC* pDC)
{
	int* color = getColor();
	CPen cPen, * pOldPen;
	cPen.CreatePen(getLinear(), getLineWidth(), RGB(color[0], color[1], color[2]));
	pOldPen = pDC->SelectObject(&cPen);//ÉèÖÃÐÂ»­±Ê

	pDC->MoveTo(firstPoint);
	pDC->LineTo(endPoint);

	pDC->MoveTo(newStartPoint);
	pDC->LineTo(NewEndPoint);

	firstPoint = newStartPoint;
	endPoint = NewEndPoint;

	//ÉèÖÃ±ß½çµã
	CPoint point2, point4;
	/*point2.x = endPoint.x;
	point2.y = firstPoint.y;
	point4.x = firstPoint.x;
	point4.y = endPoint.y;
	setBorderPoint(firstPoint, point2, endPoint, point4);*/

	point2.x = endPoint.x;
	point2.y = firstPoint.y;
	point4.x = firstPoint.x;
	point4.y = endPoint.y;
	setBorderPoint(endPoint, point4, firstPoint, point2);

	pDC->SelectObject(pOldPen);//»Ö¸´¾É»­±Ê
}