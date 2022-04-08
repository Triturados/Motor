#include "Image.h"
#include "Transform.h"
#include <stdexcept>
#include <OgreRenderer.h>
#include <GameObject.h>

#include <Vector2.H>
#include <Ogre.h>
#include <string>
#include <iostream>
#include <StringFormater.h>

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

		
		void Image::receiveMessage(std::string s)
		{
			StringFormatter sTf(s);
			material = sTf.getString("material");

			sTf.tryGetInt("width" , width );
			sTf.tryGetInt("height", height);
		}
		void Image::init() {
			ogremanager = Renderer::OgreRenderer::getInstance();

			if (material == "") throw new std::exception("El material no tiene nombre");
			
			tr = gameObject->getComponent<Transform>();
			if(!tr) throw new std::exception("Se necesita transform para usar el componente Image");

			/*tr->setPos({ 300,300,0 });*/
			container = ogremanager->renderImage(0,0,width,height,material, overlay);

			/*setPos(300, 300);*/
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

		void Image::setPos(int x, int y)
		{
			tr->setPos(Utilities::Vector3((float)x,(float)y,0.0f));
			container->setPosition(tr->getPos()->x, tr->getPos()->y);
		}

		void Image::onSceneDown()
		{
			ogremanager->disableOverlay(overlay);
			//visible = false;
		}
		void Image::onSceneUp()
		{
			//visible = true;
		}



		Image::~Image()
		{

		}
	}
}