#include "Transform.h"
#include <Vector3.h>
#include <Vector4.h>
#include <string>

namespace LoveEngine {
	namespace ECS {

		Transform::Transform()
		{
			position = new Utilities::Vector3<float>(0.0, 0.0, 0.0);
			scale = new Utilities::Vector3<float>(1.0, 1.0, 1.0);
			rotation = new Utilities::Vector4<float>(0.0, 0.0, 0.0, 0.0);
			parent = nullptr;
		}


		Utilities::Vector3<float>* Transform::getPos()
		{
			return position;
		}

		Utilities::Vector4<float>* Transform::getRot()
		{
			return rotation;
		}

		Utilities::Vector3<float>* Transform::getScale()
		{
			return scale;
		}

		void Transform::setRot(Utilities::Vector4<float>* r) {
			rotation = r;
			updateChildren(1);
		}

		void Transform::setPos(Utilities::Vector3<float>* p) {
			position = p;
			updateChildren(0);
		}

		void Transform::setScale(Utilities::Vector3<float>* s) {
			scale = s;
			updateChildren(2);
		}

		void Transform::setScale(Utilities::Vector3<float>* s, Utilities::Vector3<float>* s2)
		{
			*scale = *s * *s2;
			updateChildren(2);
		}

		void Transform::translate(Utilities::Vector3<float>* p) {
			*position += *p;
			updateChildren(0);
		}

		void Transform::rotate(Utilities::Vector4<float>* r) {
			*rotation += *r;
			updateChildren(1);
		}

		void Transform::detachChildren() {
			for (auto c : children) c->setParent(nullptr);
		}

		void Transform::setParent(Transform* p) {
			parent = p;
			parent->addChild(this);
		}

		void Transform::addChild(Transform* c) {
			children.push_back(c);
		}

		void Transform::updateChildren(int mode)
		{
			if (children.empty()) return;

			for (auto& c : children) {
				switch (mode)
				{
				case 0: c->translate(position); break;
				case 1: c->rotate(rotation); break;
				case 2: c->setScale(scale, c->scale); break;
				default:
					break;
				}
			}
		}

		Transform::~Transform()
		{
			delete position;
			delete rotation;
			delete scale;

			for (std::list<Transform*>::iterator it = children.begin();
				it != children.end(); it++) children.erase(it);
			children.clear();
		}
	}
}