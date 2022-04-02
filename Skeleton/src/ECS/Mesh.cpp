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
namespace LoveEngine {
	namespace ECS {

		void Mesh::sendvalues(std::string mN, Transform* eT)
		{
			meshName = mN;
			tr = eT;
		}
		void Mesh::init()
		{

			//El nombre y la referencia al transform se asignan cuando ya se ha creado el transform
			if (meshName == "") throw new std::exception("La malla no tiene nombre");
			entityNode = OgreRenderer::instance->createNode();

			if (entity == nullptr)entity = OgreRenderer::instance->getSceneManager()->createEntity(meshName);
			else throw new std::exception("Ya existe una entidad asociada");

			entityNode->attachObject(entity);

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
		void Mesh::update()
		{
			std::cout << "OgroPos " << pos->y << "\n";
			rot = tr->getRot();
			pos = tr->getPos();
			scale = tr->getScale();

			entityNode->setPosition(Ogre::Vector3(pos->x, pos->y, pos->z));
			entityNode->setScale(Ogre::Vector3(scale->x, scale->y, scale->z));

			entityNode->resetOrientation();
			entityNode->yaw(Ogre::Radian(rot->z), Ogre::Node::TS_WORLD);
			entityNode->pitch(Ogre::Radian(rot->y), Ogre::Node::TS_WORLD);
			entityNode->roll(Ogre::Radian(rot->x), Ogre::Node::TS_WORLD);
			//Usar Translate , Scale, y luego la rotacion esta por ver 
		}
		void Mesh::setVisibility(bool mode)
		{
			entityNode->setVisible(mode);
		}
		void Mesh::onSceneDown()
		{
			//setVisibility(false);
		}
		void Mesh::onSceneUp()
		{
			//setVisibility(true);
		}

		Mesh::~Mesh()
		{
			OgreRenderer::instance->removeNode(entityNode);
			delete rot, pos, scale;
		}
		Ogre::SceneNode* Mesh::getEntityNode()
		{
			return nullptr;
		}
	}
}