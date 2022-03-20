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
	/* entityNode->setOrientation(parent->getRot());
	entityNode->setPos(position.getOgreVector);
	entityNode->setScale(scale.getOgreVector);*/

}

Mesh::~Mesh()
{

	OgreRenderer::instance->removeNode(entityNode);

}