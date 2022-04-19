#include "Text.h"
#include <OgreOverlayElement.h>
#include <OgreOverlay.h>
#include <OgreOverlayContainer.h>
#include <OgreRenderer.h>
#include <OgreTextAreaOverlayElement.h>
#include <Vector3.h>
#include <Vector2.h>
#include <StringFormatter.h>
#include <GameObject.h>
#include "Transform.h"

namespace LoveEngine
{
	namespace ECS {


		void Text::receiveMessage(Utilities::StringFormatter& sf)
		{

			pos = new Utilities::Vector3(0, 0, 0);
			dimensions = new Utilities::Vector2(0, 0);
			int alineacion;

			sf.tryGetString("typeName", textName);
			sf.tryGetString("textContent", textContent);
			sf.tryGetFloat("red", color.r);
			sf.tryGetFloat("green", color.g);
			sf.tryGetFloat("blue", color.b);
			sf.tryGetFloat("alpha", color.a);
			sf.tryGetInt("width", dimensions->x);
			sf.tryGetInt("height", dimensions->y);
			sf.tryGetFloat("charHeight", charHeight);
			sf.tryGetInt("alignment", alineacion);

			alignment = (alignmentEnum)alineacion;
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

			textArea = ogremanager->createOverlayElement(textName);
			setPos(*pos);
			setText(textContent);
			setCol(color.r, color.g, color.b, color.a);
		}

		void Text::setPos(Utilities::Vector3<int> pos_)
		{
			pos->x = pos_.x; pos->y = pos_.y; pos->z = pos_.z;
			ogremanager->setTextPos(*pos, textArea);
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
			ogremanager->setText(textContent, *dimensions, textArea, charHeight, (int) alignment);
		}

	}


}
