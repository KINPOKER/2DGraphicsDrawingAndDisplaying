#include "pch.h"
#include "LineShape.h"

#include <string>
#include <math.h>
#include <iostream>
#include <stdio.h>

using namespace std;

float LineShape::getLength() {
	return length;
}
CPoint LineShape::getFirstPoint() {
	return firstPoint;
}
CPoint LineShape::getEndPoint() {
	return endPoint;
}

void LineShape::setFirstPoint(CPoint point) {
	firstPoint = point;
}
void LineShape::setEndPoint(CPoint point) {
	endPoint = point;
}

void LineShape::OnDraw(CDC* pDC) {
	pDC->MoveTo(firstPoint);
	pDC->LineTo(endPoint);
}

