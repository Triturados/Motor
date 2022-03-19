#include "Transform.h"
#include <Ogre.h>
#include <OgreRenderer.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include "Vector3.h"
#include "Vector4.h"
#include <string>

Transform::Transform()
{
	//Obtenenos las posiciones a partir de ogre
	position = Utilities::Vector3(0, 0, 0);
	scale = Utilities::Vector3(0, 0, 0);
	rotation = Utilities::Vector4(0, 0, 0, 0);
}


Utilities::Vector3<float>Transform::getPos()
{

	return position;
}

Utilities::Vector4<float>Transform::getRot()
{
	return rotation;
}

Utilities::Vector3<float>Transform::getScale()
{
	return scale;
}



void Transform::setRot(Utilities::Vector4<float> r)
{
	rotation = r;

}

void Transform::setPos(Utilities::Vector3<float> p)
{
	position = p;

}

void Transform::setScale(Utilities::Vector3<float> s)
{
	scale = s;

}
