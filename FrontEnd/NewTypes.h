#pragma once
#include <glm.hpp>
enum streetTypes
{
	singleDotted,
	singleContinuous,
	doubleDotted,
	doubleContinuous

};

struct SuperPipeLine
{
	glm::vec2 nextPosition;
	float nextRotation;
};

struct _position
{
	double x;
	double y;

};
struct Point
{
	int x = 1;
	int y = 1;
	int tag = 1;
};