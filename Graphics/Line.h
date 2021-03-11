#pragma once
#include "LineShape.h"

//using namespace std;

class Line : public LineShape
{
private:
	CPoint firstPoint;		// ��ʼ��
	CPoint endPoint;		// ��ֹ��
	float length;			// ����

public:
	Line();

	static int nLine;

	// �������Ե�get����
	float getLength();
	CPoint getFirstPoint();
	CPoint getEndPoint();
	//CPoint getCurrentPoint();

	// �������Ե�set����
	void setFirstPoint(CPoint point);
	void setEndPoint(CPoint point);

	//��������
	void OnDraw(CDC* pDC);

	///////////////����/////////////////
	void OnDraw(CDC* pDC, CPoint newStartPoint, CPoint NewEndPoint);
	void OnDraw(CPoint newStartPoint, CPoint NewEndPoint, CDC* pDC);
};