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

			void sendValues(int i, float f, Component* playerPos, GameObject* g) override;

			void lookAt(Utilities::Vector3<float>* pos);
			void onSceneUp() override;
			void onSceneDown() override;
		};
	}
}