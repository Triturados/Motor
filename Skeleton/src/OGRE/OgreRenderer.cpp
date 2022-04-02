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
#include <Error_handling.h>
#include <SDL.h>
#include <SDL_syswm.h>
#include <SDL_events.h>

OgreRenderer* OgreRenderer::instance = nullptr;

OgreRenderer::OgreRenderer()
{
	if (instance != nullptr) throwOgreError(__LINE__, "Ya existe una instancia del OgreManager.");

	instance = this;

	initRoot();

	initOgreWithSDL();
	//mWindow = mRoot->initialise(true, "Juego");

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

	if(!Ogre::FileSystemLayer::fileExists(mPluginsCfgPath)) throwOgreError(__LINE__, "No se ha encontrado el archivo plugins.cfg.");
	if(!Ogre::FileSystemLayer::fileExists(mCfgPath)) throwOgreError(__LINE__, "No se ha encontrado el archivo ogre.cfg.");
	if(!Ogre::FileSystemLayer::fileExists(mLogPath)) throwOgreError(__LINE__, "No se ha encontrado el archivo ogre.log.");

	mRoot = new Ogre::Root(mPluginsCfgPath, mCfgPath, mLogPath);

	if(!mRoot) throwOgreError(__LINE__, "Error al crear la raiz de Ogre.");

	//Borrar ogre.cfg para mostrar la ventana de diagolo inicial.  Uso de GL3+ por defecto
	if (!mRoot->restoreConfig()) mRoot->showConfigDialog(OgreBites::getNativeConfigDialog());
}

/// <summary>
/// Crea la ventana de OGRE a partir de la de SDL (Input de SDL en OGRE)
/// </summary>
void OgreRenderer::initOgreWithSDL() {
	// Inicializacion SDL
	assert(SDL_GetError(), SDL_Init(SDL_INIT_VIDEO) != 0);
	mRoot->restoreConfig();

	// Se pasa el valor false para indiciar que vamos a construir la ventana nosotros, no se hace automaticamente
	mWindow = mRoot->initialise(false, "Juego");

	// Se accede a las opciones de configuracion del sistema de renderizado escogido
	Ogre::ConfigOptionMap ropts = mRoot->getRenderSystem()->getConfigOptions();
	std::istringstream resolution(ropts["Video Mode"].currentValue);

	uint32_t windowHeight, windowWidth;
	resolution >> windowWidth;
	std::string x;
	resolution >> x;
	resolution >> windowHeight;

	//if (!SDL_WasInit(SDL_INIT_VIDEO | SDL_INIT_TIMER))
	//	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
	//		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
	//		/*EXCEPCION*/
	//	}

	// Aqui se pueden establecer flags, algunos que pueden ser de utilidad mas adelante:
	// SDL_WINDOW_FULLSCREEN_DESKTOP, SDL_WINDOW_BORDERLESS
	int flags = 0;
	std::string appName_;

	// Creacion ventana SDL
	native = SDL_CreateWindow(appName_.c_str(), SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, flags);

	// Se obtiene informacion de la version de SDL
	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	if (!SDL_GetWindowWMInfo(native, &wmInfo))
	{
		assert(SDL_GetError(), false);
	}

	// Se inicializan parametros segun el sistema de renderizado y la version de SDL
	Ogre::NameValuePairList miscParams;

	miscParams["FSAA"] = ropts["FSAA"].currentValue;
	miscParams["vsync"] = ropts["VSync"].currentValue;
	miscParams["gamma"] = ropts["sRGB Gamma Conversion"].currentValue;
	miscParams["externalWindowHandle"] =
		Ogre::StringConverter::toString(size_t(wmInfo.info.win.window));

	// Creamos la ventana de OGRE con estos parametros
	mWindow = mRoot->createRenderWindow(appName_, windowWidth, windowHeight, false, &miscParams);

}

/// <summary>
/// Parsea el archivo resources.cfg para obtener las rutas de los recursos
/// </summary>
void OgreRenderer::loadResources()
{
	if (!Ogre::FileSystemLayer::fileExists(mResourcesCfgPath)) throwOgreError(__LINE__, "No se ha encontrado el archivo resources.cfg.");

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
	if (Ogre::RTShader::ShaderGenerator::initialize())
	{
		mShaderGenerator = Ogre::RTShader::ShaderGenerator::getSingletonPtr();

		// Create and register the material manager listener if it doesn't exist yet.
		if (!mMaterialMgrListener) {
			mMaterialMgrListener = new OgreBites::SGTechniqueResolverListener(mShaderGenerator);
			Ogre::MaterialManager::getSingleton().addListener(mMaterialMgrListener);
		}
	}
	else throwOgreError(__LINE__, "No se ha podido inicializar el sistema de shaders de Ogre.");

	mShaderGenerator->addSceneManager(mSceneMgr);
}

void OgreRenderer::destroyRTShaderSystem()
{
	mShaderGenerator->removeAllShaderBasedTechniques();
	mShaderGenerator->flushShaderCache();

    // Restore default scheme.
	Ogre::MaterialManager::getSingleton().setActiveScheme(Ogre::MaterialManager::DEFAULT_SCHEME_NAME);

	// Unregister the material manager listener.
	if (mMaterialMgrListener != nullptr)
	{
		Ogre::MaterialManager::getSingleton().removeListener(mMaterialMgrListener);
		//delete mMaterialMgrListener;
		mMaterialMgrListener = nullptr;
	}

	// Destroy RTShader system.
	if (mShaderGenerator != NULL)
	{
		Ogre::RTShader::ShaderGenerator::destroy();
		mShaderGenerator = NULL;
	}
}

/// <summary>
/// Crea la ventana inicial (camara y viewport) y el manejador de escenas
/// </summary>
void OgreRenderer::setupScenes()
{
	mSceneMgr = mRoot->createSceneManager();

	//mCameraNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	//mCameraNode->setPosition(0, 0, 80);
	//mCameraNode->lookAt(Ogre::Vector3(0, 0, -300), Ogre::Node::TransformSpace::TS_WORLD);

	//mCamera = mSceneMgr->createCamera("MainCam");
	//mCamera->setNearClipDistance(5);

	//mCameraNode->attachObject(mCamera);

	//Ogre::Viewport* vp = mWindow->addViewport(mCamera);

	//vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));

	//mCamera->setAspectRatio(
	//	Ogre::Real(vp->getActualWidth()) /
	//	Ogre::Real(vp->getActualHeight()));

	//Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	//Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

void OgreRenderer::throwOgreError(int errorLine, const std::string& errorMsg) {
	LoveEngine::ErrorHandling::throwError(__PROJECT_NAME__, errorLine, __FILENAME__, errorMsg);
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
	//Ogre::Entity* ogreEntity = mSceneMgr->createEntity("ogrehead.mesh");

	//Ogre::SceneNode* ogreNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	//ogreNode->attachObject(ogreEntity);

	mSceneMgr->setAmbientLight(Ogre::ColourValue(.5, .5, .5));
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
Ogre::RenderWindow* OgreRenderer::getRenderWindow()
{
	return mWindow;
}
