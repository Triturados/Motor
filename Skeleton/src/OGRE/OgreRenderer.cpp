#include "OgreRenderer.h"

#include <OgreVector2.h>
#include <OgreVector3.h>
#include <OgreVector4.h>
#include <OgreRoot.h>
#include <OgreConfigFile.h>
#include <OgreRenderWindow.h>
#include <OgreTextureManager.h>
#include <OgreCamera.h>
#include <OgreSceneManager.h>
#include "OgreViewport.h"
#include <OgreEntity.h>
#include <OgreShaderGenerator.h>
#include <OgreBitesConfigDialog.h>
#include <OgreWindowEventUtilities.h>
#include <OgreSGTechniqueResolverListener.h>
#include <OgreGpuProgramManager.h>
#include <OgreWindowEventUtilities.h>
#include "../Main/checkML.h"

OgreRenderer* OgreRenderer::instance = nullptr;

OgreRenderer::OgreRenderer()
{
	assert("Ya existe una instancia de Ogre.", instance == nullptr);
	instance = this;

	initRoot();

	loadResources();

	
	setupScenes();

	initRTShaderSystem();

}

/// <summary>
/// Inicializa la raiz
/// </summary>
void OgreRenderer::initRoot() {


	mResourcesCfgPath = "./OGRE/resources.cfg";
	mPluginsCfgPath = "./OGRE/plugins/plugins.cfg";
	mLogPath = "./OGRE/Ogre.log";
	mCfgPath = "./OGRE/ogre.cfg";

	mRoot = new Ogre::Root(mPluginsCfgPath, mCfgPath, mLogPath);

	//PARA MOSTRAR LA VENTANA DE DIALOGO INICIAL HAY QUE BORRA EL OGRE.CFG.   POR DEFECTO USO GL3+
	if (!mRoot->restoreConfig())mRoot->showConfigDialog(OgreBites::getNativeConfigDialog());
}

/// <summary>
/// Parsea el archivo resources.cfg para obtener las rutas de los recursos
/// </summary>
void OgreRenderer::loadResources()
{
	Ogre::ConfigFile cf;
	cf.load(mResourcesCfgPath);

	Ogre::String name, locType;
	Ogre::ConfigFile::SectionIterator secIt = cf.getSectionIterator();
	while (secIt.hasMoreElements())
	{
		Ogre::ConfigFile::SettingsMultiMap* settings = secIt.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator it;
		for (it = settings->begin(); it != settings->end(); ++it)
		{
			locType = it->first;
			name = it->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(name, locType);
		}
	}
}

/// <summary>
/// Inicia el sistema de shaders. El m�todo debe llamarse despues de setupScenes
/// </summary>
void OgreRenderer::initRTShaderSystem()
{
	//if (Ogre::RTShader::ShaderGenerator::initialize())
	//{
	//	mShaderGenerator = Ogre::RTShader::ShaderGenerator::getSingletonPtr();

	//	// Create and register the material manager listener if it doesn't exist yet.
	//	if (!mMaterialMgrListener) {
	//		mMaterialMgrListener = new OgreBites::SGTechniqueResolverListener(mShaderGenerator);
	//		Ogre::MaterialManager::getSingleton().addListener(mMaterialMgrListener);
	//	}
	//}
	//mShaderGenerator->addSceneManager(mSceneMgr);
}

void OgreRenderer::destroyRTShaderSystem()
{
	//mShaderGenerator->removeAllShaderBasedTechniques();
	//mShaderGenerator->flushShaderCache();


 // // Restore default scheme.
	//Ogre::MaterialManager::getSingleton().setActiveScheme(Ogre::MaterialManager::DEFAULT_SCHEME_NAME);

	//// Unregister the material manager listener.
	//if (mMaterialMgrListener != nullptr)
	//{
	//	Ogre::MaterialManager::getSingleton().removeListener(mMaterialMgrListener);
	//	//delete mMaterialMgrListener;
	//	mMaterialMgrListener = nullptr;
	//}

	//// Destroy RTShader system.
	//if (mShaderGenerator != NULL)
	//{
	//	Ogre::RTShader::ShaderGenerator::destroy();
	//	mShaderGenerator = NULL;
	//}
}


/// <summary>
/// Crea la ventana inicial (c�mara y viewport) y el manejador de escenas
/// </summary>
void OgreRenderer::setupScenes()
{
	mWindow = mRoot->initialise(true, "Juego");
	mSceneMgr = mRoot->createSceneManager();

	mCameraNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	mCameraNode->setPosition(0, 0, 80);
	mCameraNode->lookAt(Ogre::Vector3(0, 0, -300), Ogre::Node::TransformSpace::TS_WORLD);

	mCamera = mSceneMgr->createCamera("MainCam");
	mCamera->setNearClipDistance(5);

	mCameraNode->attachObject(mCamera);

	Ogre::Viewport* vp = mWindow->addViewport(mCamera);

	vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));

	mCamera->setAspectRatio(
		Ogre::Real(vp->getActualWidth()) /
		Ogre::Real(vp->getActualHeight()));



	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}


/// <summary>
/// Actualiza la escena. True si lo hace correctamente, False si se cierra
/// </summary>
bool OgreRenderer::update()
{
	/*Ogre::WindowEventUtilities::messagePump();

	if (mWindow->isClosed()) return false;

	if (!mRoot->renderOneFrame()) return false;*/

	return true;
}



void OgreRenderer::exampleScene()
{
	Ogre::Entity* ogreEntity = mSceneMgr->createEntity("ogrehead.mesh");

	Ogre::SceneNode* ogreNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	ogreNode->attachObject(ogreEntity);

	//mSceneMgr->setAmbientLight(Ogre::ColourValue(.5, .5, .5));
}


OgreRenderer::~OgreRenderer()
{
	// Destroy the RT Shader System.
	destroyRTShaderSystem();
	mWindow->destroy();

	if (mRoot)
	{
		mRoot->saveConfig();
		OGRE_DELETE mRoot;
		mRoot = NULL;
	}

}


Ogre::SceneNode* OgreRenderer::createNode()
{
	return mSceneMgr->getRootSceneNode()->createChildSceneNode();

}

Ogre::SceneNode* OgreRenderer::createChildNode(Ogre::SceneNode* parent)
{
	return parent->createChildSceneNode();
}

void OgreRenderer::removeNode(Ogre::SceneNode* node)
{
	mSceneMgr->destroySceneNode(node);
}

Ogre::SceneManager* OgreRenderer::getSceneManager()
{
	return mSceneMgr;
}
