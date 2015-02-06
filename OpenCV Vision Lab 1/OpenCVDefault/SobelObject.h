#pragma once

#include "stdafx.h"
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

class SobelObject
{
public:
	SobelObject(void);
	SobelObject(int, int);
	~SobelObject(void);
	void MapFrom(bool*, Point);
	void SetPixel(Point, bool);
	bool GetPixel(Point);

private:
	Point GetXY(int);
	int GetIndex(Point);

private:
	bool* m_BoolObject;
	int m_Width;
	int m_Height;
};

