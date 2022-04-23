#pragma once
#include <string>
namespace LoveEngine {

	void setWindowSize(int x, int y);

	int getWidth();

	int getHeight();

	std::string getWindowTitle();

	void setWindowTitle(std::string);

	void setFullScreen(bool);

	void setIcon(std::string);

	float random(); // 0 - 1
	int randomBetween(int min, int max); //exclusive
}