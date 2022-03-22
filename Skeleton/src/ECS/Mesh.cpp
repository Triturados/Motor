#include "Mesh.h"
#include "Transform.h"
#include <stdexcept>
#include <OgreRenderer.h>
#include <OgreSceneNode.h>
#include <Vector3.h>
#include <Vector4.h>
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
	Utilities::Vector4 rot = *parent->getRot();
	Utilities::Vector3 pos = *parent->getPos();
	Utilities::Vector3 scale = *parent->getScale();

	entityNode->setOrientation(Ogre::Quaternion(rot.w, rot.x, rot.y, rot.z));
	entityNode->setPosition(Ogre::Vector3(pos.x, pos.y, pos.z));
	entityNode->setScale(Ogre::Vector3(scale.x, scale.y, scale.z));
}

Mesh::~Mesh()
{

	OgreRenderer::instance->removeNode(entityNode);

}
