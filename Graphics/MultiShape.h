#pragma once
#include "AreaShape.h"
class MultiShape : public AreaShape
{
private:
	CPoint* MultiPoint;
	CPoint newMultiPoint[50];
	CPoint m_startPoint;
	CPoint m_OldPoint;
	float ax;
	float ay;
	float bx;
	float by;
	float cx;
	float cy;

public:
	MultiShape();

	int nCount;
	static int nMultiShape;
	//void AddPoint(CPoint& point);
	void SetPoint(CPoint& point);
	void OnDraw(CDC* pDC);
	void FinishShape(CDC* pDC);
	void DecnCount();
	bool intersect(CPoint& a1, CPoint& a2, CPoint& b1, CPoint& b2);
	bool judge();
	bool EndJudge();
	virtual float getLength();
	double getarea();
	double trangleArea(CPoint& a,CPoint& b);
	~MultiShape();

	///////////////ÐÂÔö////////////
	CPoint getStartPoint();
	CPoint getOldPoint();
	CPoint* FindBorderpoint();
	void OnDraw(CDC* pDC, CPoint newStartPoint, CPoint NewEndPoint);
	void UpdateMultiPoint();
	void ScaleOnDraw(CDC* pDC, CPoint newStartPoint, CPoint NewEndPoint);
	void Rotate(CDC* pDC);
};

