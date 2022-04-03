#include "Transform.h"
#include <Vector3.h>
#include <Vector4.h>
#include <string>
#include <iostream>
#include <StringFormater.h>

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

		void Transform::setRot(Utilities::Vector4<float> r) {
			rotation->x = r.x;
			rotation->y = r.y;
			rotation->z = r.z;
			rotation->w = r.w;
			updateChildren(1);
		}

		void Transform::setPos(Utilities::Vector3<float> p) {
			position->x = p.x;
			position->y = p.y;
			position->z = p.z;
			updateChildren(0);
		}

		void Transform::setScale(Utilities::Vector3<float> s) {
			scale->x = s.x;
			scale->y = s.y;
			scale->z = s.z;
			updateChildren(2);
		}

		void Transform::setScale(Utilities::Vector3<float> s, Utilities::Vector3<float> s2)
		{
			scale->x *= s.x * s2.x;
			scale->y *= s.y * s2.y;
			scale->z *= s.z * s2.z;
			updateChildren(2);
		}

		void Transform::translate(Utilities::Vector3<float> p) {
			position->x += p.x;
			position->x += p.y;
			position->z += p.z;
			updateChildren(0);
		}

		void Transform::rotate(Utilities::Vector4<float> r) {
			rotation->x += r.x;
			rotation->y += r.y;
			rotation->z += r.z;
			rotation->w += r.w;
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
				case 0: c->translate(*position); break;
				case 1: c->rotate(*rotation); break;
				case 2: c->setScale(*scale, *c->scale); break;
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

		void Transform::update()
		{
			//std::cout  << "\n";
		}

		void Transform::receiveMessage(std::string s)
		{
			StringFormatter sTf(s);
			Utilities::Vector3<float> v = sTf.getVector3("scale");
			scale->x = v.x;
			scale->y = v.y;
			scale->z = v.z;
			Utilities::Vector3<float> v1 = sTf.getVector3("position");
			position->x = v1.x;
			position->y = v1.y;
			position->z = v1.z;
			Utilities::Vector4<float> v2 = sTf.getVector4("rotation");
			rotation->x = v2.x;
			rotation->y = v2.y;
			rotation->z = v2.z;
			rotation->w = v2.w;
		}
	}
}