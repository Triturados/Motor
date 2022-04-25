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
class SDL_Surface;
class SDL_Texture;
class SDL_Rect;
class SDL_SysWMinfo;
namespace LoveEngine {

	class Window;
	namespace Utilities {
		template<typename T>
		class Vector4;
		template<typename T>
		class Vector3;
		template<typename T>
		class Vector2;
	}
	namespace Renderer {
		class lovexport OgreRenderer
		{
			friend LoveEngine::Window;
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

			//UI
			int numOfImages, numOverlays;
			Ogre::OverlaySystem* overlaySystem;
			Ogre::OverlayManager* overlayManager;

			int numOfTexts;
			Ogre::OverlayContainer* textContainer;
			Ogre::Overlay* textOverlay;

			SDL_Surface* icon;

			void loadResources();
			void initOgreWithSDL();
			void initRTShaderSystem();
			void destroyRTShaderSystem();
			void setupScenes();

			void throwOgreError(int errorLine, const std::string& errorMsg);

			Window* windowinfo;
			static OgreRenderer* instance;

			Ogre::OverlayContainer* createTextPanel(const std::string& textPanelName);
			Ogre::Overlay* createTextOverlay(const std::string& overlayName);

			//Window
			void resizeWindow(Utilities::Vector2<int>);
			void resizeWindow(int x, int y);
			void changeWindowTitle(std::string);
			std::string getWindowTitle();
			Window* getWindowInfo();
			void setFullScreen(bool);
			void repositionWindow(int x, int y);
			void setWindowIcon(std::string path);
		public:
			static OgreRenderer* getInstance();
			OgreRenderer();

			void initRoot();
			bool update();



			Ogre::SceneNode* createNode();
			Ogre::SceneNode* createChildNode(Ogre::SceneNode* parent);
			void removeNode(Ogre::SceneNode* node);

			Ogre::SceneManager* getSceneManager();
			Ogre::RenderWindow* getRenderWindow();

			void exampleScene();

			void applyCompositor(Ogre::Viewport* vp, std::string compositor);

			//Image UI
			SDL_Texture* createSDLTexture(const char* texName, int& width, int& height);
			Ogre::OverlayContainer* renderImage(Utilities::Vector3<int> pos, Utilities::Vector2<int> dimensions, std::string material, Ogre::Overlay*& overlay);
			Ogre::OverlayContainer* createContainer(Utilities::Vector3<int> pos, Utilities::Vector2<int> dimensions);
			
			void setImageOpacity(Ogre::OverlayContainer* container, float fade);

			Ogre::Overlay* createOverlay();
			void disableContainer(Ogre::OverlayContainer* overlayContainer);
			void disableOverlay(Ogre::Overlay* overlay);

			//Text UI
			Ogre::TextAreaOverlayElement* createOverlayElement();
			void setTextOverlayZOrder(float zOrder);

			~OgreRenderer();
		};


	}
}

#endif // !OGRERENDERER_H
