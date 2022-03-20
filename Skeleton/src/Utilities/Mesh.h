#pragma once
#include <Component.h>
#include <string>
#include <Transform.h>

namespace Utilities {
	template<typename T>
	class Vector3;
	template<typename T>
	class Vector4;
}
namespace Ogre {
	class SceneNode;
	class Quaternion;
	class Vector3;
}


class Mesh : public Component
{
public:

	//El nombre y la referencia al transform se asignan cuando ya se ha creado el transform

	std::string  meshName = "";
	Ogre::SceneNode* entityNode = nullptr;
	Ogre::SceneNode* parentNode = nullptr;
	Transform* parent = nullptr;
	
private:

	Mesh() {};
	void init();
	void update();
	~Mesh();



};

