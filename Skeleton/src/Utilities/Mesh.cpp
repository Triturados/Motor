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

void init()
{
      //if (meshName =="") throw excepci�n->La malla no tiene nombre
      //if (transformRef ==nullptr) throw excepci�n -> No existe un componente transform para esta entidad
if (parent==nullptr) OgreRenderer::instance->createNode() : 
else OgreRenderer::instance->createChildNode(parent->entityNode);
OgreRenderer: instance->getSceneManager()->createEntity(meshName);


//ESTO NO SE SI HACE FALTA 
position/scale = new Utilities::Vector3<float>(0.0,0.0,0.0)
rotation new Utilities::Vector4<float>(0.0,0.0,0.0,0.0)

}

