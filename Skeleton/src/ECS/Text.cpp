#include "Text.h"
#include <OgreOverlayElement.h>
#include <OgreOverlay.h>
#include <OgreOverlayContainer.h>
#include <OgreRenderer.h>

namespace LoveEngine
{
	namespace ECS {

		
		void Text::receiveMessage(Utilities::StringFormatter& s)
		{

		}
		void Text::init()
		{
			ogremanager = Renderer::OgreRenderer::getInstance();
			ogremanager->createOverlayElement("text1");
		}

	}


}
