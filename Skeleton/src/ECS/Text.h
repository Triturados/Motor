#pragma once

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
			
			std::string textName;
			std::string textContent;
			Renderer::OgreRenderer* ogremanager;
			Ogre::TextAreaOverlayElement* textArea;
//<<<<<<< Updated upstream
			//Utilities::Vector3<float>* colors;
//=======
			Utilities::Vector4<float>* colorPtr;
//>>>>>>> Stashed changes
			int width;
			int height;
			int x;
			int y;
			float charHeight;
			
		};
	}
}
