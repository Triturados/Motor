#include "Button.h"
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

		void Button::receiveMessage(Utilities::StringFormatter& sf)
		{
			material = sf.getString("material");

			sf.tryGetInt("width" , width);
			sf.tryGetInt("height", height);
			sf.tryGetInt("posX", posX);
			sf.tryGetInt("posY", posY);
		}

		void Button::init() {
			ogremanager = Renderer::OgreRenderer::getInstance();
			inputmanager = Input::InputManager::getInstance();

			if (material == "") throw new std::exception("El material no tiene nombre");

			button = ogremanager->createContainer(posX, posY, width, height);
			button->setMaterialName(material);

			// El overlay, que gestiona la poscion, rotacion...
			overlayBar = ogremanager->createOverlay();
			overlayBar->add2D(button);

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
		}

		void Button::handleInput()
		{
			Utilities::Vector2<float> mousePos = inputmanager->mousePosition();
			if (inputmanager->mousePressed(Input::MouseState::JUST_CLICK_L)) {
				if (mousePos.x >= posX && mousePos.x <= posX + width && mousePos.y >= posY && mousePos.y <= posY + height) {
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
		void Button::setPos(int x, int y)
		{
			posX = x; posY = y;
			button->setPosition(x, y);
		}
		void Button::setDimensions(int w, int h)
		{
			width = w; height = h;
			button->setWidth(w);
			button->setHeight(h);
		}
		void Button::onClick(std::function<void()> l)
		{
			lambda = l;
		}
	}
}