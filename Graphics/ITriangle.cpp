#include "pch.h"
#include "ITriangle.h"
#include "math.h"

float ITriangle::getArea() {
	float a, h;
	a = currentPoint.x - m_startPoint.x;
	h = currentPoint.y - m_startPoint.y;
	area = a * h / 2;
	return area;
}

float ITriangle::getLength() {

	pt[0].x = (currentPoint.x + m_startPoint.x) / 2;
	pt[0].y = m_startPoint.y;
	pt[1].x = m_startPoint.x;
	pt[1].y = currentPoint.y;
	pt[2] = currentPoint;

	float l1, l2, l3;
	l1 = pt[2].x - pt[1].x;
	l2 = sqrt(pow((pt[1].x - pt[0].x), 2) + pow((pt[1].y - pt[0].y), 2));
	l3 = sqrt(pow((pt[2].x - pt[0].x), 2) + pow((pt[2].y - pt[0].y), 2));
	length = l1 + l2 + l3;
	return length;
}

CPoint ITriangle::getStartPoint() {
	return m_startPoint;
}

CPoint ITriangle::getOldPoint() {
	return m_OldPoint;
}

void ITriangle::setStartPoint(CPoint point) {
	m_startPoint = point;
}

void ITriangle::setOldPoint(CPoint point) {
	m_OldPoint = point;
}

void ITriangle::OnDraw(CDC* pDC)
{
	int* color = getColor();
	CPen cPen, * pOldPen;
	cPen.CreatePen(getLinear(), getLineWidth(), RGB(color[0], color[1], color[2]));
	pOldPen = pDC->SelectObject(&cPen);//�����»���

	pDC->MoveTo((m_OldPoint.x + m_startPoint.x) / 2, m_startPoint.y);
	pDC->LineTo(m_startPoint.x, m_OldPoint.y);
	pDC->LineTo(m_OldPoint);
	pDC->LineTo((m_OldPoint.x + m_startPoint.x) / 2, m_startPoint.y);

	pDC->MoveTo((currentPoint.x + m_startPoint.x) / 2, m_startPoint.y);
	pDC->LineTo(m_startPoint.x, currentPoint.y);
	pDC->LineTo(currentPoint);
	pDC->LineTo((currentPoint.x + m_startPoint.x) / 2, m_startPoint.y);

	m_OldPoint = currentPoint;

	//��ʾ�ܳ����
	getLength();
	getArea();
	CString str;
	str.Format(CString("�ܳ� = %.2f  ��� = %.2f"), length, area);
	pDC->SetTextColor(RGB(255, 0, 0));
	pDC->TextOutW(50, 300, str);

	pDC->SelectObject(pOldPen);//�ָ��ɻ���

	//DoubleBuffer(pDC);
}

void ITriangle::Echo(CDC* pDC)
{
	for (int i = 0; i < 3; i++)
	{
		CString str;
		str.Format(CString("x = %d, y = %d"), pt[i].x, pt[i].y);
		pDC->SetTextColor(RGB(255, 0, 0));
		pDC->TextOutW(pt[i].x, pt[i].y, str);	// ����
		pDC->Rectangle(pt[i].x - 5, pt[i].y - 5, pt[i].x + 5, pt[i].y + 5);
	}
}

//void ITriangle::DoubleBuffer(CDC* pDC) 
//{
//	CRect rect;
//	GetClientRect(&rect);
//	CDC memDC;
//	memDC.CreateCompatibleDC(pDC);
//	CBitmap NewBitmap, * pOldBitmap;
//	NewBitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
//	pOldBitmap = memDC.SelectObject(&NewBitmap);
//	memDC.FillSolidRect(rect, pDC->GetBkColor());
//	OnDraw(&memDC);
//	pDC->BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);
//	memDC.SelectObject(pOldBitmap);
//	NewBitmap.DeleteObject();
//	memDC.DeleteDC();
//}