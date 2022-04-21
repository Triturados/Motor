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
		enum class alignmentEnum { Left, Right, Center };

		class lovexport Text : public ComponentTemplate<Text>
		{
		public:
			Text() {};
			~Text();

			void init() override;
			void receiveMessage(Utilities::StringFormatter& sf)override;
			void onSceneUp() override;
			void onSceneDown() override;
			void setVisibility(bool mode = true);
			void receiveString(std::string mssg) override;

			void changeText(std::string mssg);
		private:

			void configText();

			const Utilities::Vector2<float>& pixelToRelative(float x, float y);

			Renderer::OgreRenderer* ogremanager;
			Ogre::TextAreaOverlayElement* textArea;

			Utilities::Vector3<float>* pos;

			std::string textContent;
			std::string fontName;

			Utilities::Vector4<float>* mainColor;
			Utilities::Vector4<float>* bottomColor;
			Utilities::Vector4<float>* topColor;

			alignmentEnum alignment;
			int elemNum;
			int width;
			int height;
			float textScale;
		};
	}
}
