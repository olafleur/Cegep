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

template <class T>
class SimpleList
{
public:
	SimpleList(void);
	~SimpleList(void);

	T* GetList();
	T Get(int Index);
	void Add(T item);
	void Remove(int Index);
	void Modify(T item, int Index);
private:
	T* m_List;
};

