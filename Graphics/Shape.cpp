#include "pch.h"
#include "Shape.h"

#include <string>
#include <iostream>
#include <stdio.h>

using namespace std;

// �������Ե�get����
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
// �������Ե�set����
void  Shape::setId(int id) {
	this->id = id;
}
void  Shape::setLength(float length) {
	this->length = length;
}
void  Shape::setName(string name) {
	this->name = name;
}

// ������ɫ
void  Shape::setColor(int r, int g, int b) {
	color[0] = r;
	color[1] = g;
	color[2] = b;

	// ��ȡ����
	CDC* pDC = GetDC();
	// �����»���,������ΪĿ����ɫ
	CPen cPen;
	cPen.CreatePen(linear, lineWidth, RGB(r, g, b));
	// ���˻���ѡ�뵱ǰ�豸����������ԭ���Ļ���
	CPen* pOldPen = pDC->SelectObject(&cPen);
	// ��Ŀ����ɫ����ԭ��ɫ
	this->OnDraw(pDC);
	// ����ԭ����
	pDC->SelectObject(pOldPen);
}

// ��������
void  Shape::setLinear(int linear) {
	this->linear = linear;

	// ��ȡ����
	CDC* pDC = GetDC();
	// �����»���,������ΪĿ����ɫ
	CPen cPen;
	cPen.CreatePen(linear, lineWidth, RGB(color[0], color[1], color[2]));
	// ���˻���ѡ�뵱ǰ�豸����������ԭ���Ļ���
	CPen* pOldPen = pDC->SelectObject(&cPen);
	// ��Ŀ�����͸���ԭ����
	this->OnDraw(pDC);
	// ����ԭ����
	pDC->SelectObject(pOldPen);
}

// �����߿�
void  Shape::setLineWidth(int lineWidth) {
	this->lineWidth = lineWidth;

	// ��ȡ����
	CDC* pDC = GetDC();
	// �����»���,������ΪĿ����ɫ
	CPen cPen;
	cPen.CreatePen(linear, lineWidth, RGB(color[0], color[1], color[2]));
	// ���˻���ѡ�뵱ǰ�豸����������ԭ���Ļ���
	CPen* pOldPen = pDC->SelectObject(&cPen);
	// ��Ŀ���߿���ԭ�߿�
	this->OnDraw(pDC);
	// ����ԭ����
	pDC->SelectObject(pOldPen);
}

void Shape::OnDraw(CDC* pDC)
{

}


