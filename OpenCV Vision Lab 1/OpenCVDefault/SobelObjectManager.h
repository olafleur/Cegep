#pragma once

#include "stdafx.h"
#include "SobelObject.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <fstream> 
#include <conio.h>
#include <windows.h>

using namespace std;
using namespace cv;

class SobelObjectManager
{
	// Functions
public:
	SobelObjectManager(Mat, int Edge = 16);
	~SobelObjectManager(void);

private:
	void Initialize(void);
	void FindObjects(void);
	void MapObjectFrom(Point);
	Point GetXY(int);
	int GetIndex(Point);

	// Variables
private:
	SobelObject* m_SobelObjects;
	bool* m_BoolImage;
	Mat m_BaseImage;
	int m_Edge;
};