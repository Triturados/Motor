#include "Utils.h"


float LoveEngine::Utilities::cubicEaseOut(float t)
{
	float inv = 1 - t;
	return 1 - (inv * inv * inv);
}

float LoveEngine::Utilities::lerp(float a, float b, float t)
{
	return (1 - t) * a + t * b;
}
