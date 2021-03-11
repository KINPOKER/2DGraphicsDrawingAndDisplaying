#pragma once
#include "AreaShape.h"

class Circle : public AreaShape
{
private:
	CPoint m_startPoint;
	CPoint m_OldPoint;
	float area;
	float length;
	float r;

public:
	Circle();

	static int nCircle;
	float getLength(CPoint m_startPoint, CPoint currentPoint);
	float getArea(CPoint m_startPoint, CPoint currentPoint);
	CPoint getStartPoint();
	CPoint getOldPoint();

	void setStartPoint(CPoint point);
	void setOldPoint(CPoint point);

	void OnDraw(CDC* pDC);
	void OnDraw(CDC* pDC, CPoint newStartPoint, CPoint NewEndPoint);
};


