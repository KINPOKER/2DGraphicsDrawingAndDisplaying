#include "pch.h"
#include "Circle.h"

float Circle::getArea() {
	r = sqrt(pow((currentPoint.x - m_startPoint.x), 2) * 2);
	area = (pow(r, 2)) * PI;
	return area;
}

float Circle::getLength() {
	r = sqrt(pow((currentPoint.x - m_startPoint.x), 2) * 2);
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
	pDC->SelectObject(&cPen);

	//��ȥ��һ�λ��Ƶ���ʱԲ
	//�趨��Բ��y���꣬��ΪҪ��֤�����x֮�����y֮��
	m_OldPoint.y = m_OldPoint.x - m_startPoint.x + m_startPoint.y;
	pDC->Ellipse(CRect(m_startPoint, m_OldPoint));
	
	//������ʱԲ
	currentPoint.y = currentPoint.x - m_startPoint.x + m_startPoint.y;
	pDC->Ellipse(CRect(m_startPoint, currentPoint));

	m_OldPoint = currentPoint;

	//��ʾ�ܳ����
	getLength();
	getArea();
	CString str;
	str.Format(CString("�뾶 = %.2f  �ܳ� = %.2f  ��� = %.2f"), r, length, area);
	pDC->SetTextColor(RGB(255, 0, 0));
	pDC->TextOutW(50, 300, str);
}