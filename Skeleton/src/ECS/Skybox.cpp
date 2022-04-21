#include "Skybox.h"
#include <string>
#include <iostream>
#include <StringFormatter.h>
#include <OgreRenderer.h>

void LoveEngine::ECS::Skybox::receiveMessage(Utilities::StringFormatter& sf)
{
	sf.tryGetString("materialName", materialName);
	sf.tryGetInt("distance", distance);
}

void LoveEngine::ECS::Skybox::init()
{
	ogremanager = Renderer::OgreRenderer::getInstance();
	ogremanager->getSceneManager()->setSkyBox(true, materialName, distance, true);
}
