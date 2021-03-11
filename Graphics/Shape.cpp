#include "pch.h"
#include "Shape.h"

#include <string>
#include <iostream>
#include <stdio.h>

using namespace std;

Shape::Shape() {
	length = 0.0;
	name = "shape";
	setColor(0, 0, 0);
	linear = PS_SOLID;
	lineWidth = 1;
	setBorderPoint(0, 0, 0, 0);
}

// 所有属性的get方法

float  Shape::getLength() {
	return length;
}
string  Shape::getName() {
	return name;
}
int* Shape::getColor() {
	return color;
}
int  Shape::getLinear() {
	return linear;
}
int  Shape::getLineWidth() {
	return lineWidth;
}
CPoint* Shape::getBorderPoint()
{
	return borderPoint;
}
// 所有属性的set方法
void  Shape::setLength(float length) {
	this->length = length;
}
void  Shape::setName(string name) {
	this->name = name;
}

// 更改颜色
void  Shape::setColor(int r, int g, int b) {
	color[0] = r;
	color[1] = g;
	color[2] = b;
}

// 更改线型
void  Shape::setLinear(int linear) {
	this->linear = linear;
}

// 更改线宽
void  Shape::setLineWidth(UINT lineWidth) {
	this->lineWidth = lineWidth;
}

void Shape::setBorderPoint(CPoint a, CPoint b, CPoint c, CPoint d)
{
	borderPoint[0] = a;
	borderPoint[1] = b;
	borderPoint[2] = c;
	borderPoint[3] = d;
}

void Shape::OnDraw(CDC* pDC)
{

}

void Shape::OnDraw(CDC* pDC, CPoint newStartPoint, CPoint NewEndPoint)
{

}

void Shape::ScaleOnDraw(CDC* pDC, CPoint newStartPoint, CPoint NewEndPoint)
{

}

void Shape::OnDraw(CPoint newStartPoint, CPoint NewEndPoint, CDC* pDC)
{

}

void Shape::Move(CDC* pDC)
{
	CPoint newStartPoint, NewEndPoint;

	CPoint* borderPoint1 = this->getBorderPoint();
	CPoint currentPoint1 = this->getCurrentPoint();
	CPoint currentPointBeforeMove1 = this->getCurrentPointBeforeMove();

	newStartPoint.x = borderPoint1[0].x + currentPoint1.x - currentPointBeforeMove1.x;
	newStartPoint.y = borderPoint1[0].y + currentPoint1.y - currentPointBeforeMove1.y;
	NewEndPoint.x = borderPoint1[2].x + currentPoint1.x - currentPointBeforeMove1.x;
	NewEndPoint.y = borderPoint1[2].y + currentPoint1.y - currentPointBeforeMove1.y;

	this->OnDraw(pDC, newStartPoint, NewEndPoint);

	moveStartPoint = newStartPoint;
	moveEndPoint = NewEndPoint;
}

void Shape::Scale(CDC* pDC, int chs)
{
	CPoint newStartPoint, NewEndPoint;

	CPoint* borderPoint1 = this->getBorderPoint();
	CPoint currentPoint1 = this->getCurrentPoint();

	if (chs == 1)     //右下角缩放
	{
		newStartPoint = borderPoint1[0];
		NewEndPoint = currentPoint1;
	}
	else if (chs == 2)     //左下角缩放
	{
		newStartPoint.x = currentPoint1.x;
		newStartPoint.y = borderPoint1[1].y;
		NewEndPoint.x = borderPoint1[1].x;
		NewEndPoint.y = currentPoint1.y;
	}
	else if (chs == 3)     //左上角缩放
	{
		newStartPoint = currentPoint1;
		NewEndPoint = borderPoint1[2];
	}
	else if (chs == 4)     //右上角缩放
	{
		newStartPoint.x = borderPoint1[3].x;
		newStartPoint.y = currentPoint1.y;
		NewEndPoint.x = currentPoint1.x;
		NewEndPoint.y = borderPoint1[3].y;
	}
	this->OnDraw(pDC, newStartPoint, NewEndPoint);

	changStartPoint = newStartPoint;
	changEndPoint = NewEndPoint;
}

void Shape::ScaleManyVertices(CDC* pDC, int chs)
{
	CPoint newStartPoint, NewEndPoint;

	CPoint* borderPoint1 = this->getBorderPoint();
	CPoint currentPoint1 = this->getCurrentPoint();

	if (chs == 1)     //右下角缩放
	{
		newStartPoint = borderPoint1[0];
		NewEndPoint = currentPoint1;
	}
	else if (chs == 2)     //左下角缩放
	{
		newStartPoint.x = currentPoint1.x;
		newStartPoint.y = borderPoint1[1].y;
		NewEndPoint.x = borderPoint1[1].x;
		NewEndPoint.y = currentPoint1.y;
	}
	else if (chs == 3)     //左上角缩放
	{
		newStartPoint = currentPoint1;
		NewEndPoint = borderPoint1[2];
	}
	else if (chs == 4)     //右上角缩放
	{
		newStartPoint.x = borderPoint1[3].x;
		newStartPoint.y = currentPoint1.y;
		NewEndPoint.x = currentPoint1.x;
		NewEndPoint.y = borderPoint1[3].y;
	}
	this->ScaleOnDraw(pDC, newStartPoint, NewEndPoint);

	changStartPoint = newStartPoint;
	changEndPoint = NewEndPoint;
}

