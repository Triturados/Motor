#pragma once

#include <vector>
#include "Vector3.h"
#include <Ogre.h>
#include <OgreRenderer.h>
#include <Component.h>
#include <OgreSceneNode.h>

class Transform :  public Component
{
	Vector3<float>position;
	Vector3<float>rotation;
	Vector3<float>scale;

	Ogre::SceneNode* entityNode;
	std::vector<Transform*> children;
public:
	Transform();
	~Transform();
	Vector3<float>getPos();
	Vector3<float>getPos();
	Vector3<float>getRot();

	void setRot();
	void setPos();
	void setScale();


};

