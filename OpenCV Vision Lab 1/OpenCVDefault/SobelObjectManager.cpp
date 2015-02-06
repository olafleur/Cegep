#include "StdAfx.h"
#include "SobelObjectManager.h"

SobelObjectManager::SobelObjectManager(Mat BaseImage, int Edge)
{
	m_BaseImage = BaseImage;
	m_Edge = Edge;

	Initialize();
}

SobelObjectManager::~SobelObjectManager(void)
{
	delete m_BoolImage;
}

void SobelObjectManager::Initialize(void)
{
	Scalar colour;
	Scalar colourTop;
	Scalar colourBack;

	m_SobelObjects = new SobelObject[0];
	m_BoolImage = new bool[m_BaseImage.cols * m_BaseImage.rows];

	for (int i = 0; i < sizeof(m_BoolImage); i++)
		m_BoolImage[i] = false;

	for (int col = 1; col < m_BaseImage.cols - 1; col++)
		for (int row = 1; row < m_BaseImage.rows - 1; row++)
		{
			colour = m_BaseImage.at<uchar>(Point(col, row));
			colourTop = m_BaseImage.at<uchar>(Point(col - 1, row));
			colourBack = m_BaseImage.at<uchar>(Point(col, row - 1));

			if (abs(colour[0] - colourTop[0]) > m_Edge || abs(colour[0] - colourBack[0]) > m_Edge)
				m_BoolImage[GetIndex(Point(col, row))] = true;
			else
				m_BoolImage[GetIndex(Point(col, row))] = false;
		}

	FindObjects();
}

void SobelObjectManager::FindObjects(void)
{
	// For every white pixel, attempt to create a SobelObject at it
	for (int col = 1; col < m_BaseImage.cols - 1; col++)
		for (int row = 1; row < m_BaseImage.rows - 1; row++)
			if (m_BoolImage[GetIndex(Point(col, row))])
				MapObjectFrom(Point(col, row));
}

void SobelObjectManager::MapObjectFrom(Point Position)
{
	SobelObject NewSobelObject;
	SobelObject* OldSobelObjects;

	// Check if the object has been mapped before
	for (int i = 0; i < sizeof(m_SobelObjects); i++)
		if (m_SobelObjects[i].GetPixel(Position))
			return;

	OldSobelObjects = m_SobelObjects;
	m_SobelObjects = new SobelObject[sizeof(OldSobelObjects) + 1];

	// 
	NewSobelObject = SobelObject(m_BaseImage.cols, m_BaseImage.rows);
	NewSobelObject.MapFrom(m_BoolImage, Position);

	for (int i = 0; i < sizeof(OldSobelObjects); i++)
		m_SobelObjects[i] = OldSobelObjects[i];

	m_SobelObjects[sizeof(OldSobelObjects)] = NewSobelObject;
}

Point SobelObjectManager::GetXY(int Index)
{
	return Point(Index % m_BaseImage.cols, Index / m_BaseImage.rows);
}

int SobelObjectManager::GetIndex(Point Position)
{
	return Position.y * m_BaseImage.cols + Position.x;
}