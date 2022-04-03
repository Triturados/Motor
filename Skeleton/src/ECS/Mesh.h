#pragma once
#include <../Export.h>

#ifndef MESH_H
#define MESH_H

#include <Component.h>
#include <string>


namespace Ogre {
	class SceneNode;
	class Entity;
}

namespace LoveEngine {

	namespace Utilities {
		template<typename T>
		class Vector3;
		template<typename T>
		class Vector4;
	}
	namespace Renderer {
		class OgreRenderer;
	}
	namespace ECS {

		class Transform;

		class lovexport Mesh : public Component
		{
		private:
			std::string  meshName = "";
			Ogre::SceneNode* entityNode = nullptr;
			Ogre::Entity* entity = nullptr;
			Transform* tr = nullptr;
			Utilities::Vector4<float>* rot;
			Utilities::Vector3<float>* pos;
			Utilities::Vector3<float>* scale;

			Renderer::OgreRenderer* ogremanager;
		public:
			void init()override;
			void update()override;
			void receiveValues(int i, float f, Component* eT = nullptr, GameObject* g = nullptr)override;
			void receiveMessage(std::string s)override;
			void onSceneUp() override;
			void onSceneDown() override;
			void setVisibility(bool mode = true);
			Ogre::Entity* getEntity();
			~Mesh();
		};
	}
}
#endif