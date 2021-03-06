#pragma once
#include <../Export.h>

#ifndef ANIMATION_H
#define ANIMATION_H

#include <Component.h>
#include <string>


//namespace Utilities {
//	template<typename T>
//	class Vector3;
//	template<typename T>
//	class Vector4;
//}
namespace Ogre {
	class SceneNode;
	class Entity;
	class AnimationState;
}

namespace LoveEngine {
	namespace ECS {

		class lovexport Animation : public Component
		{
		private:
			Ogre::AnimationState* animState = nullptr;
			bool isActive;
			bool initialState = false;
			bool initialLoop = false;
			std::string name;
		public:
			void receiveMessage(Utilities::StringFormatter& message) override;

			void setActive(bool activated = true);
			void setLoop(bool activated = true);
			void changeAnimation(const  std::string& n );

			void resetAnim();
			float getDuration();

			void init() override;
			void update() override;

			bool playingAnimation(const  std::string& animationName);

			~Animation();
		};
	}
}
#endif
