#pragma once
#include <afxwin.h>

#include <string>
#include <iostream>
#include <stdio.h>

using namespace std;

class Shape : public CView
{
private:
	float length;			// ����/�ܳ�
	string name;			// ����
	int color[3];			// ��ɫ,�ֱ�ΪR/G/B
	int linear;				// ���ͣ�PS_SOLID ʵ��,PS_DASH ����,PS_DOT ����,PS_DASHDOT �㻯��,PS_DASHDOTDOT��
	UINT lineWidth;			// �߿�
	CPoint borderPoint[4];	//��Ӿ��ο�߽��

public:
	Shape();
	CPoint currentPoint;
	CPoint currentPointBeforeMove;
	CPoint moveStartPoint, moveEndPoint;
	CPoint changStartPoint, changEndPoint;
	// �������Ե�get����
	virtual float getLength();
	string getName();
	int* getColor();
	int getLinear();
	int getLineWidth();
	CPoint* getBorderPoint();

	// �������Ե�set����
	void setLength(float length);
	void setName(string name);
	void setColor(int r, int g, int b);
	void setLinear(int linear);
	void setLineWidth(UINT lineWidth);
	void setBorderPoint(CPoint a, CPoint b, CPoint c, CPoint d);

	//��������
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

