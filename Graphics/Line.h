#pragma once
#include "LineShape.h"

//using namespace std;

class Line : public LineShape
{
private:
	CPoint firstPoint;		// 起始点
	CPoint endPoint;		// 终止点
	float length;			// 长度

public:
	Line();

	static int nLine;

	// 所有属性的get方法
	float getLength();
	CPoint getFirstPoint();
	CPoint getEndPoint();
	//CPoint getCurrentPoint();

	// 所有属性的set方法
	void setFirstPoint(CPoint point);
	void setEndPoint(CPoint point);

	//其他方法
	void OnDraw(CDC* pDC);

	///////////////新增/////////////////
	void OnDraw(CDC* pDC, CPoint newStartPoint, CPoint NewEndPoint);
	void OnDraw(CPoint newStartPoint, CPoint NewEndPoint, CDC* pDC);
};