#pragma once
#include "Point.h"
#include <iostream>
class Hexagon
{
	Point hex_;
	int icart_, jcart_;
	int xc_, yc_;
public:
	Hexagon(Point point, int icart, int jcart);
	void calcCenter();
	bool pointInHex(int x,int y);
	friend std::ostream& operator<< (std::ostream& os, const Hexagon hex);
};

