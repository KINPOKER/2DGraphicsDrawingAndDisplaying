#pragma once
#include "AreaShape.h"

class Triangle :public AreaShape
{
private:
	CPoint Point[3] = { 0,0,0 };
	int nCount = 0;		//¶¥µã¼ÆÊýÆ÷
	float area = 0;
	float length = 0;
public:
	float getLength();
	float getArea();

	void setPoint(CPoint point);
	//void setMiddlePoint(CPoint point);
	//void setEndPoint(CPoint point);

	void OnDraw(CDC* pDC);
};
