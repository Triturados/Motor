#pragma once

#include <../Export.h>

#include <Component.h>

class OgreSceneManager;
class Transform;

namespace Ogre {
	class SceneNode;
	class SceneManager;
	class Viewport;
	class Camera;
}


namespace LoveEngine {

	namespace Utilities {
		template<typename T>
		class Vector3;
	}
	namespace Renderer {
		class OgreRenderer;
	}
	namespace ECS {

		class Transform;

		class lovexport Camera : public Component
		{
			Ogre::Camera* mCamera;
			Ogre::SceneNode* mCameraNode;

			Ogre::Viewport* vp;
			Transform* position;
			Transform* player;

			Renderer::OgreRenderer* ogremanager;

		public:
			~Camera();

			void init() override;

			void lookAt(Utilities::Vector3<float> pos);
			void lookAtDir(float x, float y, float z);
			void onSceneUp() override;
			void onSceneDown() override;

			void yaw(float angle);
			void pitch(float angle);
			void roll(float angle);
		};
	}
}