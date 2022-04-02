#pragma once

#include <../Export.h>

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

		class Transform;

		class lovexport Camera : public Component
		{
			Ogre::Camera* mCamera;
			Ogre::SceneNode* mCameraNode;

			Ogre::Viewport* vp;
			Transform* position;
			Transform* player;
		public:

			
			~Camera();

			void sendvalues(Transform* playerPos = nullptr);

			void lookAtPlayer(Transform* playerPos = nullptr);

			void lookAt(Utilities::Vector3<float>* pos);
		};
	}
}