#pragma once


#include <Component.h>
#include <OgreRenderer.h>
#include <OgreSceneNode.h>

class OgreSceneManager;
class Transform;

namespace Ogre {
	class SceneNode;
	class SceneManager;
}

namespace Utilities {
	template<typename T>
	class Vector3;
}

namespace LoveEngine {
	namespace ECS {

		class CameraComponent : public Component
		{
			Ogre::Camera* mCamera;
			Ogre::SceneNode* mCameraNode;

			Ogre::Viewport* vp;
			Transform* position;
		public:

			CameraComponent();
			~CameraComponent();

			void getParameters(Transform* pos);

			void lookAt(Utilities::Vector3<float>* pos);
		};
	}
}