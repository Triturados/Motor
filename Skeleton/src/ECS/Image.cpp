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

		void Image::receiveMessage(Utilities::StringFormatter& sf)
		{
			material = sf.getString("material");

			pos = new Utilities::Vector3(0, 0, 0);
			dimensions = new Utilities::Vector2(0, 0);

			sf.tryGetInt("width", dimensions->x);
			sf.tryGetInt("height", dimensions->y);
			sf.tryGetInt("posX", pos->x);
			sf.tryGetInt("posY", pos->y);
			sf.tryGetInt("posZ", pos->z);
			
		}

		void Image::init() {
			ogremanager = Renderer::OgreRenderer::getInstance();

			if (material == "") throw new std::exception("El material no tiene nombre");

			container = ogremanager->renderImage(*pos, *dimensions, material, overlay);
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

		void Image::setPos(Utilities::Vector3<int> pos_)
		{
			container->setPosition(pos_.x, pos_.y);
			overlay->setZOrder(pos_.z);
			pos->x = pos_.x; pos->y = pos_.y; pos->z = pos_.z;
		}


		Utilities::Vector3<int> Image::getPos()
		{
			return *pos;
		}

		void Image::setDimensions(Utilities::Vector2<int> dimensions_)
		{
			container->setWidth(dimensions_.x);
			container->setHeight(dimensions_.y);
			dimensions->x = dimensions_.x; dimensions->y = dimensions_.y;
		}

		Utilities::Vector2<int> Image::getDimensions()
		{
			return *dimensions;
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
			delete pos;
			delete dimensions;
		}
	}
}