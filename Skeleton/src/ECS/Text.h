#pragma once
#include <../Export.h>

//#ifndef TEXT_H	
//#define TEXT_H

#include <Component.h>
#include <string>


namespace Ogre {
	class Overlay;
	class OverlayContainer;
	class OverlayElement;
	class TextAreaOverlayElement;
}
namespace Utilities {
	template<typename T>
	class Vector4;
}
namespace LoveEngine {

	namespace Renderer {
		class OgreRenderer;
	}
	namespace ECS {
		class Transform;
		struct colors
		{
			float r, g, b, a;
		};
		class lovexport Text : public ComponentTemplate<Text>
		{
		public:
			Text() {};
			~Text();
			void init()override;
			void setPos(float x, float y);
			void setCol(float R, float G, float B, float I);
			void setText(std::string szString);
			void receiveMessage(Utilities::StringFormatter& sf)override;
			void onSceneUp() override;
			void onSceneDown() override;
			void setVisibility(bool mode = true);
		private:
			
			std::string textName;
			std::string textContent;
			Renderer::OgreRenderer* ogremanager;
			Ogre::TextAreaOverlayElement* textArea;
			//Utilities::Vector4<float>* colorPtr;
			colors color;
			int elemNum;
			int width;
			int height;
			float charHeight;
			Transform* tr = nullptr;
			
		};
	}
}
