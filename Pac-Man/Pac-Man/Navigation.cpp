#include "stdafx.h"
#include "Navigation.h"

Navigation::Navigation()
{
}

Navigation::~Navigation()
{
}

void Navigation::Initialize(){
	ifstream inFile;
	int Num, ID; float XVal, YVal;
	ifstream myfile("Nodes.txt", ios::out | ios::binary);

	if (!myfile.is_open()) {
		cout << "Unable to open file";
		exit(1);
	}

	while (myfile.is_open()) {
		myfile >> Num >> XVal;
		for (int i = 0; i < Num; i++) {
			myfile >> ID >> YVal;
			//Add Node ID, XVal, YVal;
		}
	}

	inFile.close();
}

void Navigation::XInc()
{
}

void Navigation::XDec()
{
}

void Navigation::YInc()
{
}

void Navigation::YDec()
{
}

void Navigation::Idle()
{
}
