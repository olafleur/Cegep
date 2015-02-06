#include "StdAfx.h"
#include "Traitement.h"

void CTraitement::DrawCross(Mat Image, Scalar Color, Point Position)
{
	line(Image, Point(Position.x - 10, Position.y), Point(Position.x + 10, Position.y), Color);
	line(Image, Point(Position.x, Position.y - 10), Point(Position.x, Position.y + 10), Color);
}