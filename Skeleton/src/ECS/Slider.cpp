#include "Slider.h"
#include "Transform.h"
#include <stdexcept>
#include <OgreRenderer.h>
#include <Input.h>
#include <GameObject.h>

#include <Vector2.h>
#include <Ogre.h>
#include <string>
#include <iostream>
#include <StringFormatter.h>

#include <OgreOverlay.h>
#include <OgreOverlayManager.h>
#include <OgreOverlayContainer.h>
#include <OgreOverlayPrerequisites.h>
#include <OgreTextAreaOverlayElement.h>
#include <OgreBorderPanelOverlayElement.h>
#include <OgreOverlaySystem.h>
#include <OgreOverlayContainer.h>
namespace LoveEngine {
	namespace ECS {

		
		void Slider::receiveMessage(Utilities::StringFormatter& sf)
		{
			materialBar = sf.getString("materialBar");
			materialBarBg = sf.getString("materialBarBg");
			materialButton = sf.getString("materialButton");

			sf.tryGetInt("width" , width);
			sf.tryGetInt("height", height);
			sf.tryGetInt("posX", posX);
			sf.tryGetInt("posY", posY);
		}

		void Slider::init() {
			ogremanager = Renderer::OgreRenderer::getInstance();
			inputmanager = Input::InputManager::getInstance();

			if (materialBar == "") throw new std::exception("El material no tiene nombre");
			if (materialButton == "") throw new std::exception("El material no tiene nombre");
			
			buttonTr = gameObject->getComponent<Transform>();
			if(!buttonTr) throw new std::exception("Se necesita transform para usar el componente Image");


			inferiorBar = ogremanager->createContainer(posX, posY, width, height);
			inferiorBar->setMaterialName(materialBarBg);
			superiorBar = ogremanager->createContainer(posX, posY, width, height);
			superiorBar->setMaterialName(materialBar);
			button = ogremanager->createContainer(posX + width - buttonWidth/2, posY + height/4, buttonWidth, buttonWidth);
			button->setMaterialName(materialButton);

			// El overlay, que gestiona la poscion, rotacion...
			overlayBar = ogremanager->createOverlay();
			//overlayBarBg = ogremanager->createOverlay();
			overlayBar->add2D(inferiorBar);
			overlayBar->add2D(superiorBar);
			overlayBar->add2D(button);

			/*overlay->rotate(Ogre::Radian(Ogre::Angle(90)));*/

			// Mostrar el overlay
			overlayBar->show();
			//overlayBarBg->show();

			buttonTr->setPos({ (float)posX + width - buttonWidth / 2,(float)posY + height / 4, (float)0 });
		}

		//No se llama el update 
		void Slider::update()
		{
			Utilities::Vector2<float> mousePos = inputmanager->mousePosition();
			if (inputmanager->mousePressed(Input::MouseState::CLICK_L)) {
				if (mousePos.x >= buttonTr->getPos()->x &&
					mousePos.x <= buttonTr->getPos()->x + buttonWidth &&
					mousePos.y >= buttonTr->getPos()->y &&
					mousePos.y <= buttonTr->getPos()->y + buttonWidth
					) {
					tracking = true;
				}
			}
			else tracking = false;

			if (tracking) {
				std::cout << "SLIDER SLIDEA";
				float newXpos = mousePos.x;
				if (newXpos < posX) newXpos = posX;
				if (newXpos > posX + width - buttonWidth / 2) newXpos = posX + width - buttonWidth / 2;
				buttonTr->setPos({ newXpos,buttonTr->getPos()->y,0.0f });
				int barWidth = mousePos.x - posX;
				if (barWidth < 0) barWidth = 0;
				if (barWidth > width) barWidth = width;
				superiorBar->setWidth(barWidth);
			}
			//superiorBar->setPosition(tr->getPos()->x, tr->getPos()->y);
			//inferiorBar->setPosition(tr->getPos()->x, tr->getPos()->y);
			button->setPosition(buttonTr->getPos()->x, buttonTr->getPos()->y);

		}

		void Slider::setVisibility(bool mode)
		{
			/*if (mode) overlay->show();
			else overlay->hide();*/
		}

		void Slider::onSceneDown()
		{
			/*ogremanager->disableOverlay(overlay);*/
			//visible = false;
		}
		void Slider::onSceneUp()
		{
			//visible = true;
		}



		Slider::~Slider()
		{

		}
	}
}