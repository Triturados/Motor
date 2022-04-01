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

namespace Utilities {
	template<typename T>
	class Vector3;
	template<typename T>
	class Vector4;
}

namespace LoveEngine {
	namespace ECS {

		enum lightType { point, directional, spot };


		class Transform;
		class lovexport LightComponent : public Component
		{
		private:
			Ogre::SceneNode* entityNode;

			Transform* pos;

			Ogre::Light* light;

			bool visible;

			std::string name;
			lightType type;
		public:

			LightComponent();
			~LightComponent();

			void init();

			void sendParameters(lightType t, std::string n);
			void specularColor(float r, float g, float b);
			void diffuseColor(float r, float g, float b);
			void setDir(Utilities::Vector3<float> direction);
			void setRange(float startAngle, float endAngle, float desvanecimiento = 1.0);
			void setVisibility(bool active);
			void setPower(float power);

			Utilities::Vector3<float> getDiffuseColor();
			Utilities::Vector3<float> getSpecularColor();
			Utilities::Vector3<float> getDir();
			bool getVisibility();
		};

	}
}