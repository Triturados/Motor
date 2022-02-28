#include "OgreRenderer.h"

OgreRenderer::OgreRenderer()
{
	initRoot(); 
	
	loadResources();

	setupScenes();

	initRTShaderSystem();

}

/// <summary>
/// Inicializa la raiz
/// </summary>
void OgreRenderer::initRoot() {
	mResourcesCfgPath = "resources.cfg";
	mPluginsCfgPath = "plugins.cfg";

	mRoot = new Ogre::Root(mPluginsCfgPath);
	
	//PARA MOSTRAR LA VENTANA DE DIALOGO INICIAL HAY QUE BORRA EL OGRE.CFG.   POR DEFECTO USO GL3+
	if(!mRoot->restoreConfig())mRoot->showConfigDialog(OgreBites::getNativeConfigDialog());
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
/// Inicia el sistema de shaders. El método debe llamarse despues de setupScenes
/// </summary>
void OgreRenderer::initRTShaderSystem()
{
	if (Ogre::RTShader::ShaderGenerator::initialize())
	{
		mShaderGenerator = Ogre::RTShader::ShaderGenerator::getSingletonPtr();

		// Create and register the material manager listener if it doesn't exist yet.
		if (!mMaterialMgrListener) {
			mMaterialMgrListener = new OgreBites::SGTechniqueResolverListener(mShaderGenerator);
			Ogre::MaterialManager::getSingleton().addListener(mMaterialMgrListener);
		}
	}
	mShaderGenerator->addSceneManager(mSceneMgr);
}


/// <summary>
/// Crea la ventana inicial (cámara y viewport) y el manejador de escenas
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
	Ogre::WindowEventUtilities::messagePump();

	if (mWindow->isClosed()) return false;

	if (!mRoot->renderOneFrame()) return false;

	return true;
}

void OgreRenderer::exampleScene()
{
	Ogre::Entity* ogreEntity = mSceneMgr->createEntity("ogrehead.mesh");

	Ogre::SceneNode* ogreNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	ogreNode->attachObject(ogreEntity);

	mSceneMgr->setAmbientLight(Ogre::ColourValue(.5, .5, .5));

	Ogre::Light* light = mSceneMgr->createLight("MainLight");
	Ogre::SceneNode* lightNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	lightNode->setPosition(20, 80, 50);
	lightNode->attachObject(light);
}
