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
			~Collider();

			// Callbacks de colision
			virtual void onCollisionEnter(LoveEngine::ECS::GameObject* other) {};
			virtual void onCollisionExit(ECS::GameObject* other) {};
			virtual void onCollisionStay(ECS::GameObject* other) {};

			void setGO(LoveEngine::ECS::GameObject* ent);
			ECS::GameObject* getGO();
		protected:
			LoveEngine::ECS::GameObject* collGO = nullptr;
		};
	}
}

