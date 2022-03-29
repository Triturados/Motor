#pragma once

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
		class Mesh : public Component
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
			Mesh() {};
			void init();
			void update();
			void sendParameters(std::string mN = "", Ogre::SceneNode* eN = nullptr, Ogre::SceneNode* pN = nullptr,
				Ogre::Entity* e = nullptr, Transform* p = nullptr, Transform* eT = nullptr);
			~Mesh();

		};
	}
}
#endif