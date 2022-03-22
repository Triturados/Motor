#include "LightComponent.h"

#include "OgreLight.h"
#include "OgreSceneManager.h"
#include "OgreRenderer.h"
#include "Component.h"
#include "Transform.h"
#include "GameObject.h"
#include "Vector3.h"
#include "Vector4.h"
#include <iostream>

LightComponent::LightComponent()
{

}

void LightComponent::sendParameters(lightType t, std::string n, Ogre::SceneManager* manager)
{
	pos = gameObject->getComponent<Transform>();
	name = n;
	type = t;
	scnMgr = manager;
	Utilities::Vector3 v;

	if (type == point)
	{
		std::cout << "SOY LUZ POINT";
		std::cout << "\n";
	}
	else
	{
		std::cout << "NO SOY LUZ POINT";
		std::cout << "\n";
	}
	visible = true;

	switch (type)
	{
	case point:
		light = scnMgr->createLight(name);

		light->setDiffuseColour(0.3, 0.3, 0.3);
		light->setSpecularColour(0.3, 0.3, 0.3);

		light->setType(Ogre::Light::LT_POINT);

		entityNode = scnMgr->getRootSceneNode()->createChildSceneNode();
		entityNode->attachObject(light);

		v = *pos->getPos();
		entityNode->setPosition(Ogre::Vector3(v.x, v.y, v.z));
		break;
	case directional:
		light = scnMgr->createLight(name);

		light->setDiffuseColour(Ogre::ColourValue(0.4, 0, 0));
		light->setSpecularColour(Ogre::ColourValue(0.4, 0, 0));

		light->setType(Ogre::Light::LT_DIRECTIONAL);

		entityNode = scnMgr->getRootSceneNode()->createChildSceneNode();
		entityNode->attachObject(light);
		entityNode->setDirection(Ogre::Vector3(0, -1, 1));

		break;
	case spot:
		light = scnMgr->createLight(name);

		light->setDiffuseColour(0, 0, 1.0);
		light->setSpecularColour(0, 0, 1.0);

		light->setType(Ogre::Light::LT_SPOTLIGHT);

		entityNode = scnMgr->getRootSceneNode()->createChildSceneNode();
		entityNode->attachObject(light);
		entityNode->setDirection(-1, -1, 0);


		v = *pos->getPos();
		entityNode->setPosition(Ogre::Vector3(v.x, v.y, v.z));

		light->setSpotlightRange(Ogre::Degree(35), Ogre::Degree(50));
		break;
		default:
		break;
	}

	light->setVisible(true);
}
void LightComponent::init()
{
	visible = true;
	Utilities::Vector3 v;

	switch (type)
	{
	case point:
		light = scnMgr->createLight(name);

		light->setDiffuseColour(0.3, 0.3, 0.3);
		light->setSpecularColour(0.3, 0.3, 0.3);

		light->setType(Ogre::Light::LT_POINT);
		

		entityNode = scnMgr->getRootSceneNode()->createChildSceneNode();
		entityNode->attachObject(light);
		
		v = *pos->getPos();
		entityNode->setPosition(Ogre::Vector3(v.x, v.y, v.z));
		break;
	case directional:
		light = scnMgr->createLight(name);

		light->setDiffuseColour(Ogre::ColourValue(0.4, 0, 0));
		light->setSpecularColour(Ogre::ColourValue(0.4, 0, 0));

		light->setType(Ogre::Light::LT_DIRECTIONAL);

		entityNode = scnMgr->getRootSceneNode()->createChildSceneNode();
		entityNode->attachObject(light);
		entityNode->setDirection(Ogre::Vector3(0, -1, 0));

		break;
	case spot:
		light = scnMgr->createLight(name);

		light->setDiffuseColour(0, 0, 1.0);
		light->setSpecularColour(0, 0, 1.0);

		light->setType(Ogre::Light::LT_SPOTLIGHT);

		entityNode = scnMgr->getRootSceneNode()->createChildSceneNode(); //AQUI USO EL NODO DE LA ENTIDAD O UNO NUEVO¿?
		entityNode->attachObject(light);
		entityNode->setDirection(-1, -1, 0);


		v = *pos->getPos();
		entityNode->setPosition(Ogre::Vector3(v.x, v.y, v.z));

		light->setSpotlightRange(Ogre::Degree(35), Ogre::Degree(50));
		break;
	default:
		break;
	}

	light->setPowerScale(1000);
	light->setVisible(true);
}

LightComponent::~LightComponent()
{
	//Si destruimos el padre sera suficiente gracias a la jerarquia de nodos de Ogre 
	OgreRenderer::instance->removeNode(entityNode);
}

void LightComponent::specularColor(float r, float g, float b)
{
	light->setDiffuseColour(r, g, b);
}

void LightComponent::setPower(float power)
{
	light->setPowerScale(power);
}

Utilities::Vector4<float> LightComponent::getSpecularColor()
{
	return Utilities::Vector4<float>(light->getSpecularColour().r, light->getSpecularColour().g,
									 light->getSpecularColour().b, light->getSpecularColour().a);
}

void LightComponent::diffuseColor(float r, float g, float b)
{
	light->setSpecularColour(r, g, b);
}

Utilities::Vector4<float> LightComponent::getDiffuseColor()
{
	return Utilities::Vector4<float>(light->getDiffuseColour().r, light->getDiffuseColour().g,
					      light->getDiffuseColour().b, light->getDiffuseColour().a);
}


void LightComponent::setDir(Utilities::Vector3<float> direction)
{
	if (type != point) //Si la luz no es punto
	{
		entityNode->setDirection(direction.x, direction.y, direction.z);
	}
}

void LightComponent::setRange(float startAngle, float endAngle, float desvanecimiento)
{
	if (type == spot)
	{
		light->setSpotlightRange(Ogre::Degree(startAngle), Ogre::Degree(endAngle), Ogre::Real(desvanecimiento));
	}
}

void LightComponent::setVisibility(bool active)
{
	light->setVisible(active);
}

bool LightComponent::getVisibility()
{
	return visible;
}


