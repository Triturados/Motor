#pragma once

#include "Component.h"
#include <../Export.h>
#include <string>


class btRigidBody;

namespace LoveEngine {
	namespace Physics {
		class Collider;
	}
	namespace ECS {
		enum class ForceMode {
			FORCE, //dura un segundo la fuerza 
			IMPULSE, //impulso intantaneo en un frame
			ACCELERATION
		};

		enum class RBState {
			Kinematic = 0,
			Static = 1,
			Dynamic = 2,
			NONE = 3
		};

		enum class TipoForma {
			Cube = 0,
			Sphere = 1,
			Plane = 2,
			Capsule = 3
		};

		class Transform;

		class lovexport RigidBody : public Component
		{
		private:
			float mass;
			float restitution = 0;
			bool trigger;
			TipoForma shape;
			btRigidBody* rigidBody = nullptr;
			Transform* tr = nullptr;

			Utilities::Vector3<float>* colliderScale;

			RBState stateMode = RBState::NONE;
			bool collidesWithGameObject(RigidBody* go) const;

			LoveEngine::Physics::Collider* col = nullptr;

		public:
			RigidBody();

			~RigidBody();

			void init() override;

			void stepPhysics() override;

			void receiveMessage(Utilities::StringFormatter& s) override;

			void addForce(Utilities::Vector3<float> vel, Utilities::Vector3<float> relativePos, ForceMode mode);

			//Setters
			void setTransform(Transform* t_);

			void setMass(float mass_);

			void setShape(std::string nameF_);

			void setLinearVelocity(Utilities::Vector3<float> vel);

			void setAngularVelocity(Utilities::Vector3<float> vel);

			void setTrigger(bool trigger_);

			void setKinematic(bool kin_);

			void setStatic(bool static_);

			void setDynamic(bool dinamic_);

			void setRBGravity(Utilities::Vector3<float> newRBGrav);

			void setRestitution(float resti);

			void setFriccion(float friction);

			void setLinearFactor(Utilities::Vector3<float> vect);

			void setAngularFactor(Utilities::Vector3<float> vect);

			void setRotation(Utilities::Vector3<int> axis, float angle);

			void setDamping(float r, float s);

			//Getters
			inline float getMass() const noexcept { return mass; };
			Utilities::Vector3<float>* getVelocity() const noexcept;
			Utilities::Vector4<float>* getRotation() const noexcept;
			//inline btCollisionShape* getShape() const noexcept;
			Utilities::Vector3<float>* getGravity() const;

			//Collisiones
			bool onCollisionEnter(RigidBody* other);
		};
	};

}