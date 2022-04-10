#pragma once

//#ifndef TEXT_H	
//#define TEXT_H

#include <Component.h>
#include <string>

namespace Ogre {
	class Overlay;
	class OverlayContainer;
	class OverlayElement;
}
namespace LoveEngine {

	namespace Renderer {
		class OgreRenderer;
	}
	namespace ECS {
		class Transform;

		class lovexport Text : public Component
		{
		public:
			Text() {};
			~Text();
			void init()override;
			void setPos(float x, float y);
			void setCol(float R, float G, float B, float I);
			void setText(std::string szString);
			void receiveMessage(Utilities::StringFormatter& s)override;
			/*void onSceneUp() override;
			void onSceneDown() override;*/
			void setVisibility(bool mode = true);
		private:
			
			std::string typeName;
			Renderer::OgreRenderer* ogremanager;

		};
	}
}
