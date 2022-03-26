#include "Mesh.h"
#include "Transform.h"
#include <stdexcept>
#include <OgreRenderer.h>
#include <OgreSceneNode.h>
#include <Vector3.h>
#include <Vector4.h>
#include <Ogre.h>
#include <string>

void Mesh::sendParameters(std::string mN, Ogre::SceneNode* eN, Ogre::SceneNode* pN, Ogre::Entity* e, Transform* p, Transform* eT)
{
	meshName = mN;
	entityNode = eN;
	parentNode = pN;
	entity = e;
	parent = p;
	child = eT;

}
void Mesh::init()
{

	//El nombre y la referencia al transform se asignan cuando ya se ha creado el transform
	if (meshName == "") throw new std::exception("La malla no tiene nombre");
	if (parentNode == nullptr)entityNode = OgreRenderer::instance->createNode();
	else entityNode = OgreRenderer::instance->createChildNode(parentNode);

	if (entity == nullptr)entity = OgreRenderer::instance->getSceneManager()->createEntity(meshName);
	else throw new std::exception("Ya existe una entidad asociada");

	entityNode->attachObject(entity);


	if (parent != nullptr) {
		rot = parent->getRot();
		pos = parent->getPos();
		scale = parent->getScale();
	}
	else {
		rot = child->getRot();
		pos = child->getPos();
		scale = child->getScale();
	}

	entityNode->setPosition(Ogre::Vector3(pos->x,pos->y, pos->z));
	entityNode->setScale(Ogre::Vector3(scale->x, scale->y, scale->z));
	
	//entityNode->setOrientation(Ogre::Quaternion(rot->w, rot->x, rot->y, rot->z));
}

//No se llama el update 
void Mesh::update()
{

	rot = child->getRot();
	pos = child->getPos();
	scale = child->getScale();

    //Usar Translate , Scale, y luego la rotacion esta por ver 
}

Mesh::~Mesh()
{
	OgreRenderer::instance->removeNode(entityNode);
	delete rot, pos, scale;
}
