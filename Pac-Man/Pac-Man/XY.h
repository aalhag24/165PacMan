#pragma once
#ifndef Xy_h
#define XY_h

class XY {
	double x, y;
public:
	XY() {
		x = 0;
		y = 0;
	}
	XY(double x_c, double y_c) {
		x = x_c;
		y = y_c;
	}
	~XY(){}
	double getX() {
		return x;
	}
	double getY() {
		return y;
	}
	void setX(double x_c) {
		x = x_c;
	}
	void setY(double y_c) {
		y = y_c;
	}
	void draw() {
		glVertex2d(x, y);
	}
};
#endif // !Xy_h
