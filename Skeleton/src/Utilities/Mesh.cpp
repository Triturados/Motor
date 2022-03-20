#include "Mesh.h"
#include "Transform.h"
#include <stdexcept>
#include <OgreRenderer.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include "Vector3.h"
#include "Vector4.h"
#include <Ogre.h>
#include <string>


void Mesh::init()
{

	//El nombre y la referencia al transform se asignan cuando ya se ha creado el transform
	if (meshName == "") throw new std::exception("La malla no tiene nombre");
	if (parent == nullptr) throw new std::exception("No existe un componente transform para esta entidad");
	if (parentNode == nullptr)entityNode = OgreRenderer::instance->createNode();
	else entityNode = OgreRenderer::instance->createChildNode(parentNode);

	if(entity==nullptr)OgreRenderer::instance->getSceneManager()->createEntity(meshName);
	else throw new std::exception("Ya existe una entidad asociada");



}

void Mesh::update()
{
	entityNode->setOrientation(*getOgreQuaternion(*parent->getRot()));
	entityNode->setPosition(*getOgreVector(*parent->getPos()));
	entityNode->setScale(*getOgreVector(*parent->getScale()));
}

Mesh::~Mesh()
{

	OgreRenderer::instance->removeNode(entityNode);

}

Ogre::Vector3* Mesh::getOgreVector(Utilities::Vector3<float> v)
{
	return &Ogre::Vector3(v.x, v.y, v.z);
}

Ogre::Quaternion* Mesh::getOgreQuaternion(Utilities::Vector4<float> v)
{
	return &Ogre::Quaternion(v.x, v.y, v.z, v.w);
}
