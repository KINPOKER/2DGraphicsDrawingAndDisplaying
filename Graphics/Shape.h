#pragma once
#include <afxwin.h>

#include <string>
#include <iostream>
#include <stdio.h>

using namespace std;

class Shape : public CView
{
private:
	int id = 0;					// id
	float length = 0.0;			// 长度/周长
	string name = "shape";		// 名称
	int color[3] = { 0,0,0 };	// 颜色,分别为R/G/B
	int linear = PS_SOLID;		// 线型（PS_SOLID 实线,PS_DASH 虚线,PS_DOT 点线,PS_DASHDOT 点化线,PS_DASHDOTDOT）
	int lineWidth = 1;			// 线宽

public:
	CPoint currentPoint;

	// 所有属性的get方法
	int getId();
	virtual float getLength();
	string getName();
	int* getColor();
	int getLinear();
	int getLineWidth();

	// 所有属性的set方法
	void setId(int id);
	void setLength(float length);
	void setName(string name);
	void setColor(int r, int g, int b);
	void setLinear(int linear);
	void setLineWidth(int lineWidth);

	//其他方法
	virtual void OnDraw(CDC* pDC);
};

