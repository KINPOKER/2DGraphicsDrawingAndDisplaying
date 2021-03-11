#include "pch.h"
#include "MultiShape.h"
#include "math.h"

#define MAX 50

MultiShape::MultiShape()
{
	setName("多边形");
	m_startPoint = 0;
	m_OldPoint = 0;
	ax = 0.00;
	ay = 0.00;
	bx = 0.00;
	by = 0.00;
	cx = 0.00;
	cy = 0.00;
	if ((MultiPoint = new CPoint[MAX]) == NULL)
	{
		exit(0);
	}
	nCount = 0;
}

MultiShape::~MultiShape()
{
	delete[] MultiPoint;
}

//void MultiShape::AddPoint(CPoint& point)
//{
//	MultiPoint[nCount] = point;
//	nCount++;
//}

void MultiShape::SetPoint(CPoint& point)
{
	MultiPoint[nCount] = point;
	nCount++;
}

void MultiShape::OnDraw(CDC* pDC)
{
	int* color = getColor();
	CPen cPen;
	cPen.CreatePen(getLinear(), getLineWidth(), RGB(color[0], color[1], color[2]));
	CPen* pOldPen = pDC->SelectObject(&cPen);

	pDC->MoveTo(MultiPoint[nCount - 2]);
	pDC->LineTo(MultiPoint[nCount - 1]);

	pDC->SelectObject(pOldPen);
}

void MultiShape::FinishShape(CDC* pDC)
{
	int* color = getColor();
	CPen cPen;
	cPen.CreatePen(getLinear(), getLineWidth(), RGB(color[0], color[1], color[2]));
	CPen* pOldPen = pDC->SelectObject(&cPen);
	
	pDC->MoveTo(MultiPoint[nCount-1]);
	pDC->LineTo(MultiPoint[0]);

	CPoint* brpoint = FindBorderpoint();
	setBorderPoint(brpoint[0], brpoint[1], brpoint[2], brpoint[3]);

/*	CString str;
	str.Format(CString("周长=%0.2f,面积=%0.2lf"), getLength(),getarea());
	pDC->SetTextColor(RGB(255, 0, 0));
	pDC->SetBkMode(TRANSPARENT);
	pDC->TextOutW(MultiPoint[0].x, MultiPoint[0].y, str);
*/
	pDC->SelectObject(pOldPen);
}

void MultiShape::DecnCount()
{
	nCount--;
}

