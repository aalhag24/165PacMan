#pragma once
#ifndef Wall_h
#define Wall_h
#include <freeglut.h>
#include <vector>
#include "XY.h"
#include "Rect.h"
#include <iostream>

using namespace std;

class Wall {
	vector<vector<Rect> > points;
	double h = 1, w = 1;
	vector<XY> there, back;
public:
	Wall() {}
	Wall(vector<vector<Rect> > in_points) {
		points = in_points;
	}
	void addPoint(Rect n_point) {
		vector<Rect> temp;
		temp.push_back(n_point);
		points.push_back(temp);
	}
	void addLeg(XY center) {
		points.end()->push_back(Rect(center, h, w));
	}
	void drawInit() {
		//get init points
		Rect temp = *points.begin()->begin();
		double x = temp.getCenter().getX();
		double y = temp.getCenter().getY();
		//if leg
		if (points.at(1).size() > 1) {
			Rect leg = points.at(1).at(1);
			double legX = leg.getCenter().getX();
			double legY = leg.getCenter().getY();
			//going left
			if (x > leg.getCenter().getX()) {
				there.push_back(temp.getTR());
				there.push_back(temp.getBR());
				back.push_back(temp.getTR());
			}
			//going right
			else if (x < leg.getCenter().getX()) {
				there.push_back(temp.getBL());
				there.push_back(temp.getBR());
				back.push_back(temp.getBL());
			}
			//going up
			else if (y < leg.getCenter().getY()) {
				there.push_back(temp.getBR());
				there.push_back(temp.getBL());
				back.push_back(temp.getBR());
			}
			//going down
			else if (y > leg.getCenter().getY()) {
				there.push_back(temp.getTL());
				there.push_back(temp.getTR());
				back.push_back(temp.getTL());
			}
		}
		//no leg
		else {
			//going left
			if (x > points.at(1).begin()->getCenter().getX()) {
				there.push_back(temp.getTR());
				there.push_back(temp.getBR());
				back.push_back(temp.getTR());
			}
			//going right
			else if (x < points.at(1).begin()->getCenter().getX()) {
				there.push_back(temp.getBL());
				there.push_back(temp.getBR());
				back.push_back(temp.getBL());
			}
			//going up
			else if (y < points.at(1).begin()->getCenter().getY()) {
				there.push_back(temp.getBR());
				there.push_back(temp.getBL());
				back.push_back(temp.getBR());
			}
			//going down
			else if (y > points.at(1).begin()->getCenter().getY()) {
				there.push_back(temp.getTL());
				there.push_back(temp.getTR());
				back.push_back(temp.getTL());
			}
		}
		//fill in other points
		for (int i = 1; i < points.size(); i++) {
			temp = *points.at(i).begin();
			x = temp.getCenter().getX();
			y = temp.getCenter().getY();
			//if leg
			if (points.at(i).size() > 1) {
				Rect leg = points.at(i).at(1);
				double legX = leg.getCenter().getX();
				double legY = leg.getCenter().getY();
				//going left
				if (x > leg.getCenter().getX()) {
					//from the right
					if (x < points.at(i - 1).begin()->getCenter().getX()) {
						//bottom leg
						if (legY < y) {
							there.push_back(temp.getBR());
							there.push_back(leg.getBR());
							there.push_back(leg.getBL());
							there.push_back(temp.getBL());
						}
						//top leg
						else if (legY > y) {
							back.push_back(temp.getTL());
							back.push_back(leg.getTL());
							back.push_back(leg.getTR());
							back.push_back(temp.getTR());
						}
						else {
							cout << "Invalid leg" << endl;
						}
					}
					//from above
					else if (y < points.at(i - 1).begin()->getCenter().getX()) {
						//right leg
						if (legX > x) {
							there.push_back(temp.getTR());
							there.push_back(leg.getTR());
							there.push_back(leg.getBR());
						}
						//bottom leg
						else if (legY < y) {
							there.push_back(leg.getBR());
							there.push_back(leg.getBL());
							there.push_back(temp.getBL());
						}
						else {
							cout << "Invalid leg" << endl;
						}
						back.push_back(temp.getTL());
					}
					//from below
					else if (y > points.at(i - 1).begin()->getCenter().getX()) {
						//right leg
						if (legX > x) {
							back.push_back(leg.getTR());
							back.push_back(leg.getBR());
							back.push_back(temp.getBR());
						}
						//top leg
						else if (legY > y) {
							back.push_back(temp.getTL());
							back.push_back(leg.getTL());
							back.push_back(leg.getTR());
						}
						else {
							cout << "Invalid leg" << endl;
						}
						there.push_back(temp.getBL());
					}
				}
				//going right
				else if (x < leg.getCenter().getX()) {
					//from the left
					if (x > points.at(i - 1).begin()->getCenter().getX()) {
						//bottom leg
						if (legY < y) {
							back.push_back(temp.getBR());
							back.push_back(leg.getBR());
							back.push_back(leg.getBL());
							back.push_back(temp.getBL());
						}
						//top leg
						else if (legY > y) {
							there.push_back(temp.getTL());
							there.push_back(leg.getTL());
							there.push_back(leg.getTR());
							there.push_back(temp.getTR());
						}
						else {
							cout << "Invalid leg" << endl;
						}
					}
					//from above
					else if (y < points.at(i - 1).begin()->getCenter().getX()) {
						//left leg
						if (legX < x) {
							back.push_back(leg.getBL());
							back.push_back(leg.getTL());
							back.push_back(temp.getTL());
						}
						//bottom leg
						else if (legY < y) {
							back.push_back(temp.getBR());
							back.push_back(leg.getBR());
							back.push_back(leg.getBL());
						}
						else {
							cout << "Invalid leg" << endl;
						}
						there.push_back(temp.getTR());
					}
					//from below
					else if (y > points.at(i - 1).begin()->getCenter().getX()) {
						//left leg
						if (legX < x) {
							there.push_back(temp.getBL());
							there.push_back(leg.getBL());
							there.push_back(leg.getTL());
						}
						//top leg
						else if (legY > y) {
							there.push_back(leg.getTL());
							there.push_back(leg.getTR());
							there.push_back(temp.getTR());
						}
						else {
							cout << "Invalid leg" << endl;
						}
						back.push_back(temp.getBR());
					}
				}
				//going up
				else if (y < leg.getCenter().getY()) {
					//from the right
					if (x < points.at(i - 1).begin()->getCenter().getX()) {
						//bottom leg
						if (legY < y) {
							there.push_back(temp.getBR());
							there.push_back(leg.getBR());
							there.push_back(leg.getBL());
						}
						//left leg
						else if (legX < x) {
							there.push_back(leg.getBL());
							there.push_back(leg.getTL());
							there.push_back(temp.getTL());
						}
						else {
							cout << "Invalid leg" << endl;
						}
						back.push_back(temp.getTR());
					}
					//from the left
					else if (x > points.at(i - 1).begin()->getCenter().getX()) {
						//bottom leg
						if (legY < y) {
							back.push_back(temp.getBL());
							back.push_back(leg.getBL());
							back.push_back(leg.getBR());
						}
						//right leg
						else if (legX > x) {
							back.push_back(leg.getBR());
							back.push_back(leg.getTR());
							back.push_back(temp.getTR());
						}
						else {
							cout << "Invalid leg" << endl;
						}
						there.push_back(temp.getTL());
					}
					//from below
					else if (y > points.at(i - 1).begin()->getCenter().getX()) {
						//right leg
						if (legX > x) {
							there.push_back(temp.getTR());
							there.push_back(leg.getTR());
							there.push_back(leg.getBR());
							there.push_back(temp.getBR());
						}
						//left leg
						else if (legX < x) {
							back.push_back(temp.getBL());
							back.push_back(leg.getBL());
							back.push_back(leg.getTL());
							back.push_back(temp.getTL());
						}
						else {
							cout << "Invalid leg" << endl;
						}
					}
				}
				//going down
				else if (y > leg.getCenter().getY()) {
					//from the right
					if (x < points.at(i - 1).begin()->getCenter().getX()) {
						//top leg
						if (legY > y) {
							back.push_back(leg.getTL());
							back.push_back(leg.getTR());
							back.push_back(temp.getTR());
						}
						//left leg
						else if (legX < x) {
							back.push_back(temp.getBL());
							back.push_back(leg.getBL());
							back.push_back(leg.getTL());
						}
						else {
							cout << "Invalid leg" << endl;
						}
						there.push_back(temp.getBR());
					}
					//from the left
					else if (x > points.at(i - 1).begin()->getCenter().getX()) {
						//top leg
						if (legY > y) {
							there.push_back(temp.getTL());
							there.push_back(leg.getTL());
							there.push_back(leg.getTR());
						}
						//right leg
						else if (legX > x) {
							there.push_back(leg.getTR());
							there.push_back(leg.getBR());
							there.push_back(temp.getBR());
						}
						else {
							cout << "Invalid leg" << endl;
						}
						back.push_back(temp.getBL());
					}
					//from above
					else if (y < points.at(i - 1).begin()->getCenter().getX()) {
						//right leg
						if (legX > x) {
							there.push_back(temp.getTR());
							there.push_back(leg.getTR());
							there.push_back(leg.getBR());
							there.push_back(temp.getBR());
						}
						//left leg
						if (legX < x) {
							back.push_back(temp.getBL());
							back.push_back(leg.getBL());
							back.push_back(leg.getTL());
							back.push_back(temp.getTL());
						}
						else {
							cout << "Invalid leg" << endl;
						}
					}
				}
			}
			//no leg
			//going left
			else if (x > points.at(i + 1).begin()->getCenter().getX()) {
				if (x < points.at(i - 1).begin()->getCenter().getX()) { //from the right
																	  //back.push_back(temp.getTL());
				}
				else if (y < points.at(i - 1).begin()->getCenter().getX()) { //from above
					there.push_back(temp.getBR());
					back.push_back(temp.getTL());
				}
				else if (y > points.at(i - 1).begin()->getCenter().getX()) { //from below
					there.push_back(temp.getBL());
					back.push_back(temp.getTR());
				}
			}
			//going right
			else if (x < points.at(i + 1).begin()->getCenter().getX()) {
				if (x > points.at(i - 1).begin()->getCenter().getX()) { // from the left
																	  //back.push_back(temp.getTR());
				}
				else if (y < points.at(i - 1).begin()->getCenter().getX()) { //from above
					there.push_back(temp.getTR());
					back.push_back(temp.getBL());
				}
				else if (y > points.at(i - 1).begin()->getCenter().getX()) { //from below
					there.push_back(temp.getTL());
					back.push_back(temp.getBR());
				}
			}
			//going up
			else if (y < points.at(i + 1).begin()->getCenter().getY()) {
				if (x < points.at(i - 1).begin()->getCenter().getX()) { //from the right
					there.push_back(temp.getBL());
					back.push_back(temp.getTR());
				}
				else if (x > points.at(i - 1).begin()->getCenter().getX()) { //from the left
					there.push_back(temp.getTL());
					back.push_back(temp.getBR());
				}
				else if (y > points.at(i - 1).begin()->getCenter().getX()) { //from below
																		   //back.push_back(temp.getTR());
				}
			}
			//going down
			else if (y > points.at(i + 1).begin()->getCenter().getY()) {
				if (x < points.at(i - 1).begin()->getCenter().getX()) { //from the right
					there.push_back(temp.getBR());
					back.push_back(temp.getTL());
				}
				else if (x > points.at(i - 1).begin()->getCenter().getX()) { //from the left
					there.push_back(temp.getTR());
					back.push_back(temp.getBL());
				}
				else if (y < points.at(i - 1).begin()->getCenter().getX()) { //from above
																		   //back.push_back(temp.getBL());
				}
			}
		}

	}
	void draw() { 
		glBegin(GL_LINES);
		there.begin()->draw();
		for (int i = 1; i < there.size(); i++) {
			there.at(i).draw();
			there.at(i).draw();
		}
		back.end()->draw();
		for (int i = back.size()-1; i >= 0; i--) {
			back.at(i).draw();
			back.at(i).draw();
		}
		glEnd();
	}
	~Wall() {};
};
#endif
