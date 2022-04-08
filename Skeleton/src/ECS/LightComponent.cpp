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

		void Light::init()
		{
			ogremanager = Renderer::OgreRenderer::getInstance();
			pos = gameObject->getComponent<Transform>();
			visible = true;

			switch (type)
			{
			case lightType::point:
				light = ogremanager->getSceneManager()->createLight(name);

				light->setDiffuseColour(0.3, 0.3, 0.3);
				light->setSpecularColour(0.3, 0.3, 0.3);

				light->setType(Ogre::Light::LT_POINT);


				entityNode = ogremanager->getSceneManager()->getRootSceneNode()->createChildSceneNode();
				entityNode->attachObject(light);
				entityNode->setPosition(Ogre::Vector3(pos->getPos()->x, pos->getPos()->y, pos->getPos()->z));
				break;
			case lightType::directional:
				light = ogremanager->getSceneManager()->createLight(name);

				light->setDiffuseColour(Ogre::ColourValue(0.8, 0.8, 0.8));
				light->setSpecularColour(Ogre::ColourValue(0.8, 0.8, 0.8));

				light->setType(Ogre::Light::LT_DIRECTIONAL);

				entityNode = ogremanager->getSceneManager()->getRootSceneNode()->createChildSceneNode();
				entityNode->attachObject(light);
				entityNode->setDirection(Ogre::Vector3(0, -1, -0.5));

				break;
			case lightType::spot:
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
			if (type != lightType::point) //Si la luz no es punto
			{
				entityNode->setDirection(direction.x, direction.y, direction.z);
			}
		}

		void Light::setRange(float startAngle, float endAngle, float desvanecimiento)
		{
			if (type == lightType::spot)
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
		
			sf.tryGetString("name", name);
			std::string t;
			
			if (sf.tryGetString("type", t)) {
				if (t == "point")
					type = lightType::point;
				else if (t == "directional")
					type = lightType::directional;
				else if (t == "spot")
					type = lightType::spot;
			}
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