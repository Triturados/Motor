#pragma once

#include <vector>
#include <Component.h>
#include <Ogre.h>
#include <OgreRenderer.h>
#include <OgreSceneNode.h>
#include "Vector3.h"
#include "Vector4.h"


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
	Vector3<float>getPos();
	Vector4<float> getRot();
	Vector3<float> getScale();

	void setRot(Vector4<float> r);
	void setPos(Vector3<float> p);
	void setScale(Vector3<float> s);
	Vector3<float>transformOgreVector(Ogre::Vector3 v);
	Vector4<float>transformOgreQuaternion(Ogre::Quaternion v);
	Ogre::Quaternion transformIntoOgreQuaternion(Vector4<float> v);
	Ogre::Vector3 transformIntoOgreVector(Vector3<float> v);

};

