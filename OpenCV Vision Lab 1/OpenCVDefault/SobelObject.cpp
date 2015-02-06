#include "StdAfx.h"
#include "SobelObject.h"

SobelObject::SobelObject(void)
{
	m_Width = 0;
	m_Height = 0;
	m_BoolObject = new bool[0];
}

SobelObject::SobelObject(int Width, int Height)
{
	m_Width = Width;
	m_Height = Height;
	m_BoolObject = new bool[Width * Height];

	for (int i = 0; i < sizeof(m_BoolObject); i++)
		m_BoolObject[i] = false;
}

SobelObject::~SobelObject(void)
{
	delete m_BoolObject;
}

void SobelObject::MapFrom(bool* Image, Point Position)
{

}

void SobelObject::SetPixel(Point Position, bool Value)
{
	m_BoolObject[GetIndex(Position)] = Value;
}

bool SobelObject::GetPixel(Point Position)
{
	return m_BoolObject[GetIndex(Position)];
}

Point SobelObject::GetXY(int Index)
{
	return Point(Index % m_Width, Index / m_Height);
}

int SobelObject::GetIndex(Point Position)
{
	return Position.y * m_Width + Position.x;
}