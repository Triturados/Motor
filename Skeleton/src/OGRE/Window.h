#pragma once
#include <Vector2.h>
#include <../Export.h>

namespace LoveEngine {

	enum class lovexport  MouseState {
		FREE, INSIDE_WINDOW, CENTER
	};

	namespace Renderer {
		class OgreRenderer;
	}

	class lovexport Window {
	private:
		static Window* instance;

		bool _mouseVisibility;
		bool currentlyFullScreen;
		MouseState currentMouseState;
		Utilities::Vector2<int> windowSize;
		Renderer::OgreRenderer* renderer;
	public:
		static Window* getInstance();
		Window(Renderer::OgreRenderer* ogrerenderer);
		void setMouseState(MouseState value);
		void mouseVisibility(bool value);
		void setWindowTitle(std::string );
		void setFullScreen(bool screenmode);

		void setWindowSize(Utilities::Vector2<int> size);

		std::string getWindowTitle();
		MouseState getMouseState();
		bool isFullScreen();
		bool isMouseVisible();

		void repositionWindow(Utilities::Vector2<int> pos);

		void lockMouse();
		void freeMouse();

		Utilities::Vector2<int> getWindowSize();
	};
}