#include "Animation.h"
#include <OgreAnimation.h>
#include <OgreKeyFrame.h>
#include <OgreFrameListener.h>
#include <Timer.h>
#include <GameObject.h>
#include <Mesh.h>
#include <OgreEntity.h>
#include <GameTime.h>

namespace LoveEngine {
	namespace ECS {

		void Animation::receiveMessage(std::string animaState)
		{
			name = animaState;
		}

		void Animation::init()
		{
			animState = gameObject->getComponent<Mesh>()->getEntity()->getAnimationState(name);
		}

		Animation::~Animation()
		{

		}

		void Animation::setActive(bool activated)
		{
			isActive = activated;
			animState->setEnabled(activated);
		}

		void Animation::setLoop(bool activated)
		{
			animState->setLoop(activated);
		}

		void Animation::update()
		{
			animState->addTime(LoveEngine::Time::getInstance()->deltaTime);
		}

		bool Animation::playingAnimation(std::string animationName)
		{
			return (isActive && animationName == name);
		}
	}
}