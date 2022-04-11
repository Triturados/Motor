#pragma once
#ifndef OGRERENDERER_H
#define OGRERENDERER_H
#include <../Export.h>
// Estos dos archivos incluyen clases anidadas (MaterialManagerListener y ShaderGenerator resp.) que se referencian como atributos de OgreRenderer.
// Como no se puede hacer forward declaration de las clases anidadas, los archivos tienen que estar incluidos.
#include <OgreMaterialManager.h>;
#include <OgreRTShaderSystem.h>

namespace Ogre {
	class Root;
	class Camera;
	class RenderWindow;
	class SceneManager;
	class SceneNode;
	class OverlayManager;
	class OverlaySystem;
	class Overlay;
	class OverlayContainer;
	class TextAreaOverlayElement;
}

class SDL_Window;
class SDL_Renderer;
class SDL_Texture;
class SDL_Rect;
class SDL_SysWMinfo;
namespace LoveEngine {

	class Window;

	namespace Renderer {
		class lovexport OgreRenderer
		{
		private:
			Ogre::Root* mRoot;
			Ogre::String mResourcesCfgPath;
			Ogre::String mPluginsCfgPath;
			Ogre::String mCfgPath;
			Ogre::String mLogPath;

			Ogre::RenderWindow* mWindow;
			SDL_Window* native;
			SDL_Renderer* sdlRenderer;
			Ogre::SceneManager* mSceneMgr;

			Ogre::Camera* mCamera;
			Ogre::SceneNode* mCameraNode;

			Ogre::RTShader::ShaderGenerator* mShaderGenerator;
			Ogre::MaterialManager::Listener* mMaterialMgrListener;

			int numOfImages;
			Ogre::OverlaySystem* overlaySystem;
			Ogre::OverlayManager* overlayManager;

			void loadResources();
			void initOgreWithSDL();
			void initRTShaderSystem();
			void destroyRTShaderSystem();
			void setupScenes();

			void throwOgreError(int errorLine, const std::string& errorMsg);

			Window* windowinfo;
			static OgreRenderer* instance;
			int initForText=0;
		public:
			static OgreRenderer* getInstance();
			OgreRenderer();

			void initRoot();
			bool update();

			Window* getWindowInfo();

			Ogre::SceneNode* createNode();
			Ogre::SceneNode* createChildNode(Ogre::SceneNode* parent);
			void removeNode(Ogre::SceneNode* node);

			Ogre::SceneManager* getSceneManager();
			Ogre::RenderWindow* getRenderWindow();

			void exampleScene();
			void changeWindowTitle(std::string);

			SDL_Texture* createSDLTexture(const char* texName, int& width, int& height);
			Ogre::OverlayContainer* renderImage(int x, int y, int w, int h, std::string material, Ogre::Overlay*& overlay);

			void disableOverlay(Ogre::Overlay*);
			Ogre::TextAreaOverlayElement* createOverlayElement( std::string typeName);
			void destroyText();

			~OgreRenderer();
		};


	}
}

#endif // !OGRERENDERER_H
