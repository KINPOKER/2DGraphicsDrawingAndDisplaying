#pragma once
#include "AreaShape.h"

class RTriangle :public AreaShape
{
private:
	CPoint m_startPoint = 0;
	CPoint m_OldPoint = 0;
	CPoint pt[3];
	float area = 0;
	float length = 0;

public:
	static int nRTriangle;
	float getLength();
	float getArea();
	CPoint getStartPoint();
	CPoint getOldPoint();
	void getDrawPoint();

	void setStartPoint(CPoint point);
	void setOldPoint(CPoint point);

	void OnDraw(CDC* pDC);
	void Echo(CDC* pDC);
};
