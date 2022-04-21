#pragma once
#include <../Export.h>
namespace LoveEngine {
	namespace ECS {
	class GameObject;
	}
	namespace Physics {
		class Collider
		{
		public:
			Collider();
			virtual ~Collider();

			// Callbacks de colision
			virtual void onCollisionEnter(ECS::GameObject* other);
			virtual void onCollisionExit(ECS::GameObject* other);
			virtual void onCollisionStay(ECS::GameObject* other);

			void setGO(ECS::GameObject* ent);
			ECS::GameObject* getGO();
		protected:
			LoveEngine::ECS::GameObject* collGO = nullptr;
		};
	}
}

