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
#include <SingletonInfo.h>
#include <OgreOverlay.h>
#include <OgreOverlayManager.h>
#include <OgreOverlayContainer.h>
#include <OgreOverlayPrerequisites.h>
#include <OgreTextAreaOverlayElement.h>
#include "OgreStringConverter.h"
#include <OgreBorderPanelOverlayElement.h>
#include <OgreOverlaySystem.h>
#include <OgreOverlayContainer.h>
#include "Window.h"
#include <Vector4.h>
namespace LoveEngine {
	namespace Renderer {
		OgreRenderer* OgreRenderer::instance = nullptr;

		OgreRenderer* OgreRenderer::getInstance()
		{
			if (instance == nullptr) {
				instance = static_cast<OgreRenderer*>(Singleton::getElement(Singleton::positions::Renderer));
			}

			return instance;
		}

		OgreRenderer::OgreRenderer()
		{
			if (instance != nullptr) throwOgreError(__LINE__, "Ya existe una instancia del OgreManager.");

			instance = this;

			initRoot();

			initOgreWithSDL();
			//mWindow = mRoot->initialise(true, "Juego");

			loadResources();
			setupScenes();
			Singleton::addElement(this, Singleton::positions::Renderer);
			overlaySystem = new Ogre::OverlaySystem();
			overlayManager = Ogre::OverlayManager::getSingletonPtr();
			mSceneMgr->addRenderQueueListener(overlaySystem);
			initRTShaderSystem();
			numOfImages = 0;
		}

		/// <summary>
		/// Inicializa la raiz
		/// </summary>
		void OgreRenderer::initRoot() {

			mResourcesCfgPath = "./OGRE/resources.cfg";
			mPluginsCfgPath = "./OGRE/plugins/plugins.cfg";
			mLogPath = "./OGRE/Ogre.log";
			mCfgPath = "./OGRE/ogre.cfg";

			if (!Ogre::FileSystemLayer::fileExists(mPluginsCfgPath)) throwOgreError(__LINE__, "No se ha encontrado el archivo plugins.cfg.");
			if (!Ogre::FileSystemLayer::fileExists(mCfgPath)) throwOgreError(__LINE__, "No se ha encontrado el archivo ogre.cfg.");
			if (!Ogre::FileSystemLayer::fileExists(mLogPath)) throwOgreError(__LINE__, "No se ha encontrado el archivo ogre.log.");

			mRoot = new Ogre::Root(mPluginsCfgPath, mCfgPath, mLogPath);

			if (!mRoot) throwOgreError(__LINE__, "Error al crear la raiz de Ogre.");

			//Borrar ogre.cfg para mostrar la ventana de diagolo inicial.  Uso de GL3+ por defecto
			if (!mRoot->restoreConfig()) mRoot->showConfigDialog(OgreBites::getNativeConfigDialog());
		}

		/// <summary>
		/// Crea la ventana de OGRE a partir de la de SDL (Input de SDL en OGRE)
		/// </summary>
		void OgreRenderer::initOgreWithSDL() {
			// Inicializacion SDL
			int sdlinit = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);
			assert(SDL_GetError(), sdlinit != 0);
			SDL_JoystickEventState(SDL_ENABLE);
			SDL_JoystickUpdate();
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
			std::string appName_ = "Love";

			// Creacion ventana SDL
			native = SDL_CreateWindow(appName_.c_str(), SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, flags);

			//puntero ventana
			const auto g = SDL_bool(true);
			//SDL_SetWindowGrab(native, g);
			SDL_ShowCursor(true);

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

			Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
			Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
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

		Window* OgreRenderer::getWindowInfo()
		{
			if (windowinfo == nullptr)
			{
				windowinfo = new Window(this);
			}

			return windowinfo;
		}

		void OgreRenderer::exampleScene()
		{
			mSceneMgr->setAmbientLight(Ogre::ColourValue(.5, .5, .5));
		}

		void OgreRenderer::changeWindowTitle(std::string title)
		{
			SDL_SetWindowTitle(native, title.c_str());
		}

