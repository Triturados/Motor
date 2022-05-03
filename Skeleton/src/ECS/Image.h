#pragma once
#include <../Export.h>

#ifndef IMAGE_H	
#define IMAGE_H

#include "UIElement.h"
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


		class lovexport Image : public UIElement
		{
		private:
			std::string material = "";

			Renderer::OgreRenderer* ogremanager;

			float opacity;
			bool visible;
			Ogre::Overlay* overlay;
			Ogre::OverlayContainer* container;

		protected:

			void onResize() override;
			void onMove() override;

		public:
			Image();
			~Image();
			void init()override;
			void update()override;

			void receiveMessage(Utilities::StringFormatter& s)override;
			void onSceneUp() override;
			void onSceneDown() override;
			
			float getOpacity();
			void setOpacity(float fade);
			void setVisibility(bool mode = true);
		};
	}
}
#endif