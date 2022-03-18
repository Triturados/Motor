#include "Transform.h"
#include <Ogre.h>
#include <OgreRenderer.h>
#include <OgreSceneNode.h>
#include "Vector3.h"
#include "Vector4.h"

Transform::Transform()
{
	entityNode = parent == nullptr ? 
		OgreRenderer::instance->createNode() : 
		OgreRenderer::instance->createChildNode(parent->entityNode);

	//Obtenenos las posiciones a partir de ogre
	position = new Ogre::Vector3(entityNode->getPosition());
	scale = new Ogre::Vector3(entityNode->getScale());
	rotation = new Ogre::Quaternion(entityNode->getOrientation());
}

Transform::~Transform()
{
	//Si destruimos el padre sera suficiente gracias a la jerarquia de nodos de Ogre 
	OgreRenderer::instance->removeNode(entityNode);
}

Utilities::Vector3<float>Transform::getPos()
{
	
	return Vector3<float>(position);
}

Utilities::Vector4<float>Transform::getRot()
{
	return Vector4<float>(rotation);
}

Utilities::Vector3<float>Transform::getScale()
{
	return Vector3<float>(scale);
}



void Transform::setRot(Utilities::Vector4<float> r)
{
	rotation = r.getOgreQuaternion();
	entityNode->setOrientation(rotation);
}

void Transform::setPos(Utilities::Vector3<float> p)
{
	position = p.getOgreVector();
	entityNode->setPosition(position);
}

void Transform::setScale(Utilities::Vector3<float> s)
{
	scale = s.getOgreVector();
	entityNode->setScale(scale);
}
