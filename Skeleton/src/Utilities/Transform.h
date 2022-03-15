#pragma once

#include <vector>
#include <Component.h>

namespace Ogre {
	class Quaternion;
	class SceneNode;
	class Vector3;
}

template<typename T>
class Vector3;
template<typename T>
class Vector4;

class Transform :  public Component
{
	Ogre::Vector3 position;
	Ogre::Quaternion rotation;
	Ogre::Vector3 scale;

	Ogre::SceneNode* entityNode;
	std::vector<Transform*> children;
	Transform* parent;

public:
	Transform(Transform* p=nullptr);
	~Transform();
	Utilities::Vector3<float>getPos();
	Utilities::Vector4<float> getRot();
	Utilities::Vector3<float> getScale();

	void setRot(Utilities::Vector4<float> r);
	void setPos(Utilities::Vector3<float> p);
	void setScale(Utilities::Vector3<float> s);
	Utilities::Vector3<float>transformOgreVector(Ogre::Vector3 v);
	Utilities::Vector4<float>transformOgreQuaternion(Ogre::Quaternion v);
	Ogre::Quaternion transformIntoOgreQuaternion(Utilities::Vector4<float> v);
	Ogre::Vector3 transformIntoOgreVector(Utilities::Vector3<float> v);

};

