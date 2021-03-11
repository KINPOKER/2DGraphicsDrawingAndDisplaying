#pragma once
#include "AreaShape.h"
class ITriangle :public AreaShape
{
private:
	CPoint m_startPoint;
	CPoint m_OldPoint;
	float area;
	float length;
	int flag;

public:
	ITriangle();

	CPoint pt[3];
	
	static int nITriangle;
	float getLength(CPoint m_startPoint, CPoint currentPoint);
	float getArea(CPoint m_startPoint, CPoint currentPoint);
	CPoint getStartPoint();
	CPoint getOldPoint();

	void setStartPoint(CPoint point);
	void setOldPoint(CPoint point);
	void setDrawPoint(CPoint a, CPoint b);

	void OnDraw(CDC* pDC);
	void OnDraw(CDC* pDC, CPoint newStartPoint, CPoint NewEndPoint);
	void Rotate(CDC* pDC);
};