bool MultiShape::intersect(CPoint& a1, CPoint& a2, CPoint& b1, CPoint& b2)
{
	int ax_max = a1.x > a2.x ? a1.x : a2.x;
	int ax_min = a1.x > a2.x ? a2.x : a1.x;
	int ay_max = a1.y > a2.y ? a1.y : a2.y;
	int ay_min = a1.y > a2.y ? a2.y : a1.y;
	int bx_max = b1.x > b2.x ? b1.x : b2.x;
	int bx_min = b1.x > b2.x ? b2.x : b1.x;
	int by_max = b1.y > b2.y ? b1.y : b2.y;
	int by_min = b1.y > b2.y ? b2.y : b1.y;
	if (ax_max < bx_min || bx_max < ax_min || ay_max < by_min || by_max < ay_min)
	{
		return false;
	}
	int rest1 = (a2.x - a1.x) * (b1.y - a1.y) - (a2.y - a1.y) * (b1.x - a1.x);
	int rest2 = (a2.x - a1.x) * (b2.y - a1.y) - (a2.y - a1.y) * (b2.x - a1.x);
	int rest3 = (b1.x - b2.x) * (a1.y - b2.y) - (b1.y - b2.y) * (a1.x - b2.x);
	int rest4 = (b1.x - b2.x) * (a2.y - b2.y) - (b1.y - b2.y) * (a2.x - b2.x);
	if (rest1 * rest2 <= 0 && rest3 * rest4 <= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool MultiShape::judge()
{
	if (nCount > 3)
	{
		for (int i = 1; i < nCount - 2; i++)
		{
			if (intersect(MultiPoint[i - 1], MultiPoint[i], MultiPoint[nCount - 2], MultiPoint[nCount - 1]))
			{
				return true;
			}
		}
		return false;
	}
	return false;
}

float MultiShape::getLength()
{
	float Length = 0.00;
	for (int i = 1; i < nCount; i++)
	{
		Length = Length + sqrt((MultiPoint[i - 1].x - MultiPoint[i].x) * (MultiPoint[i - 1].x - MultiPoint[i].x) + (MultiPoint[i - 1].y - MultiPoint[i].y) * (MultiPoint[i - 1].y - MultiPoint[i].y));
	}
	Length = Length + sqrt((MultiPoint[0].x - MultiPoint[nCount - 1].x) * (MultiPoint[0].x - MultiPoint[nCount - 1].x) + (MultiPoint[0].y - MultiPoint[nCount - 1].y) * (MultiPoint[0].y - MultiPoint[nCount - 1].y));
	return Length;
}

double MultiShape::getarea()
{
	double ans = 0;
	for (int i = 1; i < nCount; i++)
	{
		ans += trangleArea(MultiPoint[i - 1], MultiPoint[i]);
	}
	ans += trangleArea(MultiPoint[nCount-1], MultiPoint[0]);
	ans = fabs(ans);
	return ans;
}

double MultiShape::trangleArea(CPoint& a, CPoint& b)
{
	double ans = 0;
	ans = 0.5 * (a.x * b.y - a.y * b.x);
	return ans;
}

bool MultiShape::EndJudge()
{
	if (nCount > 3)
	{
		for (int i = 2; i < nCount - 1; i++)
		{
			if (intersect(MultiPoint[i - 1], MultiPoint[i], MultiPoint[nCount - 1], MultiPoint[0]))
			{
				return true;
			}
		}
		return false;
	}
	return false;
}

////////////////新增//////////////////

CPoint MultiShape::getStartPoint() {
	return m_startPoint;
}

CPoint MultiShape::getOldPoint() {
	return m_OldPoint;
}

CPoint* MultiShape::FindBorderpoint()
{
	CPoint* brpoint = getBorderPoint();
	int xmin = 9999, xmax = 0, ymin = 9999, ymax = 0;
	for (int i = 0; i < nCount; i++)
	{
		if (MultiPoint[i].x < xmin) { xmin = MultiPoint[i].x; }
		if (MultiPoint[i].x > xmax) { xmax = MultiPoint[i].x; }
		if (MultiPoint[i].y < ymin) { ymin = MultiPoint[i].y; } 
		if (MultiPoint[i].y > ymax) { ymax = MultiPoint[i].y; }
	}
	brpoint[0].x = xmin; brpoint[0].y = ymin;
	brpoint[1].x = xmax; brpoint[1].y = ymin;
	brpoint[2].x = xmax; brpoint[2].y = ymax;
	brpoint[3].x = xmin; brpoint[3].y = ymax;

	m_startPoint = brpoint[0];
	m_OldPoint = brpoint[2];

	//MessageBox(_T("FindBorderpoint"));

	return brpoint;
}

void MultiShape::OnDraw(CDC* pDC, CPoint newStartPoint, CPoint NewEndPoint)
{
	//MessageBox(_T("多边形ondraw重载"));
	int* color = getColor();
	CPen cPen, * pOldPen;
	cPen.CreatePen(getLinear(), getLineWidth(), RGB(color[0], color[1], color[2]));
	pOldPen = pDC->SelectObject(&cPen);//设置新画笔

	pDC->Polygon(MultiPoint, nCount);

	//CPoint* brpoint = getBorderPoint();
	for (int i = 0; i < nCount; i++)
	{
		MultiPoint[i].x += newStartPoint.x - m_startPoint.x;
		MultiPoint[i].y += newStartPoint.y - m_startPoint.y;
	}
	pDC->Polygon(MultiPoint, nCount);

	m_startPoint = newStartPoint;
	m_OldPoint = NewEndPoint;

	pDC->SelectObject(pOldPen);//恢复旧画笔
}

void MultiShape::UpdateMultiPoint() {
	for (int i = 0; i < nCount; i++)
	{
		MultiPoint[i].x = newMultiPoint[i].x;
		MultiPoint[i].y = newMultiPoint[i].y;
	}
}

void MultiShape::ScaleOnDraw(CDC* pDC, CPoint newStartPoint, CPoint NewEndPoint)
{
	int* color = getColor();
	CPen cPen, * pOldPen;
	cPen.CreatePen(getLinear(), getLineWidth(), RGB(color[0], color[1], color[2]));
	pOldPen = pDC->SelectObject(&cPen);//设置新画笔

	CPoint* brpoint = getBorderPoint();
	float x[999] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	float y[999] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	ax = brpoint[2].x - brpoint[0].x;
	ay = brpoint[2].y - brpoint[0].y;
	bx = NewEndPoint.x - newStartPoint.x;
	by = NewEndPoint.y - newStartPoint.y;
	cx = m_OldPoint.x - m_startPoint.x;
	cy = m_OldPoint.y - m_startPoint.y;

	for (int i = 0; i < nCount; i++)
	{
		///MultiPoint[i].x = (int)((MultiPoint[i].x - m_startPoint.x) * (NewEndPoint.x - newStartPoint.x) / (m_OldPoint.x - m_startPoint.x) + newStartPoint.x);
		//MultiPoint[i].y = (int)((MultiPoint[i].y - m_startPoint.y) * (NewEndPoint.y - newStartPoint.y) / (m_OldPoint.y - m_startPoint.y) + newStartPoint.y);
		x[i] = (float)(MultiPoint[i].x - brpoint[0].x) * cx / ax + m_startPoint.x;
		y[i] = (float)(MultiPoint[i].y - brpoint[0].y) * cy / ay + m_startPoint.y;
		newMultiPoint[i].x = x[i];
		newMultiPoint[i].y = y[i];
	}
	pDC->Polygon(newMultiPoint, nCount);

	for (int i = 0; i < nCount; i++)
	{
		///MultiPoint[i].x = (int)((MultiPoint[i].x - m_startPoint.x) * (NewEndPoint.x - newStartPoint.x) / (m_OldPoint.x - m_startPoint.x) + newStartPoint.x);
		//MultiPoint[i].y = (int)((MultiPoint[i].y - m_startPoint.y) * (NewEndPoint.y - newStartPoint.y) / (m_OldPoint.y - m_startPoint.y) + newStartPoint.y);
		x[i] = (float)(MultiPoint[i].x - brpoint[0].x) * bx / ax + newStartPoint.x;
		y[i] = (float)(MultiPoint[i].y - brpoint[0].y) * by / ay + newStartPoint.y;
		newMultiPoint[i].x = x[i];
		newMultiPoint[i].y = y[i];
	}
	pDC->Polygon(newMultiPoint, nCount);

	m_startPoint = newStartPoint;
	m_OldPoint = NewEndPoint;

	//Echo(pDC, newStartPoint, NewEndPoint);

	pDC->SelectObject(pOldPen);//恢复旧画笔
}

void  MultiShape::Rotate(CDC* pDC)
{
	int* color = getColor();
	CPen cPen, * pOldPen;
	cPen.CreatePen(getLinear(), getLineWidth(), RGB(color[0], color[1], color[2]));
	pOldPen = pDC->SelectObject(&cPen);//设置新画笔

	pDC->Polygon(MultiPoint, nCount);

	CPoint* borderPoint1 = getBorderPoint();
	CPoint CenterPoint;
	CPoint newMultiPoint[50];
	CenterPoint.x = abs(borderPoint1[0].x + borderPoint1[2].x) / 2;
	CenterPoint.y = abs(borderPoint1[0].y + borderPoint1[2].y) / 2;//计算旋转中心

	for (int i = 0; i < nCount; i++)
	{
		newMultiPoint[i].x = MultiPoint[i].y - CenterPoint.y + CenterPoint.x;
		newMultiPoint[i].y = CenterPoint.x - MultiPoint[i].x + CenterPoint.y;
	}	//计算旋转后的点
	pDC->Polygon(newMultiPoint, nCount);//显示旋转后的图形
	for (int i = 0; i < nCount; i++)
	{
		MultiPoint[i] = newMultiPoint[i];
	}

	//设置边界点
	setBorderPoint(borderPoint1[0], borderPoint1[1], borderPoint1[2], borderPoint1[3]);
	pDC->SelectObject(pOldPen);
}