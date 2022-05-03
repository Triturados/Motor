#pragma once

//#ifndef LIGHT_H
//#define LIGHT_H
#include <../Export.h>

#include <Component.h>


namespace Ogre {
	class SceneNode;
	class SceneManager;
	class Light;
}

namespace LoveEngine {

	namespace Renderer {
		class OgreRenderer;
	}
	namespace ECS {

		enum class lightType { point, directional, spot };


		class Transform;
		class lovexport Light : public Component
		{
		private:
			Ogre::SceneNode* entityNode;

			Renderer::OgreRenderer* ogremanager;

			Transform* tr;

			Ogre::Light* light;

			bool visible;

			std::string name;
			lightType type;

			//Parameters

			Utilities::Vector3<float>* diffuse;
			Utilities::Vector3<float>* specular;
			Utilities::Vector3<float>* direction;

			Utilities::Vector3<float>* rot;
			Utilities::Vector3<float>* pos;
			Utilities::Vector3<float>* scale;

			int lightPower = 10;

			float inRange;
			float outRange;
			float fallOff;
		public:

			~Light();
			Light();

			void init() override;

			void specularColor(float r, float g, float b);
			void diffuseColor(float r, float g, float b);
			void setDir(Utilities::Vector3<float> direction);
			void setRange(float startAngle, float endAngle, float desvanecimiento = 1.0);
			void setVisibility(bool active);
			void setPower(float power);
			void update() override;

			Utilities::Vector3<float> getDiffuseColor();
			Utilities::Vector3<float> getSpecularColor();
			void onSceneDown()override;
			void onSceneUp()override;
			bool getVisibility();


			void receiveMessage(Utilities::StringFormatter& message) override;
		};

	}
}