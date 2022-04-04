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

			void receiveValues(int i, float f, Component* playerPos, GameObject* g) override;
			void init() override;

			void lookAt(Utilities::Vector3<float> pos);
			void lookAtDir(float x, float y, float z);
			void onSceneUp() override;
			void onSceneDown() override;
		};
	}
}