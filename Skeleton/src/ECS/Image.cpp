#include "Image.h"
#include "Transform.h"
#include <stdexcept>
#include <OgreRenderer.h>
#include <GameObject.h>

#include <Vector2.H>
#include <Ogre.h>
#include <string>
#include <iostream>
#include <StringFormatter.h>
#include <Vector3.h>
#include <Vector2.h>

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

		Image::Image()
		{
			visible = true;
			opacity = 1;
			overlay = nullptr;
			container = nullptr;
			ogremanager = nullptr;
		}
		void Image::receiveMessage(Utilities::StringFormatter& sf)
		{
			UIElement::receiveMessage(sf);
			material = sf.getString("material");
		}

		void Image::init() {
			ogremanager = Renderer::OgreRenderer::getInstance();

			if (material == "") throw new std::exception("El material no tiene nombre");

			container = ogremanager->renderImage(position, dimensions, material, overlay);
		}

		//No se llama el update 
		void Image::update()
		{
			/* render background, whereas NULL for source and destination
				rectangles just means "use the default" */
			if (!visible) return;

		}

		void Image::setVisibility(bool mode)
		{
			if (mode) overlay->show();
			else overlay->hide();
		}

		void Image::onMove()
		{
			container->setPosition(position.x, position.y);
			overlay->setZOrder(position.z);
		}

		void Image::onResize()
		{
			container->setWidth(dimensions.x);
			container->setHeight(dimensions.y);
		}

		float Image::getOpacity()
		{
			return opacity;
		}

		void Image::setOpacity(float fade)
		{
			opacity = fade;
			ogremanager->setImageOpacity(container, fade);
		}

		void Image::onSceneDown()
		{
			visible = false;
			setVisibility(visible);
		}

		void Image::onSceneUp()
		{
			visible = true;
			setVisibility(visible);
		}

		Image::~Image()
		{
			ogremanager->disableOverlay(overlay);
			ogremanager->disableContainer(container);
		}
	}
}