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

		void CameraComponent::getParameters(Transform* pos)
		{
			position = pos;

			mCameraNode = OgreRenderer::instance->getSceneManager()->getRootSceneNode()->createChildSceneNode();
			mCameraNode->setPosition(position->getPos()->x, position->getPos()->y, position->getPos()->z);
			mCameraNode->lookAt(Ogre::Vector3(0, 0, -300), Ogre::Node::TransformSpace::TS_WORLD);

			mCamera = OgreRenderer::instance->getSceneManager()->createCamera("MainCam");
			mCamera->setNearClipDistance(5);

			mCameraNode->attachObject(mCamera);


			vp = OgreRenderer::instance->getRenderWindow()->addViewport(mCamera);

			vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));

			mCamera->setAspectRatio(
				Ogre::Real(vp->getActualWidth()) /
				Ogre::Real(vp->getActualHeight()));
		}

		void CameraComponent::lookAt(Utilities::Vector3<float> pos)
		{
			mCameraNode->lookAt(Ogre::Vector3(pos.x, pos.y, pos.z), Ogre::Node::TransformSpace::TS_WORLD);
		}

	}
}