		//NO SE USA
		SDL_Texture* OgreRenderer::createSDLTexture(const char* texName, int& width, int& height)
		{
			SDL_Surface* sur = SDL_LoadBMP(texName);
			SDL_Texture* texture = SDL_CreateTextureFromSurface(sdlRenderer, sur);
			width = sur->w; height = sur->h;
			SDL_FreeSurface(sur);
			return texture;

		}
		/// <summary>
		/// Muestra una imagen 2D por pantalla como Ogre::Overlay
		/// </summary>
		Ogre::OverlayContainer* OgreRenderer::renderImage(int x, int y, int w, int h, std::string material, Ogre::Overlay*& overlay)
		{
			// Elemento que contendra el overlay
			Ogre::OverlayContainer* container = static_cast<Ogre::OverlayContainer*>(
				overlayManager->createOverlayElement("Panel", "Image" + std::to_string(numOfImages)));
			container->setMetricsMode(Ogre::GMM_PIXELS);
			container->setPosition(x, y);
			container->setDimensions(w, h);

			//material que tiene que estar definido en los recursos de Ogre. Se tiene que pasar el nombre del material, no el archivo .material
			container->setMaterialName(material);

			// El overlay, que gestiona la poscion, rotacion...
			overlay = overlayManager->create("Image" + std::to_string(numOfImages));
			overlay->add2D(container);

			/*overlay->rotate(Ogre::Radian(Ogre::Angle(90)));*/

			// Mostrar el overlay
			overlay->show();
			numOfImages++;
			return container;
		}

		void OgreRenderer::disableOverlay(Ogre::Overlay* ov)
		{
			overlayManager->destroy(ov);
		}

		Ogre::TextAreaOverlayElement* OgreRenderer::createOverlayElement(std::string typeName)
		{

			//WithoutChild
			Ogre::OverlayContainer* panel = static_cast<Ogre::OverlayContainer*>(overlayManager->createOverlayElement("Panel", "GUI"));
			panel->setMetricsMode(Ogre::GMM_PIXELS);
			panel->setPosition(0, 0);
			panel->setDimensions(1.0f, 1.0f);
			Ogre::Overlay* o = overlayManager->create("GUI_OVERLAY");
			o->add2D(panel);

			int num = 0;
			std::string szElement = "element_"+typeName;
			Ogre::Overlay* overlay = overlayManager->getByName("GUI_OVERLAY");
			panel = static_cast<Ogre::OverlayContainer*>(overlayManager->getOverlayElement("GUI"));
			Ogre::TextAreaOverlayElement* textArea = static_cast<Ogre::TextAreaOverlayElement*>(overlayManager->createOverlayElement("TextArea", szElement));
			panel->addChild(textArea);
			overlay->show();


			return textArea;

		}

		void OgreRenderer::destroyText(std::string elemName)
		{
			std::string szElement = "element_" + elemName;
			overlayManager->destroyOverlayElement(szElement);
			--(initForText);
			if (initForText == 0)
			{
				//Destruimos los dos elementos que componenel texto 
				overlayManager->destroyOverlayElement("GUI");
				overlayManager->destroy("GUI_OVERLAY" + elemName);
			}
			
		}

		void OgreRenderer::setText(std::string info, int width, int height, Ogre::TextAreaOverlayElement* tArea,float charHeight)
		{
			tArea->setCaption(info);
			tArea->setDimensions(width,height);
			tArea->setMetricsMode(Ogre::GMM_RELATIVE);
			//tArea->setFontName("arial");
			tArea->setCharHeight(charHeight);
		}

		void OgreRenderer::setTextPos(int x, int y, Ogre::TextAreaOverlayElement* tArea)
		{
			tArea->setPosition(x, y);
		}

		void OgreRenderer::setTextColor(float R, float G, float B, float I, Ogre::TextAreaOverlayElement* tArea)
		{
			tArea->setColour(Ogre::ColourValue(R, G, B, I));
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

			SDL_Quit();
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

	}
}
