#pragma once

#include "Component.h"
#include <../Export.h>


namespace Utilities {
	template <typename T>
	class Vector3;
}

enum class ForceMode {
	FORCE,
	ACCELERATION,
	IMPULSE,
	VELOCITY_CHANGE
};

enum RBState {
	Kinematic,
	Static,
	Dynamic
};

class btRigidBody;

namespace LoveEngine {

	namespace ECS {
		class Transform;

		class lovexport RigidBody : public Component
		{
		private:
			float mass;

			btRigidBody* rigidBody = nullptr;
			Transform* tr = nullptr;

			Utilities::Vector3<float>* lastForce;
			Utilities::Vector3<float>* acc;

			RBState stateMode;

		public:
			RigidBody();

			~RigidBody();

			void init();

			void update() override;

			void addForce(Utilities::Vector3<float>& vel, Utilities::Vector3<float>& relativePos, int type);

			void setTransform(Transform* t_);

			void setMass(float mass_);
		};
	}

}