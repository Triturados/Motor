#pragma once

class GameObject;

class Collider
{
public:
	Collider();
	~Collider();
	void setGO(GameObject* ent);
	GameObject* getGO();
protected:
	GameObject* collGO = nullptr;
};

