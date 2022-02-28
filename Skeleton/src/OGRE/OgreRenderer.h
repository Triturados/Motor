#pragma once
#ifndef OGRERENDERER_H
#define OGRERENDERER_H

#include <OgreRoot.h>
#include <OgreConfigFile.h>
#include <OgreRenderWindow.h>
#include <OgreTextureManager.h>
#include <OgreCamera.h>
#include <OgreSceneManager.h>
#include "OgreViewport.h"
#include <OgreEntity.h>
#include <OgreRTShaderSystem.h>
#include <OgreShaderGenerator.h>
#include <OgreBitesConfigDialog.h>
#include <OgreWindowEventUtilities.h>
#include <OgreSGTechniqueResolverListener.h>

class OgreRenderer
{
private:
	Ogre::Root* mRoot;
	Ogre::String mResourcesCfgPath;
	Ogre::String mPluginsCfgPath;

	Ogre::RenderWindow* mWindow;
	Ogre::SceneManager* mSceneMgr;

	Ogre::Camera* mCamera;
	Ogre::SceneNode* mCameraNode;

	Ogre::RTShader::ShaderGenerator* mShaderGenerator;
	Ogre::MaterialManager::Listener* mMaterialMgrListener;

	void loadResources();
	void initRTShaderSystem();
	void setupScenes();

public:
	OgreRenderer();

	void initRoot();
	bool update();
	void exampleScene();

	~OgreRenderer() { };
};


#endif // !OGRERENDERER_H