#pragma once
#include "LineShape.h"

using namespace std;

class PolyLine : public LineShape
{
private:
	CPoint* PtLine;
	CPoint newPtLine[50];
	CPoint m_startPoint;
	CPoint m_OldPoint;
	float ax;
	float ay;
	float bx;
	float by;
	float cx;
	float cy;

public:
	PolyLine();
	~PolyLine();
	static int nPolyLine;
	int numPoint;     //������

	float getLength();
	void SetPoint(CPoint& point);

	//��������
	void OnDraw(CDC* pDC);

	//////////////����//////////////////
	CPoint getStartPoint();
	CPoint getOldPoint();
	CPoint* FindBorderpoint();
	void OnDraw(CDC* pDC, CPoint newStartPoint, CPoint NewEndPoint);
	void ScaleOnDraw(CDC* pDC, CPoint newStartPoint, CPoint NewEndPoint);
	void UpdatePtLine();
	void Rotate(CDC* pDC);
};