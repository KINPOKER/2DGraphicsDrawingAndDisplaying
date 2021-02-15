#pragma once
#include "Shape.h"

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

