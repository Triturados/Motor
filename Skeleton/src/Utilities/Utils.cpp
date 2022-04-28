#include "Utils.h"
#include <cmath>

float LoveEngine::Utilities::cubicEaseOut(float t)
{
	float inv = 1 - t;
	return 1 - (inv * inv * inv);
}

float LoveEngine::Utilities::lerp(float a, float b, float t)
{
	return (1 - t) * a + t * b;
}

float LoveEngine::Utilities::abs(float a)
{
	return std::abs(a);
}

int LoveEngine::Utilities::sign(float a)
{
	if (a > 0)
		return 1;
	if (a < 0)
		return -1;
	return 0;
}
