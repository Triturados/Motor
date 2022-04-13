#include <Material.h>
#include <string>
#include <iostream>
#include <StringFormatter.h>
#include <GameObject.h>
#include <Mesh.h>
//#include <ParticleSystem.h>

void LoveEngine::ECS::Material::receiveMessage(Utilities::StringFormatter& sf)
{
	sf.tryGetString("materialName", materialName);
}

void LoveEngine::ECS::Material::receiveComponent(int i, Component* c)
{
	switch (i)
	{
	case 0: mesh = static_cast<Mesh*>(c); break;
	//case 1: pSys = static_cast<ParticleSystem*>(c); break;
	default:
		break;
	}
}

void LoveEngine::ECS::Material::init()
{
	setMaterial();
}

void LoveEngine::ECS::Material::setMaterial()
{
	if (mesh) mesh->setMaterial(materialName);
	//if (pSys) pSys->setMaterial(materialName);
}
