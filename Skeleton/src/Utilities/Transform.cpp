#include "Transform.h"
#include <Ogre.h>
#include <OgreRenderer.h>
#include <OgreSceneNode.h>
#include "Vector3.h"
#include "Vector4.h"

Transform::Transform(Transform* p)
{

	//Le pasamos un parent, por defecto es nulo 


	entityNode = p == nullptr ? 
		OgreRenderer::instance->createNode() : 
		OgreRenderer::instance->createChildNode(p->entityNode);

	parent = p;

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
	
	return transformOgreVector(position);
}

Utilities::Vector4<float>Transform::getRot()
{
	return transformOgreQuaternion(rotation);
}

Utilities::Vector3<float>Transform::getScale()
{
	return transformOgreVector(scale);
}



void Transform::setRot(Utilities::Vector4<float> r)
{
	rotation = transformIntoOgreQuaternion(r);
	entityNode->setOrientation(*rotation);
}

void Transform::setPos(Utilities::Vector3<float> p)
{
	position = transformIntoOgreVector(p);
	entityNode->setPosition(*position);
}

void Transform::setScale(Utilities::Vector3<float> s)
{
	scale = transformIntoOgreVector(s);
	entityNode->setScale(*scale);
}


//Metodos de converion a unidades de Ogre
Utilities::Vector3<float> Transform::transformOgreVector(Ogre::Vector3*  v)
{
	return Utilities::Vector3<float>(v->x,v->y,v->z);
}

Utilities::Vector4<float> Transform::transformOgreQuaternion(Ogre::Quaternion* v)
{
	return Utilities::Vector4<float>(v->x, v->y, v->z,v->w);
}

//Metodos de conversion de Unidades de Ogre a Vector3 y Vector4 
Ogre::Vector3* Transform::transformIntoOgreVector(Utilities::Vector3<float>v)
{
	return new Ogre::Vector3(v.x, v.y, v.z);
}

Ogre::Quaternion* Transform::transformIntoOgreQuaternion(Utilities::Vector4<float> v)
{
	return new Ogre::Quaternion(v.x, v.y, v.z, v.w);
}
