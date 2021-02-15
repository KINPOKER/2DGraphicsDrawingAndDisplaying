#pragma once
#include "Shape.h"

#include <string>
#include <math.h>
#include <iostream>
#include <stdio.h>

using namespace std;

class LineShape : public Shape
{
private:
	CPoint firstPoint;		// 起始点
	CPoint endPoint;		// 终止点
	float length;			// 长度

public:
	// 所有属性的get方法
	virtual float getLength();
	CPoint getFirstPoint();
	CPoint getEndPoint();

	// 所有属性的set方法
	void setFirstPoint(CPoint point);
	void setEndPoint(CPoint point);

	//其他方法
	virtual void OnDraw(CDC* pDC);
};
