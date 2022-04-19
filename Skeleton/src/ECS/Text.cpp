#include "Text.h"
#include <OgreOverlayElement.h>
#include <OgreOverlay.h>
#include <OgreOverlayContainer.h>
#include <OgreRenderer.h>
#include <OgreTextAreaOverlayElement.h>
#include <Vector3.h>
#include <StringFormatter.h>
#include <GameObject.h>
#include "Transform.h"

namespace LoveEngine
{
	namespace ECS {

		
		void Text::receiveMessage(Utilities::StringFormatter& sf)
		{

			sf.tryGetString("typeName", textName);
			sf.tryGetString("textContent", textContent);
			sf.tryGetFloat("red", color.r);
			sf.tryGetFloat("green", color.g);
			sf.tryGetFloat("blue", color.b);
			sf.tryGetFloat("isis", color.a);
			sf.tryGetInt("width", width);
			sf.tryGetInt("height", height);
			sf.tryGetFloat("charHeight", charHeight);
		}
		void Text::onSceneUp()
		{
			setVisibility(true);
		}
		void Text::onSceneDown()
		{
			setVisibility(false);
		}
		void Text::setVisibility(bool mode)
		{
			if (mode)textArea->show();
			else textArea->hide();
		}
		Text::~Text()
		{
			ogremanager->destroyText(textName);
		}
		void Text::init()
		{
			ogremanager = Renderer::OgreRenderer::getInstance();
			tr = gameObject->getComponent<Transform>();
			if (!tr) throw new std::exception("Se necesita transform para usar el componente Text");

			textArea = ogremanager->createOverlayElement(textName);
			ogremanager->setTextPos(tr->getPos()->x, tr->getPos()->y, textArea);
			ogremanager->setText(textContent, width, height, textArea, charHeight);
			ogremanager->setTextColor(color.r, color.g, color.b, color.a, textArea);
		}

		void Text::setPos(float xs, float ys)
		{
			tr->setPos(Utilities::Vector3(xs, ys, 0.0f));
			ogremanager->setTextPos(tr->getPos()->x, tr->getPos()->y, textArea);
		}

		void Text::setCol(float R, float G, float B, float I)
		{
			color.r = R;
			color.g = G;
			color.b = B;
			color.a = I;
			ogremanager->setTextColor(color.r, color.g, color.b, color.a, textArea);
		}

		void Text::setText(std::string szString)
		{
			textContent = szString;
			ogremanager->setText(textContent, width, height, textArea, charHeight);
		}

	}


}
