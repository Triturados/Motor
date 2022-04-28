#include "Utils.h"
#include <iostream>
#include <cmath>
#include <Vector2.h>
#include <Vector3.h>

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

void LoveEngine::Utilities::breakpoint()
{
	std::cout << "Breakpoint started\n";
}

using namespace LoveEngine::Utilities;
LoveEngine::Utilities::Vector3<int> LoveEngine::Utilities::Vec2toVec3Int(Vector2<int> const& v)
{
	return Vector3<int>(v.x, v.y, 0);
}

LoveEngine::Utilities::Vector2<int> LoveEngine::Utilities::Vec3toVec2Int(Vector3<int> const& v)
{
	return Vector2<int>(v.x, v.y);
}

LoveEngine::Utilities::Vector3<float> LoveEngine::Utilities::Vec2toVec3(Vector2<float> const& v)
{
	return Vector3<float>(v.x, v.y, 0);
}

LoveEngine::Utilities::Vector2<float> LoveEngine::Utilities::Vec3toVec2(Vector3<float> const& v)
{
	return Vector2<float>(v.x, v.y);
}
