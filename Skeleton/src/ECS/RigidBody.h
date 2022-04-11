#pragma once

#include "Component.h"
#include <../Export.h>
#include <string>


class btRigidBody;

namespace LoveEngine {
	
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

		enum class TipoForma {
			Cube = 0,
			Sphere = 1,
			Plane = 2,
			Cylinder = 3,
			Cone = 4
		};

		class Transform;

		class lovexport RigidBody : public Component
		{
		private:
			float mass;
			float restitution;
			TipoForma shape;
			btRigidBody* rigidBody = nullptr;
			Transform* tr = nullptr;

			Utilities::Vector3<float>* lastForce;
			Utilities::Vector3<float>* acc;

			RBState stateMode;

		public:
			RigidBody();

			~RigidBody();

			void init() override;

			void update() override;

			void stepPhysics() override;

			void receiveMessage(Utilities::StringFormatter& s) override;

			void addForce(Utilities::Vector3<float> vel, Utilities::Vector3<float> relativePos, int type);

			void setTransform(Transform* t_);

			void setMass(float mass_);

			void setShape(std::string nameF_);

			void setLinearVelocity(Utilities::Vector3<float> vel);
		};
	};

}