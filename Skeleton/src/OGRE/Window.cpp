#include "Window.h"
#include "OgreRenderer.h"
#include "OgreRenderWindow.h"
#include "SDL.h"
#include "SDL_video.h"
namespace LoveEngine {

	Window* Window::instance = nullptr;
	Window* Window::getInstance()
	{
		if (instance == nullptr)
		{
			instance = Renderer::OgreRenderer::getInstance()->getWindowInfo();
		}
		return instance;
	}

	Window::Window(Renderer::OgreRenderer* ogrerenderer)
	{
		auto renderwindow = ogrerenderer->getRenderWindow();

		Window::instance = this;
		renderer = ogrerenderer;
		
		currentlyFullScreen = renderwindow->isFullScreen();
		currentMouseState = MouseState::FREE;
		_mouseVisibility = true;

		windowSize = Utilities::Vector2<int>(renderwindow->getWidth(), renderwindow->getHeight());
	}

	//TODO
	void LoveEngine::Window::setMouseState(MouseState value)
	{
		if (value == currentMouseState)
			return;


		currentMouseState = value;
	}

	MouseState Window::getMouseState()
	{
		return currentMouseState;
	}

	void LoveEngine::Window::mouseVisibility(bool value)
	{
		if (_mouseVisibility == value)
			return;

		_mouseVisibility = value;

		int toggle = _mouseVisibility ? SDL_ENABLE : SDL_DISABLE;
		SDL_ShowCursor(toggle);
	}

	void LoveEngine::Window::setWindowTitle(std::string name)
	{
		renderer->changeWindowTitle(name);
	}

	std::string LoveEngine::Window::getWindowTitle()
	{
		return renderer->getWindowTitle();
	}

	void LoveEngine::Window::setFullScreen(bool screenmode)
	{
		if (currentlyFullScreen == screenmode) {
			return;
		}
		currentlyFullScreen = screenmode;

		renderer->setFullScreen(screenmode);
	}

	void Window::setWindowSize(Utilities::Vector2<int> size)
	{
		windowSize = size;
		renderer->resizeWindow(size);
	}

	void Window::setWindowSize(int x, int y)
	{
		windowSize = Utilities::Vector2<int>(x, y);
		renderer->resizeWindow(x, y);
	}


	bool LoveEngine::Window::isFullScreen()
	{
		return currentlyFullScreen;
	}

	bool Window::isMouseVisible()
	{
		return _mouseVisibility;
	}

	void Window::repositionWindow(Utilities::Vector2<int> pos)
	{
		repositionWindow(pos.x, pos.y);
	}
	void Window::repositionWindow(int x, int y)
	{
		renderer->repositionWindow(x, y);
	}

	void Window::setWindowIcon(std::string iconPath)
	{
		renderer->setWindowIcon(iconPath);
	}

	void Window::lockMouse()
	{
		setMouseState(MouseState::CENTER);
	}

	void Window::freeMouse()
	{
		setMouseState(MouseState::FREE);
	}

	Utilities::Vector2<int> LoveEngine::Window::getWindowSize()
	{
		return windowSize;
	}
}

