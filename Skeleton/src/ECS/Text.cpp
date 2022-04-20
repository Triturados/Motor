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
			pos = new Utilities::Vector3<float>(0, 0, 0);
			int alineacion;

			sf.tryGetVector3("position", *(pos));
			sf.tryGetString("fontName", fontName);
			sf.tryGetFloat("red", color.r);
			sf.tryGetFloat("green", color.g);
			sf.tryGetFloat("blue", color.b);
			sf.tryGetFloat("alpha", color.a);
			sf.tryGetFloat("textScale", textScale);
			sf.tryGetInt("alignment", alineacion);

			alignment = (alignmentEnum) alineacion;
		}

		void Text::receiveString(std::string mssg)
		{
			textContent = mssg;
		}

		void Text::init()
		{
			ogremanager = Renderer::OgreRenderer::getInstance();

			textArea = ogremanager->createOverlayElement();

			setText();
			setPos();
			setCol();
		}

		void Text::setPos()
		{
			auto relative = pixelToRelative(pos->x, pos->y);
			pos->x = relative.x; pos->y = relative.y;

			textArea->setPosition(pos->x, pos->y);
			ogremanager->setTextOverlayZOrder(pos->z);
		}

		void Text::setCol()
		{
			textArea->setColour(Ogre::ColourValue(color.r, color.g, color.b, color.a));
		}

		const Utilities::Vector2<float>& Text::pixelToRelative(float x, float y)
		{
			Utilities::Vector2<float> windowSize = ogremanager->getWindowSize();

			return Utilities::Vector2<float>(x / windowSize.x, y / windowSize.y);
		}

		void Text::setText()
		{
			textArea->setCaption(textContent);
			textArea->setMetricsMode(Ogre::GMM_RELATIVE);
			textArea->setFontName(fontName);
			textArea->setCharHeight(textScale);
			textArea->setAlignment((Ogre::TextAreaOverlayElement::Alignment)alignment);
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
			if (mode) textArea->show();
			else textArea->hide();
		}

		Text::~Text()
		{
			delete pos;
		}
	}
}
