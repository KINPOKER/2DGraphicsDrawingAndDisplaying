#include "pch.h"
#include "Circle.h"

Circle::Circle() {
	setName("Բ");
	m_startPoint = 0;
	m_OldPoint = 0;
	area = 0;
	length = 0;
	r = 0;
}

float Circle::getArea(CPoint m_startPoint, CPoint currentPoint)
{
	r = abs(currentPoint.x - m_startPoint.x) / 2;
	area = (pow(r, 2)) * PI;
	return area;
}

float Circle::getLength(CPoint m_startPoint, CPoint currentPoint)
{
	r = abs(currentPoint.x - m_startPoint.x) / 2;;
	length = r * PI * 2;
	return length;
}

CPoint Circle::getStartPoint() {
	return m_startPoint;
}

CPoint Circle::getOldPoint() {
	return m_OldPoint;
}

void Circle::setStartPoint(CPoint point) {
	m_startPoint = point;
}

void Circle::setOldPoint(CPoint point) {
	m_OldPoint = point;
}

void Circle::OnDraw(CDC* pDC)
{
	int* color = getColor();
	CPen cPen;
	cPen.CreatePen(getLinear(), getLineWidth(), RGB(color[0], color[1], color[2]));
	CPen* pOldPen = pDC->SelectObject(&cPen);

	//��ȥ��һ�λ��Ƶ���ʱԲ
	//�趨��Բ��y���꣬��ΪҪ��֤�����x֮�����y֮��
	m_OldPoint.y = m_OldPoint.x - m_startPoint.x + m_startPoint.y;
	pDC->Ellipse(CRect(m_startPoint, m_OldPoint));
	
	//������ʱԲ
	currentPoint.y = currentPoint.x - m_startPoint.x + m_startPoint.y;
	pDC->Ellipse(CRect(m_startPoint, currentPoint));

	m_OldPoint = currentPoint;

	pDC->SelectObject(pOldPen);

	//��ʾ�ܳ�������иĶ���������������������
/*	getLength(m_startPoint, currentPoint);
	getArea(m_startPoint, currentPoint);
	CString str;
	str.Format(CString("�뾶 = %.2f  �ܳ� = %.2f  ��� = %.2f"), r, length, area);
	pDC->SetTextColor(RGB(255, 0, 0));
	pDC->TextOutW(50, 300, str);
*/

//���ñ߽��
	r = abs(currentPoint.x - m_startPoint.x) / 2;
	CPoint point2, point3, point4;
	point2.x = m_startPoint.x + 2 * r;
	point2.y = m_startPoint.y;
	point3.x = m_startPoint.x + 2 * r;
	point3.y = m_startPoint.y + 2 * r;
	point4.x = m_startPoint.x;
	point4.y = m_startPoint.y + 2 * r;
	setBorderPoint(m_startPoint, point2, point3, point4);
}

void Circle::OnDraw(CDC* pDC, CPoint newStartPoint, CPoint NewEndPoint)
{
	int* color = getColor();
	CPen cPen;
	cPen.CreatePen(getLinear(), getLineWidth(), RGB(color[0], color[1], color[2]));
	pDC->SelectObject(&cPen);

	//��ȥ��һ�λ��Ƶ���ʱԲ
	//�趨��Բ��y���꣬��ΪҪ��֤�����x֮�����y֮��
	m_OldPoint.y = m_OldPoint.x - m_startPoint.x + m_startPoint.y;
	pDC->Ellipse(CRect(m_startPoint, m_OldPoint));
//	Echo(pDC, m_startPoint, m_OldPoint);

	//������ʱԲ
	NewEndPoint.y = NewEndPoint.x - newStartPoint.x + newStartPoint.y;
	pDC->Ellipse(CRect(newStartPoint, NewEndPoint));

	m_startPoint = newStartPoint;
	m_OldPoint = NewEndPoint;

	//��ʾ�ܳ�������иĶ�������������������������������
	/*
	getLength(newStartPoint, NewEndPoint);
	getArea(newStartPoint, NewEndPoint);
	CString str;
	str.Format(CString("�뾶 = %.2f  �ܳ� = %.2f  ��� = %.2f"), r, length, area);
	pDC->SetTextColor(RGB(255, 0, 0));
	pDC->TextOutW(50, 300, str);
	*/
	

//	Echo(pDC, newStartPoint, NewEndPoint);
}