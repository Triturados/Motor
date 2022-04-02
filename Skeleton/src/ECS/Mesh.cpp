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
namespace LoveEngine {
	namespace ECS {

		void Mesh::sendvalues(std::string mN, Transform* eT, LoveEngine::ECS::GameObject* pObj)
		{
			meshName = mN;
			child = eT;
			if (pObj != nullptr)
			{
				parentNode = pObj->getComponent<Mesh>()->getEntityNode(); //Obtenemos el nodo del padre a partir de la malla del padre 
				parent = pObj->getComponent<Transform>();
			}
		}
		void Mesh::init()
		{

			//El nombre y la referencia al transform se asignan cuando ya se ha creado el transform
			if (meshName == "") throw new std::exception("La malla no tiene nombre");
			if (parentNode == nullptr)entityNode = OgreRenderer::instance->createNode();
			else entityNode = OgreRenderer::instance->createChildNode(parentNode);

			if (entity == nullptr)entity = OgreRenderer::instance->getSceneManager()->createEntity(meshName);
			else throw new std::exception("Ya existe una entidad asociada");

			entityNode->attachObject(entity);


			if (parent != nullptr) {
				rot = parent->getRot();
				pos = parent->getPos();
				scale = parent->getScale();
			}
			else {
				rot = child->getRot();
				pos = child->getPos();
				scale = child->getScale();
			}

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

			rot = child->getRot();
			pos = child->getPos();
			scale = child->getScale();

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