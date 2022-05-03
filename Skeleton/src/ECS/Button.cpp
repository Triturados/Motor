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
			UIElement::receiveMessage(sf);
			if (sf.tryGetString("material", material)) {
				hasMaterial = true;
			}
		}

		void Button::init() {
			inputmanager = Input::InputManager::getInstance();

			if (!hasMaterial) return;
			ogremanager = Renderer::OgreRenderer::getInstance();

			button = ogremanager->createContainer(position, dimensions);
			button->setMaterialName(material);

			// El overlay, que gestiona la poscion, rotacion...
			overlayBar = ogremanager->createOverlay();
			overlayBar->add2D(button);
			overlayBar->setZOrder(position.z);

			// Mostrar el overlay
			overlayBar->show();
		}

		//No se llama el update 
		void Button::update()
		{
			if (interactable) handleInput();
		}

		void Button::setVisibility(bool mode)
		{
			if (!hasMaterial) return;
			if (mode) overlayBar->show();
			else overlayBar->hide();
		}

		void Button::onSceneDown()
		{
			if (hasMaterial)
				overlayBar->hide();
		}
		void Button::onSceneUp()
		{
			if (hasMaterial)
				overlayBar->show();
		}

		Button::~Button()
		{
			if (hasMaterial)
				ogremanager->disableOverlay(overlayBar);
			hasMaterial = false;
		}

		Button::Button()
		{
			hasMaterial = false;
			interactable = true;
			hovering = false;

			ogremanager = nullptr;
			inputmanager = nullptr;
			overlayBar = nullptr;
			button = nullptr;
		}

		void Button::handleInput()
		{
			Utilities::Vector2<int> mousePos = inputmanager->mousePosition();
			if ((hovering = mousePos.x >= position.x && mousePos.x <= position.x + dimensions.x && mousePos.y >= position.y && mousePos.y <= position.y + dimensions.y)) {
				if (inputmanager->justClicked()) {
					for (auto l : lambda) l();
				}
			}
		}

		void Button::setInteractable(bool val) {
			interactable = val;
		}

		bool Button::isInteractable() {
			return interactable;
		}

		bool Button::isHovering() {
			return hovering;
		}

		void Button::onMove()
		{
			button->setPosition(position.x, position.y);
			overlayBar->setZOrder(position.z);
			position.x = position.x; position.y = position.y; position.z = position.z;
		}

		void Button::onResize()
		{
			button->setWidth(dimensions.x);
			button->setHeight(dimensions.y);
		}

		void Button::onClick(std::function<void()> l)
		{
			lambda.push_back(l);
		}
	}
}