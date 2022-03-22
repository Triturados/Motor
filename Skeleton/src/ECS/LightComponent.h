#pragma once

#include "Component.h"

namespace Ogre {
	class Light;
	class SceneNode;
	class SceneManager;
}

namespace Utilities {
	template<typename T>
	class Vector3;
	template<typename T>
	class Vector4;
}

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
	void setDir(Utilities::Vector3<float> direction);
	void setRange(float startAngle, float endAngle, float desvanecimiento = 1.0);
	void setVisibility(bool active);
	void setPower(float power);

	Utilities::Vector4<float> getDiffuseColor();
	Utilities::Vector4<float> getSpecularColor();
	bool getVisibility();
};

