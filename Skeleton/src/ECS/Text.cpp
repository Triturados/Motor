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
			mainColor = new Utilities::Vector4<float>();
			bottomColor = new Utilities::Vector4<float>(0,0,0,-1);
			topColor = new Utilities::Vector4<float>(0,0,0,-1);

			int alineacion;

			sf.tryGetVector3("position", *(pos));
			sf.tryGetString("fontName", fontName);
			sf.tryGetVector4("mainColor", *(mainColor));
			sf.tryGetVector4("bottomColor", *(bottomColor));
			sf.tryGetVector4("topColor", *(topColor));
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

			configText();
		}

		void Text::configText()
		{
			//Posicion
			auto relative = pixelToRelative(pos->x, pos->y);
			pos->x = relative.x; pos->y = relative.y;

			textArea->setPosition(pos->x, pos->y);
			ogremanager->setTextOverlayZOrder(pos->z);

			//Color
			textArea->setColour(Ogre::ColourValue(mainColor->x, mainColor->y, mainColor->z, mainColor->w));
			if (bottomColor->w != -1) textArea->setColourBottom(Ogre::ColourValue(bottomColor->x, bottomColor->y, bottomColor->z, bottomColor->w));
			if (topColor->w != -1) textArea->setColourTop(Ogre::ColourValue(topColor->x, topColor->y, topColor->z, topColor->w));

			//Texto
			textArea->setCaption(textContent);
			textArea->setMetricsMode(Ogre::GMM_RELATIVE);
			textArea->setFontName(fontName);
			textArea->setCharHeight(textScale);
			textArea->setAlignment((Ogre::TextAreaOverlayElement::Alignment)alignment);
		}

		void Text::changeText(std::string mssg)
		{
			textContent = mssg;
			textArea->setCaption(textContent);
		}

		const Utilities::Vector2<float>& Text::pixelToRelative(float x, float y)
		{
			Utilities::Vector2<float> windowSize = ogremanager->getWindowSize();

			return Utilities::Vector2<float>(x / windowSize.x, y / windowSize.y);
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
