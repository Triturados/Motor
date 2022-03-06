#pragma once

#include <vector>
#include <Ogre.h>
#include <OgreRenderer.h>
#include <Component.h>
#include <OgreSceneNode.h>

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
	Ogre::Vector3 getPos();
	Ogre::Quaternion getRot();
	Ogre::Vector3 getScale();

	void setRot(Ogre::Quaternion r);
	void setPos(Ogre::Vector3 p);
	void setScale(Ogre::Vector3 s);


};

