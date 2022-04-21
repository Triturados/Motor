#pragma once
#include <../Export.h>

#ifndef SKYBOX_H
#define SKYBOX_H

#include <Component.h>
#include <string>

namespace LoveEngine {
	namespace Renderer {
		class OgreRenderer;
	}

	namespace ECS {

		class lovexport Skybox : public Component
		{
		private:
			std::string materialName = "";
			int distance;
			Renderer::OgreRenderer* ogremanager;
		public:
			void receiveMessage(Utilities::StringFormatter& sf) override;

			void init() override;

			~Skybox() {};
		};
	}
}
#endif
