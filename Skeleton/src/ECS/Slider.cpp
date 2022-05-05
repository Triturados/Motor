#include "Slider.h"
#include "Transform.h"
#include <stdexcept>
#include <OgreRenderer.h>
#include <Input.h>
#include <GameObject.h>

#include <Vector2.h>
#include <Vector3.h>
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

			pos = new Utilities::Vector3(0, 0, 1);
			buttonPos = new Utilities::Vector3(0, 0, 1);
			dimensions = new Utilities::Vector2(0, 0);
			buttonDimensions = new Utilities::Vector2(0, 0);

			sf.tryGetInt("width", dimensions->x);
			sf.tryGetInt("height", dimensions->y);
			sf.tryGetInt("posX", pos->x);
			sf.tryGetInt("posY", pos->y);
			sf.tryGetInt("posZ", pos->z);
		}

		void Slider::init() {
			ogremanager = Renderer::OgreRenderer::getInstance();
			inputmanager = Input::InputManager::getInstance();

			if (materialBar == "") throw new std::exception("El material no tiene nombre");
			if (materialButton == "") throw new std::exception("El material no tiene nombre");

			// Containers con cada elemento
			inferiorBar = ogremanager->createContainer(*pos,* dimensions);
			inferiorBar->setMaterialName(materialBarBg);
			superiorBar = ogremanager->createContainer((*pos) + Utilities::Vector3<int>(0, 0, 1), *dimensions);
			superiorBar->setMaterialName(materialBar);
			buttonPos->x = pos->x + dimensions->x - buttonWidth / 2;
			buttonPos->y = pos->y + dimensions->y / 2 - buttonWidth / 2;
			buttonPos->z = pos->z;
			buttonDimensions->x = buttonDimensions->y = buttonWidth;
			button = ogremanager->createContainer(*buttonPos, *buttonDimensions);
			button->setMaterialName(materialButton);

			// El overlay, que gestiona la poscion, rotacion...
			overlayBar = ogremanager->createOverlay();
			overlayBar->add2D(inferiorBar);
			overlayBar->add2D(superiorBar);
			overlayBar->add2D(button);

			// Mostrar el overlay
			overlayBar->show();
			//setDetectInput(false);
		}

		//No se llama el update 
		void Slider::update()
		{
			if (detectInput) handleInput();
		}

		void Slider::setVisibility(bool mode)
		{
			if (mode) overlayBar->show();
			else overlayBar->hide();
		}

		void Slider::setVisibilityBg(bool mode)
		{
			if (mode) inferiorBar->show();
			else inferiorBar->hide();
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

		inline int Slider::getMaxBarWidth()
		{
			return dimensions->x;
		}

		void Slider::setProgress(int progress)
		{
			if (progress < 0) progress = 0;
			if (progress > MAX_VALUE) progress = MAX_VALUE;
			barProgress = progress;

			barWidth = barProgress * dimensions->x / MAX_VALUE;
			button->setPosition((float)pos->x + barWidth - buttonWidth / 2, (float)pos->y + dimensions->y / 2 - buttonWidth / 2);
			superiorBar->setWidth(barWidth);
		}

		void Slider::handleInput()
		{
			Utilities::Vector2<int> mousePos = inputmanager->mousePosition();
			if (inputmanager->mousePressed(Input::MouseState::CLICK_L)) {
				if (mousePos.x >= buttonPos->x &&
					mousePos.x <= buttonPos->x + dimensions->x &&
					mousePos.y >= buttonPos->y &&
					mousePos.y <= buttonPos->y + dimensions->y
					) {
					tracking = true;
				}
			}
			else tracking = false;

			if (tracking) {
				//std::cout << "SLIDER SLIDEA progreso:  ";
				float newXpos = mousePos.x;
				if (newXpos < pos->x) newXpos = pos->x;
				if (newXpos > pos->x + dimensions->x - buttonWidth / 2) newXpos = pos->x + dimensions->x - buttonWidth / 2;
				button->setPosition(newXpos, pos->y);
				barWidth = mousePos.x - pos->x;
				if (barWidth < 0) barWidth = 0;
				if (barWidth > dimensions->x) barWidth = dimensions->x;
				superiorBar->setWidth(barWidth);

				barProgress = barWidth * MAX_VALUE / dimensions->x;
				//std::cout << barProgress << std::endl;
			}
		}
		void Slider::setDetectInput(bool mode)
		{
			detectInput = mode;
			if (mode) button->show();
			else button->hide();
		}
		void Slider::setPos(Utilities::Vector3<int> pos_)
		{
			pos->x = pos_.x; pos->y = pos_.y; pos->z = pos_.z;
			superiorBar->setPosition(pos_.x, pos_.y);
			inferiorBar->setPosition(pos_.x, pos_.y);
			float buttonNewPos = barProgress * dimensions->x / MAX_VALUE;
			buttonPos->x = pos->x + buttonNewPos - buttonWidth / 2;
			buttonPos->y = pos->y + dimensions->y / 2 - buttonDimensions->x / 2;
			buttonPos->z = pos->z;
			button->setPosition(buttonPos->x, buttonPos->y);

			overlayBar->setZOrder(pos->z);
		}

		void Slider::setDimensions(Utilities::Vector2<int> dimensions_)
		{
			dimensions->x = dimensions_.x; dimensions->y = dimensions_.y;
			superiorBar->setWidth(dimensions_.x);
			superiorBar->setHeight(dimensions_.y);
			inferiorBar->setWidth(dimensions_.x);
			inferiorBar->setHeight(dimensions_.y);
			buttonPos->x = (float)pos->x + dimensions->x - buttonWidth / 2;
			buttonPos->y = (float)pos->y + dimensions->y / 2 - buttonDimensions->x / 2;
			buttonPos->z = pos->z;
			button->setPosition(buttonPos->x, buttonPos->y);
		}
	}
}