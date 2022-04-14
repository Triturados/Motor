#include "Collider.h"
namespace LoveEngine {
	namespace Physics {
		Collider::Collider()
		{
			collGO = nullptr;
		}

		Collider::~Collider()
		{
			delete collGO;
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
