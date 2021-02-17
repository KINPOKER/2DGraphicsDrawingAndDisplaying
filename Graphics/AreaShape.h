#pragma once
#include "Shape.h"

const double PI = 3.1415926535897932;

using namespace std;

class AreaShape : public Shape
{
private:
	float area = 0.0;
	float length = 0.0;

public:
	virtual float getLength();
	virtual float getArea();

	virtual void OnDraw(CDC* pDC);
};

