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
	class Vector3;
	class Vector2;
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
		enum class alignmentEnum {Left,Right,Center};
		class lovexport Text : public ComponentTemplate<Text>
		{
		public:
			Text() {};
			~Text();
			void init()override;
			void setPos(Utilities::Vector3<int> pos_);
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
			colors color;
			alignmentEnum alignment;
			int elemNum;
			int width;
			int height;
			Utilities::Vector3<int>* pos;
			Utilities::Vector2<int>* dimensions;
			float charHeight;
			

		};
	}
}
