#pragma once
#include <../Export.h>

#ifndef BUTTON_H	
#define BUTTON_H

#include <string>
#include <functional>
#include <UIElement.h>

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
		class lovexport Button : public UIElement
		{
		private:
			std::string material = "";

			Renderer::OgreRenderer* ogremanager;
			Input::InputManager* inputmanager;

			bool visible = true;
			Ogre::Overlay* overlayBar;
			Ogre::OverlayContainer* button;
			bool interactable;
			std::vector<std::function<void()>> lambda;
	
			void handleInput();
			
			bool hovering;
			bool hasMaterial;

		protected:
			void onMove() override;
			void onResize() override;
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

			bool isHovering();

			void onClick(std::function<void()> l);
		};
	}
}
#endif