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
#include "Window.h"
namespace LoveEngine
{
	namespace ECS {

		void Text::receiveMessage(Utilities::StringFormatter& sf)
		{
			UIElement::receiveMessage(sf);
			mainColor = Utilities::Vector4<float>();
			bottomColor = Utilities::Vector4<float>(0,0,0,-1);
			topColor = Utilities::Vector4<float>(0,0,0,-1);

			int alineacion;

			sf.tryGetString("fontName", fontName);
			sf.tryGetVector4("mainColor", mainColor);
			sf.tryGetVector4("bottomColor", bottomColor);
			sf.tryGetVector4("topColor", topColor);
			sf.tryGetFloat("textScale", textScale);
			sf.tryGetInt("alignment", alineacion);
			sf.tryGetString("text", textContent);
			alignment = (alignmentEnum) alineacion;
		}

		void Text::receiveString(const  std::string& mssg)
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
			setTextPosition(position);
			setTextColor(mainColor);
			setTextBottomColor(bottomColor);
			setTextBottomColor(topColor);
			setTextContent(textContent);
			setTextFont(fontName);
			setTextScale(textScale);
			setTextAligment(alignment);
		}

		void Text::setTextPosition(Utilities::Vector3<int>& position)
		{
			//Posicion
			auto relative = pixelToRelative(position.x, position.y);
			textArea->setPosition(relative.x, relative.y);
			ogremanager->setTextOverlayZOrder(position.z);
		}

		void Text::setTextColor(const Utilities::Vector4<float>& color)
		{
			//Color
			textArea->setColour(Ogre::ColourValue(color.x, color.y, color.z, color.w));
		}

		void Text::setTextBottomColor(const Utilities::Vector4<float>& color)
		{
			if(color.w != -1) textArea->setColourBottom(Ogre::ColourValue(color.x, color.y, color.z, color.w));
		}

		void Text::setTextTopColor(const Utilities::Vector4<float>& color)
		{
			if (color.w != -1) textArea->setColourTop(Ogre::ColourValue(color.x, color.y, color.z, color.w));
		}

		void Text::setTextContent(const std::string& content)
		{
			textArea->setCaption(textContent);
		}

		void Text::setTextFont(const std::string& font)
		{
			textArea->setFontName(font);
		}

		void Text::setTextScale(float scale)
		{
			textArea->setCharHeight(scale);
		}

		void Text::setTextAligment(alignmentEnum aling)
		{
			textArea->setAlignment((Ogre::TextAreaOverlayElement::Alignment)aling);
		}

		void Text::changeText(const  std::string& mssg)
		{
			textContent = mssg;
			textArea->setCaption(textContent);
		}

		void Text::onMove()
		{
			UIElement::onMove();
			setTextPosition(position);
		}

		Utilities::Vector2<float> Text::pixelToRelative(float x, float y)
		{
			Utilities::Vector2<int> windowSize = Window::getInstance()->getWindowSize();

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
		}
	}
}
