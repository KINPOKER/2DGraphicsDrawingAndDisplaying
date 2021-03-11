#pragma once
#include <afxwin.h>

#include <string>
#include <iostream>
#include <stdio.h>

using namespace std;

class Shape : public CView
{
private:
	float length;			// 长度/周长
	string name;			// 名称
	int color[3];			// 颜色,分别为R/G/B
	int linear;				// 线型（PS_SOLID 实线,PS_DASH 虚线,PS_DOT 点线,PS_DASHDOT 点化线,PS_DASHDOTDOT）
	UINT lineWidth;			// 线宽
	CPoint borderPoint[4];	//外接矩形框边界点

public:
	Shape();
	CPoint currentPoint;
	CPoint currentPointBeforeMove;
	CPoint moveStartPoint, moveEndPoint;
	CPoint changStartPoint, changEndPoint;
	// 所有属性的get方法
	virtual float getLength();
	string getName();
	int* getColor();
	int getLinear();
	int getLineWidth();
	CPoint* getBorderPoint();

	// 所有属性的set方法
	void setLength(float length);
	void setName(string name);
	void setColor(int r, int g, int b);
	void setLinear(int linear);
	void setLineWidth(UINT lineWidth);
	void setBorderPoint(CPoint a, CPoint b, CPoint c, CPoint d);

	//其他方法
	virtual void OnDraw(CDC* pDC);
	virtual void OnDraw(CDC* pDC, CPoint newStartPoint, CPoint NewEndPoint);
	virtual void ScaleOnDraw(CDC* pDC, CPoint newStartPoint, CPoint NewEndPoint);

	void Move(CDC* pDC);
	void Scale(CDC* pDC, int chs);
	void ScaleManyVertices(CDC* pDC, int chs);

	void Echo(CDC* pDC, CPoint startPoint, CPoint endPoint);
	void UpdateBorderpoint();
	void changesize(CPoint* brpoint, CPoint& point, int& chs, CDC* pDC);

	CPoint getCurrentPoint();
	CPoint getCurrentPointBeforeMove();

	void Rotate(CDC* pDC);
	virtual void OnDraw(CPoint newStartPoint, CPoint NewEndPoint, CDC* pDC);
};

