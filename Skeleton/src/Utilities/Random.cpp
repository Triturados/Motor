#include "Random.h"
#include <random>

float LoveEngine::Utilities::Random::random()
{
	return rand() % 1000 / 1000.0;
}

int LoveEngine::Utilities::Random::randomBetween(int min, int max)
{
	int dif = max - min;
	int r = rand() % dif;
	return min + r;
}
