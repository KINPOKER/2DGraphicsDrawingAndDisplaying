#include "pch.h"
#include "ITriangle.h"
#include "math.h"

ITriangle::ITriangle() {
	setName("����������");
	m_startPoint = 0;
	m_OldPoint = 0;
	area = 0;
	length = 0;
	flag = 1;
}

float ITriangle::getArea(CPoint m_startPoint, CPoint currentPoint)
{
	float a, h;
	a = abs(currentPoint.x - m_startPoint.x);
	h = abs(currentPoint.y - m_startPoint.y);
	area = a * h / 2;
	return fabs(area);
}

float ITriangle::getLength(CPoint m_startPoint, CPoint currentPoint)
{

	setDrawPoint(m_startPoint, currentPoint);
	float l1, l2, l3;
	l1 = abs(pt[2].x - pt[1].x);
	l2 = sqrt(pow((pt[1].x - pt[0].x), 2) + pow((pt[1].y - pt[0].y), 2));
	l3 = sqrt(pow((pt[2].x - pt[0].x), 2) + pow((pt[2].y - pt[0].y), 2));
	length = l1 + l2 + l3;
	return fabs(length);
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

void ITriangle::setDrawPoint(CPoint p1, CPoint p2) {
	pt[0].x = (p1.x + p2.x) / 2;
	pt[0].y = p1.y;
	pt[1].x = p1.x;
	pt[1].y = p2.y;
	pt[2] = p2;
}

void ITriangle::OnDraw(CDC* pDC)
{
	int* color = getColor();
	CPen cPen, * pOldPen;
	cPen.CreatePen(getLinear(), getLineWidth(), RGB(color[0], color[1], color[2]));
	pOldPen = pDC->SelectObject(&cPen);//�����»���

	setDrawPoint(m_startPoint, m_OldPoint);
	pDC->Polygon(pt, 3);

	setDrawPoint(m_startPoint, currentPoint);
	pDC->Polygon(pt, 3);

	m_OldPoint = currentPoint;

/*	//��ʾ�ܳ����
	getLength(m_startPoint, currentPoint);
	getArea(m_startPoint, currentPoint);
	CString str;
	str.Format(CString("�ܳ� = %.2f  ��� = %.2f"), length, area);
	pDC->SetTextColor(RGB(255, 0, 0));
	pDC->TextOutW(50, 300, str);
*/

//���ñ߽��
	CPoint point2, point4;
	point2.x = currentPoint.x;
	point2.y = m_startPoint.y;
	point4.x = m_startPoint.x;
	point4.y = currentPoint.y;
	setBorderPoint(m_startPoint, point2, currentPoint, point4);

	pDC->SelectObject(pOldPen);//�ָ��ɻ���

}

void ITriangle::OnDraw(CDC* pDC, CPoint newStartPoint, CPoint NewEndPoint)
{
	int* color = getColor();
	CPen cPen, * pOldPen;
	cPen.CreatePen(getLinear(), getLineWidth(), RGB(color[0], color[1], color[2]));
	pOldPen = pDC->SelectObject(&cPen);//�����»���

	setDrawPoint(m_startPoint, m_OldPoint);
	pDC->Polygon(pt, 3);
//	Echo(pDC, m_startPoint, m_OldPoint);

	setDrawPoint(newStartPoint, NewEndPoint);
	pDC->Polygon(pt, 3);

	m_startPoint = newStartPoint;
	m_OldPoint = NewEndPoint;

	//��ʾ�ܳ����
	/*
	getLength(newStartPoint, NewEndPoint);
	getArea(newStartPoint, NewEndPoint);
	CString str;
	str.Format(CString("�ܳ� = %.2f  ��� = %.2f"), length, area);
	pDC->SetTextColor(RGB(255, 0, 0));
	pDC->TextOutW(50, 300, str);
	*/
	

//	Echo(pDC, newStartPoint, NewEndPoint);

	pDC->SelectObject(pOldPen);//�ָ��ɻ���
}

void ITriangle::Rotate(CDC* pDC)
{
	int* color = getColor();
	CPen cPen, * pOldPen;
	cPen.CreatePen(getLinear(), getLineWidth(), RGB(color[0], color[1], color[2]));
	pOldPen = pDC->SelectObject(&cPen);//�����»���

	pDC->Polygon(pt, 3);

	CPoint CenterPoint;
	CPoint newpt[3];
	CPoint* borderPoint1 = this->getBorderPoint();
	CenterPoint.x = abs(borderPoint1[0].x + borderPoint1[2].x) / 2;
	CenterPoint.y = abs(borderPoint1[0].y + borderPoint1[2].y) / 2;//������ת����
	for (int i = 0; i < 3; i++)
	{
		newpt[i].x = pt[i].y - CenterPoint.y + CenterPoint.x;
		newpt[i].y = CenterPoint.x - pt[i].x + CenterPoint.y;
	}	//������ת��ĵ�

	pDC->Polygon(newpt, 3);//��ʾ��ת���ͼ��

	for (int i = 0; i < 3; i++)
	{
		pt[i] = newpt[i];
	} //����pt
	//��������ͨ��pt�ҵ�m_startPoint��m_OldPoint�������Ի�
	m_startPoint.y = pt[2].y;
	m_OldPoint.x = pt[1].x;
	int mark = 0;
	mark = flag % 2;
	if (mark) {
		m_startPoint.x = pt[0].x;
		m_OldPoint.y = pt[1].y;
	}
	else {
		m_startPoint.x = pt[2].x;
		m_OldPoint.y = pt[0].y;
	}//��ת��pt�ͻ��Ե�Ķ�Ӧ�ᷢ���仯
	flag++;

	//���ñ߽��
	CPoint point2, point4;
	point2.x = m_OldPoint.x;
	point2.y = m_startPoint.y;
	point4.x = m_startPoint.x;
	point4.y = m_OldPoint.y;
	setBorderPoint(m_startPoint, point2, m_OldPoint, point4);

	pDC->SelectObject(pOldPen);
}