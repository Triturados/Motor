#pragma once
#include <../Export.h>

#ifndef BUTTON_H	
#define BUTTON_H

#include <Component.h>
#include <string>
#include <functional>

namespace Ogre {
	class Overlay;
	class OverlayContainer;
}

namespace LoveEngine {

	namespace Renderer {
		class OgreRenderer;
	}

	namespace Input {
		class InputManager;
	}

	namespace ECS {

		class Transform;
		class lovexport Button : public Component
		{
		private:
			bool detectInput = true;
			std::string materialBarBg = "";

			int width = 10, height = 10;
			int posX = 0, posY = 0;

			Renderer::OgreRenderer* ogremanager = nullptr;
			Input::InputManager* inputmanager = nullptr;

			bool visible = true;
			Ogre::Overlay* overlayBar = nullptr;
			Ogre::OverlayContainer* button = nullptr;

			std::function<void()> lambda;
		public:
			void init()override;
			void update()override;
			void receiveMessage(Utilities::StringFormatter& s)override;
			void onSceneUp() override;
			void onSceneDown() override;
			void setVisibility(bool mode = true);

			void handleInput();
			void setDetectInput(bool mode);
			void setPos(int x, int y);
			void setDimensions(int w, int h);
			void setLambda(std::function<void()> l);
			~Button();

			const int MAX_VALUE = 100;
		};
	}
}
#endif