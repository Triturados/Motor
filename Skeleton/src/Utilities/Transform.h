#pragma once

#include <vector>
#include <Component.h>

namespace Utilities {
	template<typename T>
	class Vector3;
	template<typename T>
	class Vector4;
}

class Transform :  public Component
{
private:
	Utilities::Vector3<float>* position;
	Utilities::Vector4<float>* rotation;
	Utilities::Vector3<float>*  scale;
public:
	
	Transform();
	~Transform();
	Utilities::Vector3<float>*getPos();
	Utilities::Vector4<float>*getRot();
	Utilities::Vector3<float>*getScale();

	void setRot(Utilities::Vector4<float>* r);
	void setPos(Utilities::Vector3<float>* p);
	void setScale(Utilities::Vector3<float>* s);
};

