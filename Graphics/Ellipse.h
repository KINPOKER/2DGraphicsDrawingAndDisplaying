#pragma once
#include "AreaShape.h"

class Ellipses : public AreaShape
{
private:
	CPoint m_startPoint;
	CPoint m_OldPoint;
	float area;
	float length;
	float a;
	float b;

public:
	Ellipses();

	static int nEllipse;
	float getLength(CPoint m_startPoint, CPoint currentPoint);
	float getArea(CPoint m_startPoint, CPoint currentPoint);
	CPoint getStartPoint();
	CPoint getOldPoint();
	float getmaxaxit(CPoint m_startPoint, CPoint currentPoint);
	float getminaxit(CPoint m_startPoint, CPoint currentPoint);

	void setStartPoint(CPoint point);
	void setOldPoint(CPoint point);

	void OnDraw(CDC* pDC);
	void OnDraw(CDC* pDC, CPoint newStartPoint, CPoint NewEndPoint);

	void OnDraw(CPoint newStartPoint, CPoint NewEndPoint, CDC* pDC);
};
