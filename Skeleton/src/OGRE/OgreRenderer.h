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
			Ogre::Overlay* o;

			Ogre::Camera* mCamera;
			Ogre::SceneNode* mCameraNode;

			Ogre::RTShader::ShaderGenerator* mShaderGenerator;
			Ogre::MaterialManager::Listener* mMaterialMgrListener;

			//Interfaz
			int numOfImages, numOverlays;
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

			//Interfaz
			SDL_Texture* createSDLTexture(const char* texName, int& width, int& height);
			Ogre::OverlayContainer* renderImage(Utilities::Vector3<int> pos, Utilities::Vector2<int> dimensions, std::string material, Ogre::Overlay*& overlay);
			Ogre::OverlayContainer* createContainer(Utilities::Vector3<int> pos, Utilities::Vector2<int> dimensions);
			Ogre::Overlay* createOverlay();

			void disableOverlay(Ogre::Overlay*);
			Ogre::TextAreaOverlayElement* createOverlayElement(std::string typeName);
			void destroyText(std::string textName);
			void setText(std::string info, Utilities::Vector2<int>dimensions, Ogre::TextAreaOverlayElement* tArea,float charHeight,int alignment);
			void setTextPos(Utilities::Vector3<int> pos_, Ogre::TextAreaOverlayElement* tArea);
			void setTextColor(float R, float G, float B, float I, Ogre::TextAreaOverlayElement* tArea);
			~OgreRenderer();
		};


	}
}

#endif // !OGRERENDERER_H
