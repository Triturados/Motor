#include "Transform.h"

Transform::Transform(Transform* p = nullptr)
{

	//Le pasamos un parent, por defecto es nulo 
	entityNode = OgreRenderer::instance->createChildNode(p->entityNode);
	parent = p;

	//Obtenenos las posiciones a partir de ogre
	position = entityNode->getPosition();
	scale = entityNode->getScale();
	rotation = entityNode->getOrientation();


}

Transform::~Transform()
{
	//Si destruimos el padre sera suficiente gracias a la jerarquia de nodos de Ogre 
	OgreRenderer::instance->removeNode(entityNode);
}

Ogre::Vector3 Transform::getPos()
{
	return position;
}

Ogre::Quaternion Transform::getRot()
{
	return rotation;
}

Ogre::Vector3 Transform::getScale()
{
	return scale;
}

void Transform::setRot(Ogre::Quaternion r)
{
	rotation = r;
	entityNode->setOrientation(r);
}

void Transform::setPos(Ogre::Vector3 p)
{
	position = p;
	entityNode->setPosition(p);
}

void Transform::setScale(Ogre::Vector3 s)
{
	scale = s;
	entityNode->setScale(s);
}
