#include "Button.h"
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

		void Button::receiveMessage(Utilities::StringFormatter& sf)
		{
			material = sf.getString("material");

			pos = new Utilities::Vector3(0, 0, 1);
			dimensions = new Utilities::Vector2(0, 0);

			sf.tryGetInt("width", dimensions->x);
			sf.tryGetInt("height", dimensions->y);
			sf.tryGetInt("posX", pos->x);
			sf.tryGetInt("posY", pos->y);
			sf.tryGetInt("posZ", pos->z);
		}

		void Button::init() {
			ogremanager = Renderer::OgreRenderer::getInstance();
			inputmanager = Input::InputManager::getInstance();

			if (material == "") throw new std::exception("El material no tiene nombre");

			button = ogremanager->createContainer(*pos, *dimensions);
			button->setMaterialName(material);

			// El overlay, que gestiona la poscion, rotacion...
			overlayBar = ogremanager->createOverlay();
			overlayBar->add2D(button);
			overlayBar->setZOrder(pos->z);

			// Mostrar el overlay
			overlayBar->show();

		}

		//No se llama el update 
		void Button::update()
		{
			if (detectInput) handleInput();
		}

		void Button::setVisibility(bool mode)
		{
			if (mode) overlayBar->show();
			else overlayBar->hide();
		}

		void Button::onSceneDown()
		{
			overlayBar->hide();
		}
		void Button::onSceneUp()
		{
			overlayBar->show();
		}



		Button::~Button()
		{
			ogremanager->disableOverlay(overlayBar);
			delete pos;
			delete dimensions;
		}

		Button::Button()
		{
			lambda = []() {};
		}

		void Button::handleInput()
		{
			if (inputmanager->justClicked()) {
				Utilities::Vector2<float> mousePos = inputmanager->mousePosition();
				if (mousePos.x >= pos->x && mousePos.x <= pos->x + dimensions->x && mousePos.y >= pos->y && mousePos.y <= pos->y + dimensions->y) {
					lambda();
				}
			}
		}

		void Button::setDetectInput(bool mode)
		{
			detectInput = mode;
			if (mode) button->show();
			else button->hide();
		}

		void Button::setPos(Utilities::Vector3<int> pos_)
		{
			button->setPosition(pos_.x, pos_.y);
			overlayBar->setZOrder(pos_.z);
			pos->x = pos_.x; pos->y = pos_.y; pos->z = pos_.z;
		}

		Utilities::Vector3<int> Button::getPos()
		{
			return *pos;
		}

		Utilities::Vector2<int> Button::getSize()
		{
			return *dimensions;
		}

		void Button::setSize(Utilities::Vector2<int> newsize)
		{
			*dimensions = newsize;
			button->setWidth(newsize.x);
			button->setHeight(newsize.y);
		}

		void Button::onClick(std::function<void()> l)
		{
			lambda = l;
		}
	}
}