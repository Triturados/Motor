#include "Transform.h"
#include "Vector3.h"
#include "Vector4.h"
#include <string>

Transform::Transform()
{
	//Obtenenos las posiciones a partir de ogre


	//DA ERROR 

	position = new Utilities::Vector3<float>(0.0, 0.0, 0.0);
	scale = new Utilities::Vector3<float>(0.0, 0.0, 0.0);
	rotation = new Utilities::Vector4<float>(0.0, 0.0, 0.0, 0.0); 
}


Utilities::Vector3<float>*Transform::getPos()
{

	return position;
}

Utilities::Vector4<float>*Transform::getRot()
{
	return rotation;
}

Utilities::Vector3<float>*Transform::getScale()
{
	return scale;
}


//LA ASIGNACION DA ERROR 

void Transform::setRot(Utilities::Vector4<float>* r)
{
	rotation = r;

}

void Transform::setPos(Utilities::Vector3<float>* p)
{
	position = p;

}

void Transform::setScale(Utilities::Vector3<float>* s)
{
	scale = s;

}
