// OpenCVDefault.cpp : définit le point d'entrée pour l'application console.

#include "stdafx.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <fstream> 
#include <conio.h>
#include <windows.h>

#include "Traitement.h"
#include "SimpleList.h"

using namespace std;
using namespace cv;

#define KEY_TAB 9
#define KEY_ENTER 13
#define KEY_SPACE 32
#define KEY_F 100
#define KEY_G 103
#define KEY_Q 113
#define KEY_R 114

bool m_IsGray;
bool m_DrawLine;
bool m_CamMode;
Mat m_Image;
string m_CurrentImagePath;
Point m_MousePos;
Scalar m_SelectedColor;
vector<int> m_CompressionParams;
VideoCapture m_Camera(0);	

void CallBackFunc(int event, int x, int y, int flags, void* userdata);
int update_keystate(int delay);
bool fexists(const char *filename);

int main(int argc, char** argv)
{
	Mat DisplayImage;
	string text;
	int fontFace = FONT_HERSHEY_SCRIPT_SIMPLEX;
	double fontScale = 1;
	int thickness = 1;  
	cv::Point textOrg(5, 50);
	int LastKey = 0;
	m_SelectedColor = Scalar(255, 255, 255);

	// Initialization

	m_IsGray = true;
	m_CamMode = false;
	m_DrawLine = false;
	m_CurrentImagePath = "";

	m_CompressionParams.push_back(CV_IMWRITE_PNG_COMPRESSION);
	m_CompressionParams.push_back(9);

	if(!m_Camera.isOpened())
	{		
		cout << "erreur load camera" << endl;
		return -1;
	}

	// Allow user to pick image

	cout << "Entrez le chemin de l'image a selectionner... (Appuyez sur Esc pour charger la derniere image)" << endl;

	while (LastKey != KEY_ENTER)
	{
		LastKey = getch();

		cout << (char)LastKey;

		if (LastKey != KEY_ENTER && LastKey != 8 && LastKey != 127)
			m_CurrentImagePath += (char)LastKey;
		else if (LastKey == 8 || LastKey == 127)
			m_CurrentImagePath = m_CurrentImagePath.substr(0, m_CurrentImagePath.size() - 1);

		if (LastKey == 27)
		{
			m_CurrentImagePath = "Circle.jpg";
			break;
		}
	}

	m_Image = imread(m_CurrentImagePath);
	imwrite("ScreenShot.png", m_Image, m_CompressionParams);
	m_CurrentImagePath = "ScreenShot.png";

	// Main Loop
	while(LastKey = update_keystate(1) >= 0)
	{
		ostringstream PosX;	
		ostringstream PosY;

		setMouseCallback("Image", CallBackFunc, NULL);
		PosX << m_MousePos.x;
		PosY << m_MousePos.y;

		text = "(" + PosX.str() + ", " + PosY.str() + ")";

		// Cam Mode
		if (m_CamMode)
			m_Camera >> m_Image;

		if (m_DrawLine)
		{
			line(m_Image, Point(0, 0), Point(m_Image.cols, m_Image.rows), Scalar(0, 0, 255));
		}

		if (m_CamMode)
		{
			if (m_IsGray)
				cvtColor(m_Image, m_Image, CV_RGB2GRAY);

			cv::putText(m_Image, text, textOrg, fontFace, fontScale, Scalar::all(255), thickness,8);
			imshow("Image", m_Image);
		}
		else
		{
			DisplayImage = (Mat)m_Image.clone();

			if (m_IsGray)
				cvtColor(DisplayImage, DisplayImage, CV_RGB2GRAY);

			cv::putText(DisplayImage, text, textOrg, fontFace, fontScale, Scalar::all(255), thickness,8);
			imshow("Image", DisplayImage);
		}

		if (GetAsyncKeyState(VK_RBUTTON) < 0)
			m_SelectedColor = Scalar(
				m_Image.at<cv::Vec3b>(m_MousePos.y, m_MousePos.x)[0],	// B
				m_Image.at<cv::Vec3b>(m_MousePos.y, m_MousePos.x)[1],	// G
				m_Image.at<cv::Vec3b>(m_MousePos.y, m_MousePos.x)[2]);	// R

		if (GetAsyncKeyState(VK_LBUTTON) < 0)
		{
			setMouseCallback("Image", CallBackFunc, NULL);
			CTraitement::DrawCross(m_Image, m_SelectedColor, m_MousePos);
			imwrite("ScreenShot.png", m_Image, m_CompressionParams);
		}
	}

	// the camera will be deinitialized automatically in VideoCapture destructor
	return 0;
}

void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
	m_MousePos = Point(x, y);
}

int update_keystate(int delay)
{
	switch(waitKey(delay))
	{
	case KEY_TAB: 
		m_CamMode = !m_CamMode;
		if (!m_CamMode)
			m_Image = imread(m_CurrentImagePath);
		break;

	case KEY_ENTER:
		m_CamMode = false;
		m_Camera >> m_Image;
		imwrite("ScreenShot.png", m_Image, m_CompressionParams);
		break;

	case KEY_SPACE: m_Image = NULL;
		break;

	case KEY_G : m_IsGray = !m_IsGray;
		break;

	case KEY_Q: return KEY_Q;
		break;

	case KEY_R:m_DrawLine = !m_DrawLine;
		break;

	case KEY_F: return KEY_F;
		break;
	}
	return 0;
}