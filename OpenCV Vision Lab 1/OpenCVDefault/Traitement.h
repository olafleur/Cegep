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
#include "SimpleList.h"

using namespace std;
using namespace cv;

class CTraitement
{
	public:
		static void DrawCross(Mat Image, Scalar Color, Point Position);
		static void TurnGray(Mat Image);
		static Point* MarkCircles(Mat Image, int Edge = 16);
};
