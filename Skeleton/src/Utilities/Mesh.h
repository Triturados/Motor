#pragma once
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
	class Quaternion;
	class Vector3;
}


class Mesh : public Component
{
public:
	std::string  meshName = "";
	Transform* transformRef = nullptr;
	Ogre::SceneNode* entityNode = nullptr;
	Transform* parent = nullptr;
	Utilities::Vector3<float>* position;
	Utilities::Vector3<float>* scale;
	Utilities::Vector3<float>* rotation;
private:
	void init();




};

