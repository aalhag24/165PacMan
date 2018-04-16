#pragma once
#ifndef Rect_h
#define Rect_h

#include <freeglut.h>
#include "XY.h"
#include <vector>

using namespace std;

class Rect {
	XY tl, bl, tr, br, center;
public:
	Rect() {}
	Rect(XY topLeft, XY topRight, XY botLeft, XY botRight) {
		tl = topLeft;
		bl = botLeft;
		tr = topRight;
		br = botRight;
	}
	Rect(XY cent, double h, double w) {
		center = cent;
		tl.setX(center.getX() - w / 2);
		tl.setY(center.getY() + h / 2);
		tr.setX(center.getX() + w / 2);
		tr.setY(center.getY() + h / 2);
		bl.setX(center.getX() - w / 2);
		bl.setY(center.getY() - h / 2);
		br.setX(center.getX() + w / 2);
		br.setY(center.getY() - h / 2);
	}
	XY getTL() {
		return tl;
	}
	XY getTR() {
		return tr;
	}
	XY getBL() {
		return bl;
	}
	XY getBR() {
		return br;
	}
	XY getCenter() {
		return center;
	}
	~Rect() {}
};
#endif // !Rect_h
