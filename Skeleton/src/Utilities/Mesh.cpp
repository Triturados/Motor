#include "Mesh.h"
#include <stdexcept>
#include <Transform.h>
#include <OgreRenderer.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include "Vector3.h"
#include "Vector4.h"
#include <Ogre.h>
#include <string>

void Mesh::init()
{
	if (meshName == "") throw new std::exception("La malla no tiene nombre");
	if (parent == nullptr) throw new std::exception("No existe un componente transform para esta entidad");
	if (parentNode == nullptr)entityNode = OgreRenderer::instance->createNode();
	else entityNode = OgreRenderer::instance->createChildNode(parentNode);

	OgreRenderer::instance->getSceneManager()->createEntity(meshName);



}

void Mesh::update()
{
	entityNode->setOrientation()
	entityNode->setPos(position.getOgreVector);
	entityNode->setScale(scale.getOgreVector);

}

Mesh::~Mesh()
{
	OgreRenderer::instance->removeNode(entityNode);
	if (parentNode != nullptr)OgreRenderer::instance->removeNode(parentNode);
	

}