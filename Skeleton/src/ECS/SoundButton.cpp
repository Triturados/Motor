#include "SoundButton.h"
#include <stdexcept>
#include <OgreRenderer.h>
#include <Input.h>
#include <GameObject.h>
#include <Button.h>
#include <Sound.h>

void LoveEngine::ECS::SoundButton::init()
{
	button = gameObject->getComponent<Button>();
	sound = gameObject->getComponent<Sound>();
}

void LoveEngine::ECS::SoundButton::postInit()
{
	button->onClick([&]() {	sound->playSound(); });
}
