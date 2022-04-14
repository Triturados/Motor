#include "Collider.h"
#include "GameObject.h"
#include <iostream>
namespace LoveEngine {
	namespace Physics {
		Collider::Collider()
		{
			collGO = nullptr;
		}

		Collider::~Collider()
		{

			collGO = nullptr; //hacer delete
			//delete collGO; collGO = nullptr;
		}

		void Collider::onCollisionEnter(LoveEngine::ECS::GameObject* other)
		{
			std::cout << "Entro en collision" << std::endl;
			collGO->enterCollision(other);
		}

		void Collider::onCollisionExit(LoveEngine::ECS::GameObject* other)
		{
			std::cout << "Salgo de collision" << std::endl;
			collGO->exitCollision(other);
		}

		void Collider::onCollisionStay(LoveEngine::ECS::GameObject* other)
		{
			std::cout << "Estoy en collision" << std::endl;
			collGO->colliding(other);
		}

		void Collider::setGO(LoveEngine::ECS::GameObject* ent)
		{
			collGO = ent;
		}

		ECS::GameObject* Collider::getGO()
		{
			return collGO;
		}
	}
}
