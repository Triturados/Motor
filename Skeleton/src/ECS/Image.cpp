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
namespace LoveEngine {
	namespace ECS {

		void Image::receiveValues(int i, float f, Component* eT, GameObject* g)
		{

			/*tr = static_cast<Transform*>(eT);*/
		}
		void Image::receiveMessage(std::string s)
		{
			StringFormatter sTf(s);
			material = sTf.getString("material");

			sTf.tryGetInt("width" , width );
			sTf.tryGetInt("height", height);
		}
		void Image::init() {
			ogremanager = Renderer::OgreRenderer::getInstance();

			/*if (texName == "") throw new std::exception("La textura no tiene nombre");
			texture = ogremanager->createSDLTexture(texName.c_str(), width, height);*/
			
			/*tr = gameObject->getComponent<Transform>();
			if(!tr) throw new std::exception("Se necesita transform para usar el componente Image");*/

			/*tr->setPos({ 300,300,0 });*/
			overlay = ogremanager->renderImage(0,0,width,height,material);
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
			visible = mode;
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