#pragma once

#include <Component.h>
#include <OgreRenderer.h>
#include <OgreSceneNode.h>

class OgreSceneManager;

namespace LoveEngine {
	namespace ECS {

		class CameraComponent : public Component
		{
			Ogre::Camera* mCamera;
			Ogre::SceneNode* mCameraNode;
			Ogre::SceneManager* mSceneMgr;

			Ogre::Viewport* vp;
			Ogre::RenderWindow* mWindow;
		public:

			CameraComponent();
			~CameraComponent();

			void getParameters(Ogre::RenderWindow* window, Ogre::SceneManager* manager);
		};
	}
}