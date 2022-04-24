#include "CameraComponent.h"
#include <iostream>
#include "OgreLight.h"
#include "OgreSceneManager.h"
#include <Ogre.h>
#include <OgreRenderer.h>
#include <OgreSceneNode.h>
#include <OgreViewport.h>
#include <OgreCamera.h>
#include "Transform.h"
#include "GameObject.h"
#include <Vector3.h>
#include <Vector4.h>
#include <StringFormatter.h>

namespace LoveEngine {
	namespace ECS {

		Camera::~Camera()
		{
			if (mCamera != nullptr)
				ogremanager->getSceneManager()->destroyCamera(mCamera);
			
			ogremanager->getRenderWindow()->removeViewport(viewportZorder);
		}

		void Camera::init()
		{
			ogremanager = Renderer::OgreRenderer::getInstance();
			tr = gameObject->getComponent<Transform>();
			
			mCameraNode = ogremanager->getSceneManager()->getRootSceneNode()->createChildSceneNode();
			mCameraNode->setPosition(tr->getPos()->x, tr->getPos()->y, tr->getPos()->z);
			
			mCameraNode->lookAt(Ogre::Vector3(0, 0, -300), Ogre::Node::TransformSpace::TS_WORLD);

			mCamera = ogremanager->getSceneManager()->createCamera(name);
			mCamera->setNearClipDistance(5);

			mCameraNode->attachObject(mCamera);

			vp = ogremanager->getRenderWindow()->addViewport(mCamera, viewportZorder);

			vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));

			mCamera->setAspectRatio(
				Ogre::Real(vp->getActualWidth()) /
				Ogre::Real(vp->getActualHeight()));
		}

		void Camera::update()
		{
			rot = tr->getRot();
			pos = tr->getPos();
			scale = tr->getScale();

			mCameraNode->setPosition(Ogre::Vector3(pos->x, pos->y, pos->z));
			mCameraNode->setScale(Ogre::Vector3(scale->x, scale->y, scale->z));

			mCameraNode->resetOrientation();
			mCameraNode->pitch(Ogre::Radian(rot->x), Ogre::Node::TS_WORLD);
			mCameraNode->yaw(Ogre::Radian(rot->y), Ogre::Node::TS_WORLD);
			mCameraNode->roll(Ogre::Radian(rot->z), Ogre::Node::TS_WORLD);
			//Usar Translate , Scale, y luego la rotacion esta por ver 
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
			mCameraNode->setVisible(false);
		}
		void Camera::yaw(float angle)
		{
			mCameraNode->yaw(Ogre::Radian(angle));
		}
		void Camera::pitch(float angle)
		{
			mCameraNode->pitch(Ogre::Radian(angle));
		}
		void Camera::roll(float angle)
		{
			mCameraNode->roll(Ogre::Radian(angle));
		}
		void Camera::onSceneUp()
		{
			//mCameraNode->setVisible(true);
		}

		void Camera::receiveMessage(Utilities::StringFormatter& sf)
		{
			sf.tryGetString("name", name);
			sf.tryGetInt("zOrder", viewportZorder);
		}
	}
}