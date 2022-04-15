#pragma once
#include <../Export.h>

#ifndef SLIDER_H	
#define SLIDER_H

#include <Component.h>
#include <string>

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

		class lovexport Slider : public Component
		{
		private:
			bool tracking = false;
			const int MAX_VALUE = 100;
			std::string materialBar = "";
			std::string materialBarBg = "";
			std::string materialButton = "";
			Transform* buttonTr = nullptr;

			int width = 10, height = 10;
			int posX = 0, posY = 0;
			int buttonWidth = 30;

			Renderer::OgreRenderer* ogremanager;
			Input::InputManager* inputmanager;

			bool visible = true;
			Ogre::Overlay* overlayBar, *overlayBarBg;
			Ogre::OverlayContainer* superiorBar;
			Ogre::OverlayContainer* inferiorBar;
			Ogre::OverlayContainer* button;
		public:
			void init()override;
			void update()override;
			void receiveMessage(Utilities::StringFormatter& s)override;
			void onSceneUp() override;
			void onSceneDown() override;
			void setVisibility(bool mode = true);
			~Slider();
		};
	}
}
#endif