#pragma once

#include <../Export.h>

#include <Component.h>
#include <vector>

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
			std::string name;
			Ogre::Camera* mCamera;
			Ogre::SceneNode* mCameraNode;

			Ogre::Viewport* vp;
			Transform* tr;
			Transform* player;

			Utilities::Vector4<float>* rot;
			Utilities::Vector3<float>* pos;
			Utilities::Vector3<float>* scale;

			Renderer::OgreRenderer* ogremanager;
			int viewportZorder = 0;

			// usado solo para almacenar los compositores que se añaden antes del init
			std::vector<std::string> compositors = std::vector<std::string>();

		public:
			~Camera();

			void init() override;

			void lookAt(Utilities::Vector3<float> pos);
			void lookAtDir(float x, float y, float z);
			void onSceneUp() override;
			void onSceneDown() override;
			void receiveMessage(Utilities::StringFormatter& sf)override;
			void update()override;

			void yaw(float angle);
			void pitch(float angle);
			void roll(float angle);
			
			void applyCompositor(std::string compositor);
		};
	}
}