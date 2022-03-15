#pragma once

#include <Component.h>
#include <Ogre.h>
#include <OgreRenderer.h>
#include <OgreSceneNode.h>
#include "Vector3.h"

class OgreSceneManager;
class OgreLight;
class Transform;

enum lightType{point, directional, spot};

class LightComponent :  public Component
{
	Ogre::SceneNode* entityNode;
	Ogre::SceneManager* scnMgr;

	Transform* pos;

	Ogre::Light* light;
	
	bool visible;

	std::string name;
	lightType type;
public:

	LightComponent();
	~LightComponent();

	void init();

	void sendParameters(lightType t, std::string n, Ogre::SceneManager* manager);
	void specularColor(float r, float g, float b);
	void diffuseColor(float r, float g, float b);
	void setDir(Vector3<float> direction);
	void setRange(float startAngle, float endAngle, float desvanecimiento = 1.0);
	void setVisibility(bool active);
	void setPower(float power);

	Vector3<float> getDiffuseColor();
	Vector3<float> getSpecularColor();
	Vector3<float> getDir();
	bool getVisibility();
};

