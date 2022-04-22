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
#include <StringFormatter.h>

namespace LoveEngine {
	namespace ECS {

		Light::Light()
		{
			specular = new Utilities::Vector3<float>(0.5, 0.5, 0.5);
			diffuse = new Utilities::Vector3<float>(0.5, 0.5, 0.5);
			direction = new Utilities::Vector3<float>(0, -1, -0.5);
			inRange = 35.0;
			outRange = 55.0;
			fallOff = 1.0;
			visible = true;
		}
		void Light::init()
		{
			ogremanager = Renderer::OgreRenderer::getInstance();
			tr = gameObject->getComponent<Transform>();

			switch (type)
			{
			case lightType::point:
				light = ogremanager->getSceneManager()->createLight(name);

				light->setDiffuseColour(diffuse->x, diffuse->y, diffuse->z);
				light->setSpecularColour(specular->x, specular->y, specular->z);

				light->setType(Ogre::Light::LT_POINT);


				entityNode = ogremanager->getSceneManager()->getRootSceneNode()->createChildSceneNode();
				entityNode->attachObject(light);
				entityNode->setPosition(Ogre::Vector3(tr->getPos()->x, tr->getPos()->y, tr->getPos()->z));
				break;
			case lightType::directional:
				light = ogremanager->getSceneManager()->createLight(name);

				light->setDiffuseColour(diffuse->x, diffuse->y, diffuse->z);
				light->setSpecularColour(specular->x, specular->y, specular->z);

				light->setType(Ogre::Light::LT_DIRECTIONAL);

				entityNode = ogremanager->getSceneManager()->getRootSceneNode()->createChildSceneNode();
				entityNode->attachObject(light);
				entityNode->setDirection(Ogre::Vector3(direction->x, direction->y, direction->z));

				break;
			case lightType::spot:
				light = ogremanager->getSceneManager()->createLight(name);

				light->setDiffuseColour(diffuse->x, diffuse->y, diffuse->z);
				light->setSpecularColour(specular->x, specular->y, specular->z);

				light->setType(Ogre::Light::LT_SPOTLIGHT);

				entityNode = ogremanager->getSceneManager()->getRootSceneNode()->createChildSceneNode();
				entityNode->attachObject(light);
				entityNode->setDirection(Ogre::Vector3(direction->x, direction->y, direction->z));


				entityNode->setPosition(Ogre::Vector3(tr->getPos()->x, tr->getPos()->y, tr->getPos()->z));

				light->setSpotlightRange(Ogre::Degree(inRange), Ogre::Degree(outRange), fallOff);
				break;
			default:
				break;
			}

			setVisibility(visible);
		}

		void Light::update()
		{
			rot = tr->getRot();
			pos = tr->getPos();
			scale = tr->getScale();

			entityNode->setPosition(Ogre::Vector3(pos->x, pos->y, pos->z));
			entityNode->setScale(Ogre::Vector3(scale->x, scale->y, scale->z));

			entityNode->resetOrientation();
			entityNode->pitch(Ogre::Radian(rot->x), Ogre::Node::TS_WORLD);
			entityNode->yaw(Ogre::Radian(rot->y), Ogre::Node::TS_WORLD);
			entityNode->roll(Ogre::Radian(rot->z), Ogre::Node::TS_WORLD);
			//Usar Translate , Scale, y luego la rotacion esta por ver 
		}

		Light::~Light()
		{
			delete diffuse;
			delete specular;
			delete direction;
			//Si destruimos el padre sera suficiente gracias a la jerarquia de nodos de Ogre 
			ogremanager->removeNode(entityNode);

			if (light != nullptr)
				ogremanager->getSceneManager()->destroyLight(light);
			if (entityNode != nullptr)
				ogremanager->getSceneManager()->destroySceneNode(entityNode);
		}

		void Light::diffuseColor(float r, float g, float b)
		{
			diffuse->x += r;
			diffuse->y += g;
			diffuse->z += b;
			light->setDiffuseColour(r, g, b);
		}

		void Light::setPower(float power)
		{
			lightPower = power;
			light->setPowerScale(power);
		}

		Utilities::Vector3<float> Light::getSpecularColor()
		{

			return *specular;
		}

		void Light::specularColor(float r, float g, float b)
		{
			specular->x += r;
			specular->y += g;
			specular->z += b;
			light->setSpecularColour(r, g, b);
		}

		Utilities::Vector3<float> Light::getDiffuseColor()
		{
			return *diffuse;
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
				inRange = startAngle;
				outRange = endAngle;
				fallOff = desvanecimiento;
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

		void Light::receiveMessage(Utilities::StringFormatter& sf)
		{
			sf.tryGetString("name", name);
			std::string t;
			
			if (sf.tryGetString("type", t)) {
				if (t == "point")
					type = lightType::point;
				else if (t == "directional")
					type = lightType::directional;
				else if (t == "spot")
					type = lightType::spot;

				Utilities::Vector3<float> aux;
				if (sf.tryGetVector3("diffuse", aux))
				{
					diffuse->x += aux.x;
					diffuse->y += aux.y;
					diffuse->z += aux.z;
				}

				if (sf.tryGetVector3("specular", aux))
				{
					specular->x += aux.x;
					specular->y += aux.y;
					specular->z += aux.z;
				}

				if (sf.tryGetVector3("direction", aux))
				{
					direction->x += aux.x;
					direction->y += aux.y;
					direction->z += aux.z;
				}

				int p;
				if (sf.tryGetInt("power", p))
				{
					lightPower = p;
				}

				float rang;

				if (sf.tryGetFloat("inAngle", rang))
				{
					inRange = rang;
				}

				if (sf.tryGetFloat("outAngle", rang))
				{
					outRange = rang;
				}

				if (sf.tryGetFloat("fallOff", rang))
				{
					fallOff = rang;
				}

				bool see;

				if (sf.tryGetBool("visibility", see))
				{
					visible = see;
				}
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