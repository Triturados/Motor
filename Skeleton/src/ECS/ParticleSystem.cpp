#include "ParticleSystem.h"
#include "Transform.h"
#include <stdexcept>
#include <OgreRenderer.h>
#include <GameObject.h>
#include <OgreSceneNode.h>
#include <Vector3.h>
#include <Vector4.h>
#include <Ogre.h>
#include <string>
#include <iostream>
#include <StringFormatter.h>

namespace LoveEngine {
	namespace ECS {

		void ParticleSystem::receiveMessage(Utilities::StringFormatter& sf)
		{
			sf.tryGetString("particleName", templateName);
			bool isEmit;
			if(sf.tryGetBool("emitting", isEmit)) emitting = isEmit;
		}

		void ParticleSystem::setActive(bool activated)
		{
			pSys->setEmitting(activated);
			emitting = activated;
		}

		bool ParticleSystem::isEmitting()
		{
			return emitting;
		}

		void ParticleSystem::setMaterial(std::string materialName)
		{
			pSys->setMaterialName(materialName);
		}

		void ParticleSystem::init() {
			ogremanager = Renderer::OgreRenderer::getInstance();

			particleName = templateName + std::to_string(ogremanager->addParticleSystem());
			tr = gameObject->getComponent<Transform>();

			//El nombre y la referencia al transform se asignan cuando ya se ha creado el transform
			if (templateName == "") throw new std::exception("El sistema de particulas no tiene nombre");

			entityNode = ogremanager->createNode();

			if (pSys == nullptr)
				if (!ogremanager->getSceneManager()->hasParticleSystem(templateName))
					pSys = ogremanager->getSceneManager()->createParticleSystem(particleName, templateName);
				else throw new std::exception("Ya existe el sistema de particulas");
			
			//else throw new std::exception("Ya existe un sistema de particulas con ese nombre.");

			entityNode->attachObject(pSys);
			pSys->setEmitting(emitting);

			rot = tr->getRot();
			pos = tr->getPos();
			scale = tr->getScale();

			entityNode->setPosition(Ogre::Vector3(pos->x, pos->y, pos->z));
			entityNode->setScale(Ogre::Vector3(scale->x, scale->y, scale->z));

			entityNode->resetOrientation();
			entityNode->yaw(Ogre::Radian(rot->z), Ogre::Node::TS_WORLD);
			entityNode->pitch(Ogre::Radian(rot->y), Ogre::Node::TS_WORLD);
			entityNode->roll(Ogre::Radian(rot->x), Ogre::Node::TS_WORLD);
		}

		//No se llama el update 
		void ParticleSystem::update()
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
		}

		Ogre::ParticleSystem* ParticleSystem::getPSys()
		{
			return pSys;
		}

		ParticleSystem::~ParticleSystem()
		{
			ogremanager->removeNode(entityNode);
			ogremanager->getSceneManager()->destroyParticleSystem(particleName);
		}
	}
}