#pragma once
#include <../Export.h>

#ifndef IMAGE_H	
#define IMAGE_H

#include <Component.h>
#include <string>

class SDL_Texture;

namespace Ogre {
	class Overlay;
}

namespace LoveEngine {

	namespace Utilities {
		template<typename T>
		class Vector3;
		template<typename T>
		class Vector4;
		template<typename T>
		class Vector2;
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
			SDL_Texture* texture = nullptr;

			int width = 10, height = 10;
			//Utilities::Vector2<float>* scale;

			Renderer::OgreRenderer* ogremanager;

			bool visible = true;
			Ogre::Overlay* overlay;
		public:
			void init()override;
			void update()override;
			void receiveMessage(std::string s)override;
			void onSceneUp() override;
			void onSceneDown() override;
			void setVisibility(bool mode = true);
			~Image();
		};
	}
}
#endif