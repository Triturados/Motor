#include "CameraComponent.h"

#include "OgreSceneManager.h"
#include "Component.h"
#include <iostream>
#include <OgreViewport.h>
#include <OgreCamera.h>
#include <OgreRenderWindow.h>


namespace LoveEngine {
	namespace ECS {

		CameraComponent::CameraComponent()
		{

		}

		CameraComponent::~CameraComponent()
		{

		}

		void CameraComponent::getParameters(Ogre::RenderWindow* window, Ogre::SceneManager* manager)
		{
			mWindow = window;
			mSceneMgr = manager;

			mCameraNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
			mCameraNode->setPosition(0, 0, 80);
			mCameraNode->lookAt(Ogre::Vector3(0, 0, -300), Ogre::Node::TransformSpace::TS_WORLD);

			mCamera = mSceneMgr->createCamera("MainCam");
			mCamera->setNearClipDistance(5);

			mCameraNode->attachObject(mCamera);


			vp = mWindow->addViewport(mCamera);

			vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));

			mCamera->setAspectRatio(
				Ogre::Real(vp->getActualWidth()) /
				Ogre::Real(vp->getActualHeight()));
		}
	}
}