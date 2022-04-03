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
}

class SDL_Window;
namespace LoveEngine {
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
			Ogre::SceneManager* mSceneMgr;

			Ogre::Camera* mCamera;
			Ogre::SceneNode* mCameraNode;

			Ogre::RTShader::ShaderGenerator* mShaderGenerator;
			Ogre::MaterialManager::Listener* mMaterialMgrListener;

			void loadResources();
			void initOgreWithSDL();
			void initRTShaderSystem();
			void destroyRTShaderSystem();
			void setupScenes();

			void throwOgreError(int errorLine, const std::string& errorMsg);

		public:

			static OgreRenderer* instance;
			OgreRenderer();

			void initRoot();
			bool update();

			Ogre::SceneNode* createNode();
			Ogre::SceneNode* createChildNode(Ogre::SceneNode* parent);
			void removeNode(Ogre::SceneNode* node);

			Ogre::SceneManager* getSceneManager();
			Ogre::RenderWindow* getRenderWindow();

			void exampleScene();


			~OgreRenderer();
		};


	}
}

#endif // !OGRERENDERER_H
