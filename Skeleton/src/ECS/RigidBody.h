#pragma once

#include "Component.h"
#include <../Export.h>


class btRigidBody;

namespace LoveEngine {
	namespace Utilities {
		template <typename T>
		class Vector3;
	}
	namespace ECS {
		enum class ForceMode {
			FORCE,
			ACCELERATION,
			IMPULSE,
			VELOCITY_CHANGE
		};

		enum class RBState {
			Kinematic = 0,
			Static = 1,
			Dynamic = 2
		};

		class Transform;

		class lovexport RigidBody : public Component
		{
		private:
			float mass;
			int forma;
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

			void stepPhysics() override;

			void sendParameters(float mass_, Transform* eTm, int state_, int forma_);

			void addForce(Utilities::Vector3<float> vel, Utilities::Vector3<float> relativePos, int type);

			void setTransform(Transform* t_);

			void setMass(float mass_);
		};
	}

}