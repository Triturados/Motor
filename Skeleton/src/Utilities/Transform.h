#pragma once

#include <vector>
#include <Component.h>

class Quaternion;
class SceneNode;
class Vector3;

namespace Utilities {
	template<typename T>
	class Vector3;
	template<typename T>
	class Vector4;
}

class Transform :  public Component
{
	Vector3* position = nullptr;
	Quaternion* rotation = nullptr;
	Vector3* scale = nullptr;

	SceneNode* entityNode;
	std::vector<Transform*> children;
	Transform* parent;

public:
	Transform(Transform* p=nullptr);
	~Transform();
	Utilities::Vector3<float>getPos();
	Utilities::Vector4<float> getRot();
	Utilities::Vector3<float> getScale();

	void setRot(Utilities::Vector4<float> r);
	void setPos(Utilities::Vector3<float> p);
	void setScale(Utilities::Vector3<float> s);
	Utilities::Vector3<float>transformOgreVector(Vector3* v);
	Utilities::Vector4<float>transformOgreQuaternion(Quaternion* v);
	Quaternion* transformIntoOgreQuaternion(Utilities::Vector4<float> v);
	Vector3* transformIntoOgreVector(Utilities::Vector3<float> v);

};

