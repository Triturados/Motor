#include "GameTime.h"


float GameTime::calculateFrameRate() {

	return frameCount / timeSinceStart * 1000;
}