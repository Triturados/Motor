#include "LightComponent.h"
#include <iostream>
#include "OgreLight.h"
#include "OgreSceneManager.h"
#include <Ogre.h>
#include <OgreRenderer.h>
#include <OgreSceneNode.h>
#include "Transform.h"
#include "GameObject.h"
#include <Vector3.h>
#include <Vector4.h>
#include <StringFormater.h>

namespace LoveEngine {
	namespace ECS {

		void Light::receiveValues(int lightT, float lightNumber, Component* c, GameObject*)
		{
			ogremanager = Renderer::OgreRenderer::getInstance();
			pos = gameObject->getComponent<Transform>();
			name = "light"+(int)lightNumber;
			type = static_cast<lightType>(lightT);
		}
		void Light::init()
		{
			ogremanager = Renderer::OgreRenderer::getInstance();
			visible = true;

			switch (type)
			{
			case point:
				light = ogremanager->getSceneManager()->createLight(name);

				light->setDiffuseColour(0.3, 0.3, 0.3);
				light->setSpecularColour(0.3, 0.3, 0.3);

				light->setType(Ogre::Light::LT_POINT);


				entityNode = ogremanager->getSceneManager()->getRootSceneNode()->createChildSceneNode();
				entityNode->attachObject(light);
				entityNode->setPosition(Ogre::Vector3(pos->getPos()->x, pos->getPos()->y, pos->getPos()->z));
				break;
			case directional:
				light = ogremanager->getSceneManager()->createLight(name);

				light->setDiffuseColour(Ogre::ColourValue(0.4, 0, 0));
				light->setSpecularColour(Ogre::ColourValue(0.4, 0, 0));

				light->setType(Ogre::Light::LT_DIRECTIONAL);

				entityNode = ogremanager->getSceneManager()->getRootSceneNode()->createChildSceneNode();
				entityNode->attachObject(light);
				entityNode->setDirection(Ogre::Vector3(0, -1, 0));

				break;
			case spot:
				light = ogremanager->getSceneManager()->createLight(name);

				light->setDiffuseColour(0, 0, 1.0);
				light->setSpecularColour(0, 0, 1.0);

				light->setType(Ogre::Light::LT_SPOTLIGHT);

				entityNode = ogremanager->getSceneManager()->getRootSceneNode()->createChildSceneNode();
				entityNode->attachObject(light);
				entityNode->setDirection(-1, -1, 0);


				entityNode->setPosition(Ogre::Vector3(pos->getPos()->x, pos->getPos()->y, pos->getPos()->z));

				light->setSpotlightRange(Ogre::Degree(35), Ogre::Degree(50));
				break;
			default:
				break;
			}

			light->setVisible(true);
		}

		Light::~Light()
		{
			//Si destruimos el padre sera suficiente gracias a la jerarquia de nodos de Ogre 
			ogremanager->removeNode(entityNode);
		}

		void Light::specularColor(float r, float g, float b)
		{
			light->setDiffuseColour(r, g, b);
		}

		void Light::setPower(float power)
		{
			light->setPowerScale(power);
		}

		Utilities::Vector3<float> Light::getSpecularColor()
		{

			return Utilities::Vector3<float>(light->getSpecularColour().r, light->getSpecularColour().g, light->getSpecularColour().b);
		}

		void Light::diffuseColor(float r, float g, float b)
		{
			light->setSpecularColour(r, g, b);
		}

		Utilities::Vector3<float> Light::getDiffuseColor()
		{
			return Utilities::Vector3<float>(light->getDiffuseColour().r, light->getDiffuseColour().g, light->getDiffuseColour().b);
		}


		void Light::setDir(Utilities::Vector3<float> direction)
		{
			if (type != point) //Si la luz no es punto
			{
				entityNode->setDirection(direction.x, direction.y, direction.z);
			}
		}

		void Light::setRange(float startAngle, float endAngle, float desvanecimiento)
		{
			if (type == spot)
			{
				light->setSpotlightRange(Ogre::Degree(startAngle), Ogre::Degree(endAngle), Ogre::Real(desvanecimiento));
			}
		}

		void Light::setVisibility(bool active)
		{
			light->setVisible(active);
		}

		bool Light::getVisibility()
		{
			return visible;
		}

		void Light::receiveMessage(std::string message)
		{
			StringFormatter sf(message);
		
		}


		void Light::onSceneDown()
		{
			//setVisibility(false);
		}
		void Light::onSceneUp()
		{
			//setVisibility(true);
		}


	}
}