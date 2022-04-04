#pragma once
#include <../Export.h>

#ifndef IMAGE_H	
#define IMAGE_H

#include <Component.h>
#include <string>

class SDL_Texture;
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

			int width = -1, height = -1;
			//Utilities::Vector2<float>* scale;

			Renderer::OgreRenderer* ogremanager;

			bool visible = true;
		public:
			void init()override;
			void update()override;
			void receiveValues(int i, float f, Component* eT = nullptr, GameObject* g = nullptr)override;
			void receiveMessage(std::string s)override;
			void onSceneUp() override;
			void onSceneDown() override;
			void setVisibility(bool mode = true);
			~Image();
		};
	}
}
#endif