#include "CameraComponent.h"
#include <iostream>
#include "OgreLight.h"
#include "OgreSceneManager.h"
#include <Ogre.h>
#include <OgreRenderer.h>
#include <OgreSceneNode.h>
#include "Transform.h"
#include "GameObject.h"
#include <Vector3.h>
#include <Vector4.h>

namespace LoveEngine {
	namespace ECS {

		Camera::~Camera()
		{

			OgreRenderer::instance->removeNode(mCameraNode);
		}

		void Camera::sendvalues(Transform* pos)
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

		void Camera::lookAtPlayer(Transform* playerPos)
		{
			/*Utilities::Vector3<float>* pos = playerPos->getPos();
			mCameraNode->lookAt(Ogre::Vector3(pos->x, pos->y, pos->z), Ogre::Node::TransformSpace::TS_WORLD);*/
		}

		void Camera::lookAt(Utilities::Vector3<float>* pos)
		{
			mCameraNode->lookAt(Ogre::Vector3(pos->x, pos->y, pos->z), Ogre::Node::TransformSpace::TS_WORLD);
		}
		void Camera::onSceneDown()
		{
			mCameraNode->setVisible(false);
		}
		void Camera::onSceneUp()
		{
			mCameraNode->setVisible(true);
		}
	}
}