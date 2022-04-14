#pragma once
#include <../Export.h>

#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <list>
#include <string>
#include <Component.h>

namespace LoveEngine {

	namespace ECS {

		class lovexport Transform : public ComponentTemplate<Transform>
		{
		private:
			Utilities::Vector3<float>* position;
			Utilities::Vector4<float>* rotation;
			Utilities::Vector3<float>* scale;
			Utilities::Vector3<float>* localPosition;
			Utilities::Vector4<float>* localRotation;
			Utilities::Vector3<float>* localScale;

			Transform* parent;
			std::list<Transform*> children;

			void setScale(Utilities::Vector3<float> s, Utilities::Vector3<float> s2);

		public:

			Transform();
			~Transform();

			void update() override;
			void receiveMessage(Utilities::StringFormatter& s) override;
			void receiveComponent(int i, Component* c) override;

			Utilities::Vector3<float>* getPos();
			Utilities::Vector4<float>* getRot();
			Utilities::Vector3<float>* getScale();

			Utilities::Vector3<float> forward();

			void setRot(Utilities::Vector4<float> r);
			void setPos(Utilities::Vector3<float> p);
			void setLocalPos(Utilities::Vector3<float> lP);
			void setScale(Utilities::Vector3<float> s);
			void translate(Utilities::Vector3<float> p);
			void rotate(Utilities::Vector4<float> r);
			void detachChildren();

			void setParent(Transform* p);
			Transform* getParent();
			Transform* getFirstParent();
			void addChild(Transform* c);
			void updateChildren(int mode, Utilities::Vector3<float> p);

			void rotateChild(int angule, float ang, Utilities::Vector3<float> posP);
		};
	}
}
#endif