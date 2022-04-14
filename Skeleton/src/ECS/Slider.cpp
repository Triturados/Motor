#include "Slider.h"
#include "Transform.h"
#include <stdexcept>
#include <OgreRenderer.h>
#include <GameObject.h>

#include <Vector2.H>
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
			materialButton = sf.getString("materialButton");

			sf.tryGetInt("width" , width );
			sf.tryGetInt("height", height);
			sf.tryGetInt("posX", posX);
			sf.tryGetInt("posY", posY);
		}
		void Slider::init() {
			ogremanager = Renderer::OgreRenderer::getInstance();

			if (materialBar == "") throw new std::exception("El material no tiene nombre");
			if (materialButton == "") throw new std::exception("El material no tiene nombre");
			
			tr = gameObject->getComponent<Transform>();
			if(!tr) throw new std::exception("Se necesita transform para usar el componente Image");


			Ogre::OverlayContainer* superiorBar = ogremanager->createContainer(posX, posY, width, height);
			container->setMaterialName(materialBar);
			Ogre::OverlayContainer* inferiorBar = ogremanager->createContainer(posX, posY, width, height);
			container->setMaterialName(materialBar);

			// El overlay, que gestiona la poscion, rotacion...
			overlay = ogremanager->createOverlay();
			overlay->add2D(superiorBar);
			overlay->add2D(inferiorBar);

			/*overlay->rotate(Ogre::Radian(Ogre::Angle(90)));*/

			// Mostrar el overlay
			overlay->show();
			return container;
		}

		//No se llama el update 
		void Slider::update()
		{
			container->setPosition(tr->getPos()->x, tr->getPos()->y);
		}

		void Slider::setVisibility(bool mode)
		{
			if (mode) overlay->show();
			else overlay->hide();
		}

		void Slider::onSceneDown()
		{
			ogremanager->disableOverlay(overlay);
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