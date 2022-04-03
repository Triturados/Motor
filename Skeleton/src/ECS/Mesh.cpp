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
#include <StringFormater.h>

namespace LoveEngine {
	namespace ECS {

		void Mesh::receiveValues(int i, float f, Component* eT, GameObject* g)
		{

			tr = static_cast<Transform*>(eT);
		}
		void Mesh::receiveMessage(std::string s)
		{
			StringFormatter sTf(s);
			meshName = sTf.getString("meshName");
		}
		void Mesh::init() {
			ogremanager = Renderer::OgreRenderer::getInstance();
			//El nombre y la referencia al transform se asignan cuando ya se ha creado el transform
			if (meshName == "") throw new std::exception("La malla no tiene nombre");
			entityNode = ogremanager->createNode();

			if (entity == nullptr)
				entity = ogremanager->getSceneManager()->createEntity(meshName);
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
			ogremanager->removeNode(entityNode);
			delete rot, pos, scale;
		}
	}
}