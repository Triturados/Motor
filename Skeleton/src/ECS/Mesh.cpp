#include "Mesh.h"
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

		void Mesh::receiveMessage(Utilities::StringFormatter& sf)
		{

			sf.tryGetString("meshName", meshName);
		}

		void Mesh::init() {
			ogremanager = Renderer::OgreRenderer::getInstance();
			tr = gameObject->getComponent<Transform>();
			if (meshName != "emptyMesh") {
				//El nombre y la referencia al transform se asignan cuando ya se ha creado el transform
				if (meshName == "") throw new std::exception("La malla no tiene nombre");
				entityNode = ogremanager->createNode();

				if (entity == nullptr)
					entity = ogremanager->getSceneManager()->createEntity(meshName);
				else throw new std::exception("Ya existe una entidad asociada");
				entityNode = ogremanager->createNode();
				entityNode->attachObject(entity);

			}
			else entityNode = ogremanager->createNode();

			rot = tr->getRot();
			pos = tr->getPos();
			scale = tr->getScale();

			entityNode->setPosition(Ogre::Vector3(pos->x, pos->y, pos->z));
			entityNode->setScale(Ogre::Vector3(scale->x, scale->y, scale->z));

			entityNode->resetOrientation();
			entityNode->yaw(Ogre::Radian(rot->y), Ogre::Node::TS_WORLD);
			entityNode->pitch(Ogre::Radian(rot->x), Ogre::Node::TS_WORLD);
			entityNode->roll(Ogre::Radian(rot->z), Ogre::Node::TS_WORLD);
		}

		void Mesh::update()
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

		void Mesh::setVisibility(bool mode)
		{
			entityNode->setVisible(mode);
		}

		void Mesh::setMaterial(const  std::string& materialName)
		{
			entity->setMaterialName(materialName);
		}

		void Mesh::onSceneDown()
		{
			setVisibility(false);
		}
		void Mesh::onSceneUp()
		{
			setVisibility(true);
		}

		Ogre::Entity* Mesh::getEntity()
		{
			return entity;
		}

		Ogre::SceneNode* Mesh::getNode()
		{
			return entityNode;
		}

		Mesh::~Mesh()
		{
			ogremanager->removeNode(entityNode);
			//delete rot, pos, scale;
		}
	}
}