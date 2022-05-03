#pragma once
#include <../Export.h>

#ifndef PARTICLESYS_H
#define PARTICLESYS_H

#include <Component.h>
#include <string>

namespace Ogre {
	class SceneNode;
	class Entity;
	class AnimationState;
	class ParticleSystem;
}

namespace LoveEngine {
	namespace Renderer {
		class OgreRenderer;
	}

	namespace ECS {
		class Transform;

		class lovexport ParticleSystem : public Component
		{
		private:
			Ogre::ParticleSystem* pSys = nullptr;
			Ogre::SceneNode* entityNode = nullptr;
			std::string templateName = "";
			std::string particleName = "";
			Transform* tr = nullptr;
			Utilities::Vector3<float>* rot;
			Utilities::Vector3<float>* pos;
			Utilities::Vector3<float>* scale;
			bool emitting = false;

			Renderer::OgreRenderer* ogremanager;
		public:
			void receiveMessage(Utilities::StringFormatter& message) override;

			void setActive(bool activated = true);
			bool isEmitting();
			void setMaterial(std::string materialName);

			void init() override;
			void update() override;

			void onSceneUp() override;
			void onSceneDown() override;

			Ogre::ParticleSystem* getPSys();
			~ParticleSystem();
		};
	}
}
#endif
