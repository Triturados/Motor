#include "Transform.h"

Transform::Transform(Transform* p)
{

	//Le pasamos un parent, por defecto es nulo 


	entityNode = p == nullptr ? 
		OgreRenderer::instance->createNode() : 
		OgreRenderer::instance->createChildNode(p->entityNode);

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

Vector3<float>Transform::getPos()
{
	
	return Vector3<float>(position);
}

Vector4<float>Transform::getRot()
{
	return Vector4<float>(rotation);
}

Vector3<float>Transform::getScale()
{
	return Vector3<float>(scale);
}



void Transform::setRot(Vector4<float> r)
{
	rotation = r.getOgreQuaternion();
	entityNode->setOrientation(rotation);
}

void Transform::setPos(Vector3<float> p)
{
	position = p.getOgreVector();
	entityNode->setPosition(position);
}

void Transform::setScale(Vector3<float> s)
{
	scale = s.getOgreVector();
	entityNode->setScale(scale);
}