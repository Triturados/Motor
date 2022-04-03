#pragma once
#include <../Export.h>

#ifndef MESH_H
#define MESH_H

#include <Component.h>
#include <string>


namespace Utilities {
	template<typename T>
	class Vector3;
	template<typename T>
	class Vector4;
}
namespace Ogre {
	class SceneNode;
	class Entity;
}

namespace LoveEngine {
	namespace ECS {

		class Transform;
		class lovexport Mesh : public Component
		{
		private:
			std::string  meshName = "";
			Ogre::SceneNode* entityNode = nullptr;
			Ogre::SceneNode* parentNode = nullptr;
			Ogre::Entity* entity = nullptr;
			Transform* parent = nullptr;
			Transform* child = nullptr;
			Utilities::Vector4<float>* rot;
			Utilities::Vector3<float>* pos;
			Utilities::Vector3<float>* scale;

		public:
			void init()override;
			void update()override;
			void sendvalues(std::string mN, Transform* eT, LoveEngine::ECS::GameObject* pObj);
			void onSceneUp() override;
			void onSceneDown() override;
			void setVisibility(bool mode = true);
			~Mesh();
			Ogre::SceneNode* getEntityNode();

		};
	}
}
#endif