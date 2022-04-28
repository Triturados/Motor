#include "SplashScreen.h"
#include <Scene.h>
#include <GameObject.h>
#include <Mesh.h>
#include <Image.h>
#include <Timer.h>
#include <SceneManager.h>
#include <iostream>
#include <StringFormatter.h>
#include <GameTime.h>
namespace LoveEngine {

	namespace SceneManagement {
		void populateSplashScreen(ECS::Scene* scene) {

			auto camera = scene->createGameObject("Camera");
			camera->createComponent("Transform")->sendFormattedString("scale: 1,1,1; position: 0, 15, 75; rotation: 0, 0, 0, 0; ");
			camera->createComponent("Camera")->sendFormattedString("cameraName: escenaSplash");

			auto gameObject = scene->createGameObject("Background");
			gameObject->createComponent("Image")->sendFormattedString("material: splashScreen_background; width: 1280; height : 720; posZ: 0");

			gameObject = scene->createGameObject("White");
			gameObject->createComponent("Image")->sendFormattedString("material: splashScreen_white; width: 1280; height : 720; posY: 480; posZ: 1");
			gameObject->addComponent<FillIcon>()->sendFormattedString("speed: -100.0");
			
			gameObject = scene->createGameObject("Content");
			gameObject->createComponent("Image")->sendFormattedString("material: splashScreen_content; width: 1280; height : 720; posZ: 2");

			gameObject = scene->createGameObject("Vignette");
			gameObject->createComponent("Image")->sendFormattedString("material: splashScreen_vignette; width: 1280; height : 720; posZ: 20");


			ECS::Timer::invoke([&](ECS::Timer*) {
				changeScene(0, SceneLoad::SWAP);
				 }, 3.0f);

		}
	}
	void FillIcon::update()
	{
		ypos += speed * Time::getInstance()->deltaTime;
		auto pos = img->getPos();
		pos.y = round(ypos);
		img->setPos(pos);
	}
	void FillIcon::receiveMessage(Utilities::StringFormatter& sf)
	{
		speed = sf.getFloat("speed");
	}
	void FillIcon::init()
	{
		img = gameObject->getComponent<ECS::Image>();
		ypos = img->getPos().y;
	}
}