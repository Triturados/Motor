#include "Animation.h"
#include <OgreAnimation.h>
#include <OgreKeyFrame.h>
#include <OgreFrameListener.h>
#include <Timer.h>
#include <GameObject.h>
#include <Mesh.h>
#include <OgreEntity.h>
#include <GameTime.h>
#include <StringFormatter.h>

namespace LoveEngine {
	namespace ECS {

		void Animation::receiveMessage(Utilities::StringFormatter& sf)
		{
			name = sf.getString("animName");
			sf.tryGetBool("initialState", initialState);
			setActive(initialState);

			sf.tryGetBool("initialLoopss", initialLoop);
			setLoop(initialLoop);
		}

		void Animation::init()
		{
			animState = gameObject->getComponent<Mesh>()->getEntity()->getAnimationState(name);
			setLoop(initialLoop);
			setActive(initialState);
		}

		void Animation::changeAnimation(std::string n)
		{
			name = n;
			setActive(false);
			setLoop(false);
			animState = gameObject->getComponent<Mesh>()->getEntity()->getAnimationState(name);
			setActive(true);
		}

		void Animation::resetAnim()
		{
			animState->setTimePosition(0);
		}

		float Animation::getDuration()
		{
			return animState->getLength();
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
			if (isActive)
				animState->addTime(LoveEngine::Time::getInstance()->deltaTime);
		}

		bool Animation::playingAnimation(std::string animationName)
		{
			return (isActive && animationName == name);
		}
	}
}