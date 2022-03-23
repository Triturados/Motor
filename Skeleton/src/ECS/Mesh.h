#pragma once

#ifndef MESH_H
#define MESH_H

#include "Component.h"
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

class Transform; 
class Mesh : public Component
{
public:
	std::string  meshName = "";
	Ogre::SceneNode* entityNode = nullptr;
	Ogre::SceneNode* parentNode = nullptr;
	Ogre::Entity* entity = nullptr;
	Transform* parent = nullptr;
	
private:

	Mesh() {};
	void init();
	void update();
	~Mesh();

};

#endif