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
			bool detectInput = true;
			std::string materialBar = "";
			std::string materialBarBg = "";
			std::string materialButton = "";
			Transform* buttonTr = nullptr;

			int width = 10, height = 10;
			int posX = 0, posY = 0;
			int barWidth = 10;
			int buttonWidth = 30;

			int barProgress = 100;

			Renderer::OgreRenderer* ogremanager = nullptr;
			Input::InputManager* inputmanager = nullptr;

			bool visible = true;
			Ogre::Overlay* overlayBar = nullptr;
			Ogre::OverlayContainer* superiorBar = nullptr;
			Ogre::OverlayContainer* inferiorBar = nullptr;
			Ogre::OverlayContainer* button = nullptr;
		public:
			void init()override;
			void update()override;
			void receiveMessage(Utilities::StringFormatter& s)override;
			void onSceneUp() override;
			void onSceneDown() override;
			void setVisibility(bool mode = true);

			inline int getProgress() { return barProgress; }
			inline int getBarWidth() { return barWidth; }
			inline int getMaxBarWidth() { return width; }
			void setProgress(int progress);
			void handleInput();
			void setDetectInput(bool mode);
			void setPos(int x, int y);
			void setDimensions(int w, int h);
			~Slider();

			const int MAX_VALUE = 100;
		};
	}
}
#endif