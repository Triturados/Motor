#pragma once
#include <../Export.h>

#ifndef MATERIAL_H
#define MATERIAL_H

#include <Component.h>
#include <string>

namespace LoveEngine {
	namespace Renderer {
		class OgreRenderer;
	}

	namespace ECS {
		//class ParticleSystem;
		class Mesh;

		class lovexport Material : public Component
		{
		private:
			std::string materialName = "";
			//ParticleSystem* pSys = nullptr;
			Mesh* mesh = nullptr;

		public:
			void receiveMessage(Utilities::StringFormatter& sf) override;
			void receiveComponent(int i, Component* c) override;

			void init() override;
			void setMaterial();

			~Material() {};
		};
	}
}
#endif
