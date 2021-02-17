#include "pch.h"
#include "Triangle.h"
#include "math.h"

float Triangle::getArea() {
	area = abs(Point[0].x * Point[1].y + Point[1].x * Point[2].y + Point[2].x * Point[0].y
		- Point[0].y * Point[1].x - Point[1].y * Point[2].x - Point[2].y * Point[0].x) / 2;
	return area;
}

float Triangle::getLength() {
	double l1, l2, l3;
	l1 = sqrt(pow(Point[0].x - Point[1].x, 2) + pow(Point[0].y - Point[1].y, 2));
	l2 = sqrt(pow(Point[1].x - Point[2].x, 2) + pow(Point[1].y - Point[2].y, 2));
	l3 = sqrt(pow(Point[2].x - Point[0].x, 2) + pow(Point[2].y - Point[0].y, 2));
	length = l1 + l2 + l3;
	return length;
}

void Triangle::setPoint(CPoint point)
{
	if (nCount == 3)
	{
		nCount = 0;
	}
	Point[nCount] = point;
	nCount++;
}

//void Triangle::setMiddlePoint(CPoint point)
//{
//	Point[1] = point;
//}
//
//void Triangle::setEndPoint(CPoint point)
//{
//	Point[2] = point;
//}

void Triangle::OnDraw(CDC* pDC)
{
	int* color = getColor();
	CPen cPen, * pOldPen;
	cPen.CreatePen(getLinear(), getLineWidth(), RGB(color[0], color[1], color[2]));
	pOldPen = pDC->SelectObject(&cPen);

	//画点
	for (int i = 0; i <= nCount; i++)
	{
		CString str;
		str.Format(CString("x = %d, y = %d"), Point[i].x, Point[i].y);
		pDC->SetTextColor(RGB(255, 0, 0));
		pDC->TextOutW(Point[i].x, Point[i].y, str);	// 回显
		pDC->Rectangle(Point[i].x - 5, Point[i].y - 5, Point[i].x + 5, Point[i].y + 5);
	}

	//画三角形并显示周长面积
	if (nCount == 2)
	{
		for (int i = 0; i < 3; i++)
		{
			if (0 == i)
				pDC->MoveTo(Point[i]);
			else
				pDC->LineTo(Point[i]);
		}
		pDC->LineTo(Point[0]);

		//显示周长面积
		getLength();
		getArea();
		CString str;
		str.Format(CString("周长 = %.2f  面积 = %.2f"), length, area);
		pDC->SetTextColor(RGB(255, 0, 0));
		pDC->TextOutW(50, 300, str);
		//Point[2] = currentPoint;
	}
	pDC->SelectObject(pOldPen);
}