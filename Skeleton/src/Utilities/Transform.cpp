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
	
	return transformOgreVector(position);
}

Vector4<float>Transform::getRot()
{
	return transformOgreQuaternion(rotation);
}

Vector3<float>Transform::getScale()
{
	return transformOgreVector(scale);
}



void Transform::setRot(Vector4<float> r)
{
	rotation = transformIntoOgreQuaternion(r);
	entityNode->setOrientation(rotation);
}

void Transform::setPos(Vector3<float> p)
{
	position = transformIntoOgreVector(p);
	entityNode->setPosition(position);
}

void Transform::setScale(Vector3<float> s)
{
	scale = transformIntoOgreVector(s);
	entityNode->setScale(scale);
}


//Metodos de converion a unidades de Ogre
Vector3<float> Transform::transformOgreVector(Ogre::Vector3  v)
{
	return Vector3<float>(v.x,v.y,v.z);
}

Vector4<float> Transform::transformOgreQuaternion(Ogre::Quaternion v)
{
	return Vector4<float>(v.x, v.y, v.z,v.w);
}

//Metodos de conversion de Unidades de Ogre a Vector3 y Vector4 
Ogre::Vector3 Transform::transformIntoOgreVector(Vector3<float>v)
{
	return Ogre::Vector3(v.x, v.y, v.z);
}

Ogre::Quaternion Transform::transformIntoOgreQuaternion(Vector4<float> v)
{
	return Ogre::Quaternion(v.x, v.y, v.z, v.w);
}
