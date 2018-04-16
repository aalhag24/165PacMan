#pragma once
#ifndef Border_h
#define Border_h

#include "Wall.h"

class Border : public Wall {
	double h = 0.5, w = 0.5;
	vector<vector<Rect> > points;
	vector<XY> there, back;
public:
	Border() {}
	Border(vector<vector<Rect> > n_points) {
		points = n_points;
	}
	void addLeg(XY center) {
		points.end()->push_back(Rect(center, h*2, w*2));
	}
};
#endif // !Border_h
