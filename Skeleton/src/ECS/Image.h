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

	namespace Utilities {
		template<typename T>
		class Vector3;
	}
	namespace Renderer {
		class OgreRenderer;
	}

	namespace ECS {

		class Transform;

		class lovexport Image : public Component
		{
		private:
			std::string material = "";

			Utilities::Vector3<int>* pos;
			Utilities::Vector2<int>* dimensions;
			Renderer::OgreRenderer* ogremanager;

			float opacity = 1;
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
			Utilities::Vector3<int> getPos();
			void setPos(Utilities::Vector3<int> pos_);
			float getOpacity();
			void setOpacity(float fade);
			Utilities::Vector2<int> getDimensions();
			void setDimensions(Utilities::Vector2<int> dimensions_);
			~Image();
		};
	}
}
#endif