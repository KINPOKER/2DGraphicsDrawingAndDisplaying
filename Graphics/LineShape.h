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
	CPoint firstPoint;		// ��ʼ��
	CPoint endPoint;		// ��ֹ��
	float length;			// ����

public:
	// �������Ե�get����
	virtual float getLength();
	CPoint getFirstPoint();
	CPoint getEndPoint();

	// �������Ե�set����
	void setFirstPoint(CPoint point);
	void setEndPoint(CPoint point);

	//��������
	virtual void OnDraw(CDC* pDC);
};