void Shape::Echo(CDC* pDC, CPoint startPoint, CPoint endPoint)	// 回显
{
	//CPoint* brpoint = borderPoint;
	CPoint LeftBottomPoint, RightUpPoint, EchoPoint[4];
	LeftBottomPoint.x = startPoint.x;
	LeftBottomPoint.y = endPoint.y;
	RightUpPoint.x = endPoint.x;
	RightUpPoint.y = startPoint.y;

	::SetCursor(LoadCursorW(NULL, IDC_HAND));

	EchoPoint[0] = startPoint;
	EchoPoint[1] = RightUpPoint;
	EchoPoint[2] = endPoint;
	EchoPoint[3] = LeftBottomPoint;

	for (int i = 0; i < 4; i++)
	{
		CString str;
		pDC->Rectangle(EchoPoint[i].x - 5, EchoPoint[i].y - 5, EchoPoint[i].x + 5, EchoPoint[i].y + 5);
	}
}

void Shape::UpdateBorderpoint()
{
	for (int i = 0; i < 4; i++)
	{
		borderPoint[i].x += currentPoint.x - this->currentPointBeforeMove.x;
		borderPoint[i].y += currentPoint.y - this->currentPointBeforeMove.y;
		//borderPoint[i].x += currentPoint.x - currentPointBeforeMove.x;
		//borderPoint[i].y += currentPoint.y - currentPointBeforeMove.y;
	}
}

void Shape::changesize(CPoint* brpoint, CPoint& point, int& chs, CDC* pDC)
{
	this->currentPoint = point;
	this->Scale(pDC, chs);
	if (chs == 1)     //右下角缩放
	{
		brpoint[0].x = brpoint[0].x;
		brpoint[1].x = point.x;
		brpoint[2].x = point.x;
		brpoint[3].x = brpoint[3].x;
		brpoint[0].y = brpoint[0].y;
		brpoint[1].y = brpoint[1].y;
		brpoint[2].y = point.y;
		brpoint[3].y = point.y;
		this->setBorderPoint(brpoint[0], brpoint[1], brpoint[2], brpoint[3]);
	}
	else if (chs == 2)     //左下角缩放
	{
		brpoint[0].x = point.x;
		brpoint[1].x = brpoint[1].x;
		brpoint[2].x = brpoint[2].x;
		brpoint[3].x = point.x;
		brpoint[0].y = brpoint[0].y;
		brpoint[1].y = brpoint[1].y;
		brpoint[2].y = point.y;
		brpoint[3].y = point.y;
		this->setBorderPoint(brpoint[0], brpoint[1], brpoint[2], brpoint[3]);
	}
	else if (chs == 3)     //左上角缩放
	{
		brpoint[0].x = point.x;
		brpoint[1].x = brpoint[1].y;
		brpoint[2].x = brpoint[2].y;
		brpoint[3].x = point.x;
		brpoint[0].y = point.y;
		brpoint[1].y = point.y;
		brpoint[2].y = brpoint[2].y;
		brpoint[3].y = brpoint[3].y;
		this->setBorderPoint(brpoint[0], brpoint[1], brpoint[2], brpoint[3]);
	}
	else if (chs == 4)     //右上角缩放
	{
		brpoint[0].x = brpoint[0].x;
		brpoint[1].x = point.x;
		brpoint[2].x = point.x;
		brpoint[3].x = brpoint[3].x;
		brpoint[0].y = point.y;
		brpoint[1].y = point.y;
		brpoint[2].y = brpoint[2].y;
		brpoint[3].y = brpoint[3].y;
		this->setBorderPoint(brpoint[0], brpoint[1], brpoint[2], brpoint[3]);
	}
}

CPoint Shape::getCurrentPoint()
{
	return this->currentPoint;
}

CPoint Shape::getCurrentPointBeforeMove()
{
	return this->currentPointBeforeMove;
}

void Shape::Rotate(CDC* pDC) {
	CPoint CenterPoint, newStartPoint, NewEndPoint;

	CPoint* borderPoint1 = this->getBorderPoint();

	CenterPoint.x = abs(borderPoint1[0].x + borderPoint1[2].x) / 2;
	CenterPoint.y = abs(borderPoint1[0].y + borderPoint1[2].y) / 2;

	newStartPoint.y = CenterPoint.x - borderPoint1[0].x + CenterPoint.y;
	newStartPoint.x = borderPoint1[0].y - CenterPoint.y + CenterPoint.x;
	NewEndPoint.y = CenterPoint.x - borderPoint1[2].x + CenterPoint.y;
	NewEndPoint.x = borderPoint1[2].y - CenterPoint.y + CenterPoint.x;

	this->OnDraw(newStartPoint, NewEndPoint, pDC);

}