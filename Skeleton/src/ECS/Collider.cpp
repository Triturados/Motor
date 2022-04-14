#include "Collider.h"

Collider::Collider()
{
	collGO = nullptr;
}

Collider::~Collider()
{
	delete collGO;
}

void Collider::setGO(GameObject* ent)
{
	collGO = ent;
}

GameObject* Collider::getGO()
{
	return collGO;
}
