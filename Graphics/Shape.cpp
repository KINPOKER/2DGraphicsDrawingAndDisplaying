#include "pch.h"
#include "Shape.h"

#include <string>
#include <iostream>
#include <stdio.h>

using namespace std;

// 所有属性的get方法
int Shape::getId() {
	return id;
}
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
// 所有属性的set方法
void  Shape::setId(int id) {
	this->id = id;
}
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

	// 获取窗口
	CDC* pDC = GetDC();
	// 声明新画笔,并设置为目标颜色
	CPen cPen;
	cPen.CreatePen(linear, lineWidth, RGB(r, g, b));
	// 将此画笔选入当前设备环境并保存原来的画笔
	CPen* pOldPen = pDC->SelectObject(&cPen);
	// 用目标颜色覆盖原颜色
	this->OnDraw(pDC);
	// 换回原画笔
	pDC->SelectObject(pOldPen);
}

// 更改线型
void  Shape::setLinear(int linear) {
	this->linear = linear;

	// 获取窗口
	CDC* pDC = GetDC();
	// 声明新画笔,并设置为目标颜色
	CPen cPen;
	cPen.CreatePen(linear, lineWidth, RGB(color[0], color[1], color[2]));
	// 将此画笔选入当前设备环境并保存原来的画笔
	CPen* pOldPen = pDC->SelectObject(&cPen);
	// 用目标线型覆盖原线型
	this->OnDraw(pDC);
	// 换回原画笔
	pDC->SelectObject(pOldPen);
}

// 更改线宽
void  Shape::setLineWidth(int lineWidth) {
	this->lineWidth = lineWidth;

	// 获取窗口
	CDC* pDC = GetDC();
	// 声明新画笔,并设置为目标颜色
	CPen cPen;
	cPen.CreatePen(linear, lineWidth, RGB(color[0], color[1], color[2]));
	// 将此画笔选入当前设备环境并保存原来的画笔
	CPen* pOldPen = pDC->SelectObject(&cPen);
	// 用目标线宽覆盖原线宽
	this->OnDraw(pDC);
	// 换回原画笔
	pDC->SelectObject(pOldPen);
}

void Shape::OnDraw(CDC* pDC)
{

}


