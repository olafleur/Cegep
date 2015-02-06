// OpenCVDefault.cpp : définit le point d'entrée pour l'application console.

#include "stdafx.h"
#include "device_launch_parameters.h"
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

#define KEY_TAB 9
#define KEY_ENTER 13
#define KEY_SPACE 32
#define KEY_Q 113
#define KEY_R 114
#define F_DEFAULT 100
//#define VK_LBUTTON 1
//#define VK_RBUTTON 2
//#define VK_MBUTTON 4

bool DrawLine;
bool CamMode;
Mat Image;
string CurrentImagePath;
Point MousePos;
Scalar SelectedColor;

void CallBackFunc(int event, int x, int y, int flags, void* userdata);
int update_keystate(int delay);
bool fexists(const char *filename);

int main(int argc, char** argv)
{
	string text;
	int fontFace = FONT_HERSHEY_SCRIPT_SIMPLEX;
	double fontScale = 1;
	int thickness = 1;  
	cv::Point textOrg(5, 50);
	int LastKey = 0;
	vector<int> compression_params;
	SelectedColor = Scalar(255, 255, 255);

	// Initialization

	CamMode = true;
	DrawLine = false;
	CurrentImagePath = "";

	compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
	compression_params.push_back(9);

	VideoCapture capture(0);	
	if(!capture.isOpened())
	{		
		cout << "erreur load camera" << endl;
		return -1;
	}

	// Allow user to pick image

	cout << "Enter an image path..." << endl;

	while (LastKey != KEY_ENTER)
	{
		LastKey = getch();

		cout << (char)LastKey;

		// DOES NOT LIKE BACKSPACE
		if (LastKey != KEY_ENTER)
			CurrentImagePath += (char)LastKey;

		if (LastKey == 27)
		{
			CurrentImagePath = "Chat.png";
			break;
		}
	}

	// Main Loop

	while(waitKey(1))
	{
		ostringstream PosX;	
		ostringstream PosY;

		setMouseCallback("edges", CallBackFunc, NULL);
		PosX << MousePos.x;
		PosY << MousePos.y;

		text = "(" + PosX.str();
		text += ", " + PosY.str();
		text += ")";

		// Cam Mode
		if (CamMode)
			capture >> Image;

		if (DrawLine)
		{
			line(Image, Point(0, 0), Point(Image.cols, Image.rows), SelectedColor);
		}

		cv::putText(Image, text, textOrg, fontFace, fontScale, Scalar::all(255), thickness,8);
		imshow("edges", Image);

		// Key Check
		if (LastKey == KEY_ENTER)
			imwrite("ScreenShot.png", Image, compression_params);

		LastKey = update_keystate(1);

		if (GetAsyncKeyState(VK_RBUTTON) < 0)
		{
			SelectedColor = Scalar(Image.at<cv::Vec3b>(MousePos.y, MousePos.x)[0], Image.at<cv::Vec3b>(MousePos.y, MousePos.x)[1], Image.at<cv::Vec3b>(MousePos.y, MousePos.x)[2]);
		}

		if (GetAsyncKeyState(VK_LBUTTON) < 0)
		{
			setMouseCallback("edges", CallBackFunc, NULL);
			line(Image, Point(MousePos.x - 10, MousePos.y), Point(MousePos.x + 10, MousePos.y), SelectedColor);
			line(Image, Point(MousePos.x, MousePos.y - 10), Point(MousePos.x, MousePos.y + 10), SelectedColor);
		}

	}

	// the camera will be deinitialized automatically in VideoCapture destructor
	return 0;
}

void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
	MousePos = Point(x, y);
}

int update_keystate(int delay)
{
	switch(waitKey(delay))
	{
	case KEY_TAB: 
		CamMode = !CamMode;
		if (!CamMode)
		{
			Image = imread(CurrentImagePath);
		}
		break;
	case KEY_ENTER: return KEY_ENTER;
		break;
	case KEY_SPACE: Image = NULL;
		break;
	case KEY_Q: return KEY_Q;
		break;
	case KEY_R:DrawLine = !DrawLine;
		break;
	case F_DEFAULT: return F_DEFAULT;
		break;
	}
	return 0;
}