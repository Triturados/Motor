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

	namespace ECS {

		class Transform;

		class lovexport Slider : public Component
		{
		private:
			std::string materialBar = "";
			std::string materialButton = "";
			Transform* tr = nullptr;

			int width = 10, height = 10;
			int posX = 0, posY = 0;

			Renderer::OgreRenderer* ogremanager;

			bool visible = true;
			Ogre::Overlay* overlay;
			Ogre::OverlayContainer* container;
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