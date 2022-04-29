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
			std::string material = "";

			Utilities::Vector3<int>* pos;
			Utilities::Vector2<int>* dimensions;

			Renderer::OgreRenderer* ogremanager = nullptr;
			Input::InputManager* inputmanager = nullptr;

			bool visible = true;
			Ogre::Overlay* overlayBar = nullptr;
			Ogre::OverlayContainer* button = nullptr;
			
			bool interactable;
			std::function<void()> lambda;
		public:
			Button();
			~Button();

			void init()override;
			void update()override;
			void receiveMessage(Utilities::StringFormatter& s)override;
			void onSceneUp() override;
			void onSceneDown() override;
			void setVisibility(bool mode = true);
			
			void setInteractable(bool);
			bool isInteractable();
			void handleInput();
			Utilities::Vector3<int> getPos();

			Utilities::Vector2<int> getSize();
			void setSize(Utilities::Vector2<int>);

			void setPos(Utilities::Vector3<int> pos_);
			void onClick(std::function<void()> l);

			const int MAX_VALUE = 100;
		};
	}
}
#endif