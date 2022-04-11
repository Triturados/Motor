#include "Text.h"
#include <OgreOverlayElement.h>
#include <OgreOverlay.h>
#include <OgreOverlayContainer.h>
#include <OgreRenderer.h>
#include <OgreTextAreaOverlayElement.h>
#include <Vector3.h>

namespace LoveEngine
{
	namespace ECS {


		void Text::receiveMessage(Utilities::StringFormatter& s)
		{
			
		}
		void Text::init()
		{
			ogremanager = Renderer::OgreRenderer::getInstance();
			textArea = ogremanager->createOverlayElement("text1");

		}

	}


}
