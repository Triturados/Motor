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

	namespace Utilities {
		template<typename T>
		class Vector3;
		template<typename T>
		class Vector2;
	}

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
			std::string material = "";

			Utilities::Vector3<int>* pos;
			Utilities::Vector2<int>* dimensions;

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
			Utilities::Vector3<int> getPos();
			void setPos(Utilities::Vector3<int> pos_);
			void setDimensions(Utilities::Vector2<int> dimensions_);
			void onClick(std::function<void()> l);
			Button();
			~Button();

			const int MAX_VALUE = 100;
		};
	}
}
#endif