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
	float length = 0.0;			// ����/�ܳ�
	string name = "shape";		// ����
	int color[3] = { 0,0,0 };	// ��ɫ,�ֱ�ΪR/G/B
	int linear = PS_SOLID;		// ���ͣ�PS_SOLID ʵ��,PS_DASH ����,PS_DOT ����,PS_DASHDOT �㻯��,PS_DASHDOTDOT��
	int lineWidth = 1;			// �߿�

public:
	CPoint currentPoint;

	// �������Ե�get����
	int getId();
	virtual float getLength();
	string getName();
	int* getColor();
	int getLinear();
	int getLineWidth();

	// �������Ե�set����
	void setId(int id);
	void setLength(float length);
	void setName(string name);
	void setColor(int r, int g, int b);
	void setLinear(int linear);
	void setLineWidth(int lineWidth);

	//��������
	virtual void OnDraw(CDC* pDC);
};

