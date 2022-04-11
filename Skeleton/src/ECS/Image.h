#pragma once
#include <../Export.h>

#ifndef IMAGE_H	
#define IMAGE_H

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

		class lovexport Image : public Component
		{
		private:
			std::string material = "";
			Transform* tr = nullptr;

			int width = 10, height = 10;

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
			void setPos(int x, int y);
			~Image();
		};
	}
}
#endif