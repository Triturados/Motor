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

			ogremanager->removeNode(mCameraNode);
		}

		void Camera::receiveValues(int i, float f, Component* playerPos, GameObject* g)
		{
		
		}

		void Camera::init()
		{
			ogremanager = Renderer::OgreRenderer::getInstance();
			position = gameObject->getComponent<Transform>();
			mCameraNode = ogremanager->getSceneManager()->getRootSceneNode()->createChildSceneNode();
			mCameraNode->setPosition(position->getPos()->x, position->getPos()->y, position->getPos()->z);
			mCameraNode->lookAt(Ogre::Vector3(0, 0, -300), Ogre::Node::TransformSpace::TS_WORLD);

			mCamera = ogremanager->getSceneManager()->createCamera("MainCam");
			mCamera->setNearClipDistance(5);

			mCameraNode->attachObject(mCamera);

			vp = ogremanager->getRenderWindow()->addViewport(mCamera);

			vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));

			mCamera->setAspectRatio(
				Ogre::Real(vp->getActualWidth()) /
				Ogre::Real(vp->getActualHeight()));
		}

		void Camera::lookAt(Utilities::Vector3<float> pos)
		{
			mCameraNode->lookAt(Ogre::Vector3(pos.x, pos.y, pos.z), Ogre::Node::TransformSpace::TS_WORLD);
		}

		void Camera::lookAtDir(float x, float y, float z)
		{
			lookAt(Utilities::Vector3(x, y, z));
		}

		void Camera::onSceneDown()
		{
			//mCameraNode->setVisible(false);
		}
		void Camera::onSceneUp()
		{
			//mCameraNode->setVisible(true);
		}
	}
}