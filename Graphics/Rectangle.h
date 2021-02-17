#pragma once
#include "AreaShape.h"

class Rectangles : public AreaShape
{
private:
	CPoint m_startPoint = 0;
	CPoint m_OldPoint = 0;
	float area = 0;
	float length = 0;

	float width = 0;
	float extent = 0;

public:
	float getLength();
	float getArea();
	CPoint getStartPoint();
	CPoint getOldPoint();

	void setStartPoint(CPoint point);
	void setOldPoint(CPoint point);

	void OnDraw(CDC* pDC);
};

