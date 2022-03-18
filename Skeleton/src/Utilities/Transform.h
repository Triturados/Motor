#pragma once

#include <vector>
#include <Component.h>/*
#include <Ogre.h>
#include <OgreRenderer.h>
#include <OgreSceneNode.h>
#include "Vector3.h"
#include "Vector4.h"*/

namespace Ogre {
	class SceneNode;
	class Quaternion;
	class Vector3;
}

class Quaternion;
class SceneNode;
class Vector3;

namespace Utilities {
	template<typename T>
	class Vector3;
	template<typename T>
	class Vector4;
}

class Transform :  public Component
{
	Vector3* position = nullptr;
	Quaternion* rotation = nullptr;
	Vector3* scale = nullptr;

	SceneNode* entityNode;
	std::vector<Transform*> children;

public:
	Transform* parent = nullptr;
	
	Transform();
	~Transform();
	Utilities::Vector3<float>getPos();
	Utilities::Vector4<float> getRot();
	Utilities::Vector3<float> getScale();

	void setRot(Utilities::Vector4<float> r);
	void setPos(Utilities::Vector3<float> p);
	void setScale(Utilities::Vector3<float> s);
};

