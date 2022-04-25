#include "LUAfunctionality.h"
#include <Window.h>
#include <random>
#include <iostream>

namespace LoveEngine {

	void setWindowSize(int x, int y) {
		Window::getInstance()->setWindowSize(x, y);
	}

	int getWidth() {
		return Window::getInstance()->getWindowSize().x;
	}
	int getHeight() {
		return Window::getInstance()->getWindowSize().y;
	}

	std::string getWindowTitle() {
		return Window::getInstance()->getWindowTitle();
	}

	void setWindowTitle(std::string s) {
		Window::getInstance()->setWindowTitle(s);
	}

	void setFullScreen(bool val) {
		Window::getInstance()->setFullScreen(val);
	}

	void setIcon(std::string val) {
		Window::getInstance()->setWindowIcon(val);
	}

	float random()
	{
		return rand() % 1000 / 1000.0;
	}

	int randomBetween(int min, int max)
	{
		int dif = max - min;
		int r = rand() % dif;
		return min + r;
	}

	void print(std::string mssg) {
		std::cout << mssg << "\n";
	}

	int round(float t) {
		return std::round(t);
	}

	int floor(float t) {
		return std::floor(t);
	}

	int ceil(float t) {
		return std::ceil(t);
	}
}