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

			// Containers con cada elemento
			inferiorBar = ogremanager->createContainer(posX, posY, width, height);
			inferiorBar->setMaterialName(materialBarBg);
			superiorBar = ogremanager->createContainer(posX, posY, width, height);
			superiorBar->setMaterialName(materialBar);
			button = ogremanager->createContainer(posX + width - buttonWidth/2, posY + height/2 - buttonWidth/2, buttonWidth, buttonWidth);
			button->setMaterialName(materialButton);

			// El overlay, que gestiona la poscion, rotacion...
			overlayBar = ogremanager->createOverlay();
			overlayBar->add2D(inferiorBar);
			overlayBar->add2D(superiorBar);
			overlayBar->add2D(button);

			// Mostrar el overlay
			overlayBar->show();
			buttonTr->setPos({ (float)posX + width - buttonWidth / 2,(float)posY + height / 2 - buttonWidth / 2, (float)0 });

			//setDetectInput(false);
		}

		//No se llama el update 
		void Slider::update()
		{
			if (detectInput) handleInput();
			
			button->setPosition(buttonTr->getPos()->x, buttonTr->getPos()->y);
		}

		void Slider::setVisibility(bool mode)
		{
			if (mode) overlayBar->show();
			else overlayBar->hide();
		}

		void Slider::onSceneDown()
		{
			overlayBar->hide();
		}
		void Slider::onSceneUp()
		{
			overlayBar->show();
		}



		Slider::~Slider()
		{
			ogremanager->disableOverlay(overlayBar);
		}

		void Slider::setProgress(int progress)
		{
			if (progress < 0 || progress > MAX_VALUE) throw new std::exception("setProgress(), parametro de salud invalido");;
			barProgress = progress;

			barWidth = barProgress * width / MAX_VALUE;
			buttonTr->setPos({ (float) posX + barWidth - buttonWidth / 2, (float)posY + height / 2 - buttonWidth / 2,0.0f });
			superiorBar->setWidth(barWidth);
		}

		void Slider::handleInput()
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
				//std::cout << "SLIDER SLIDEA progreso:  ";
				float newXpos = mousePos.x;
				if (newXpos < posX) newXpos = posX;
				if (newXpos > posX + width - buttonWidth / 2) newXpos = posX + width - buttonWidth / 2;
				buttonTr->setPos({ newXpos,buttonTr->getPos()->y,0.0f });
				barWidth = mousePos.x - posX;
				if (barWidth < 0) barWidth = 0;
				if (barWidth > width) barWidth = width;
				superiorBar->setWidth(barWidth);

				barProgress = barWidth * MAX_VALUE / width;
				//std::cout << barProgress << std::endl;
			}
		}
		void Slider::setDetectInput(bool mode)
		{
			detectInput = mode;
			if (mode) button->show();
			else button->hide();
		}
		void Slider::setPos(int x, int y)
		{
			posX = x; posY = y;
			superiorBar->setPosition(x, y);
			inferiorBar->setPosition(x, y);
			float buttonNewPos = barProgress * width / MAX_VALUE;
			buttonTr->setPos({ posX + buttonNewPos - buttonWidth/2, (float)posY + height / 2 - buttonWidth / 2,0.0f });
		}
		void Slider::setDimensions(int w, int h)
		{
			width = w; height = h;
			superiorBar->setWidth(w);
			superiorBar->setHeight(h);
			inferiorBar->setWidth(w);
			inferiorBar->setHeight(h);
			buttonTr->setPos({ (float)posX + w - buttonWidth / 2, (float)posY + h / 2 - buttonWidth / 2,0.0f });
		}
	}
}