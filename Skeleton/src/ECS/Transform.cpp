#include "Transform.h"
#include <Vector3.h>
#include <Vector4.h>
#include <string>
#include <iostream>
#include <StringFormatter.h>
#include <math.h>
#include <cmath>
#include <numbers>

namespace LoveEngine {
	namespace ECS {

		Transform::Transform()
		{
			position = new Utilities::Vector3<float>(0.0, 0.0, 0.0);
			localPosition = new Utilities::Vector3<float>(0.0, 0.0, 0.0);
			localRotation = new Utilities::Vector3<float>(0.0, 0.0, 0.0);
			scale = new Utilities::Vector3<float>(1.0, 1.0, 1.0);
			rotation = new Utilities::Vector3<float>(0.0, 0.0, 0.0);
			parent = nullptr;
		}

		Transform::~Transform()
		{
			delete position;
			delete rotation;
			delete scale;

			// Solo hay que quitar los hijos de la lista. Se destruir�n cuando se destruyan sus objetos
			while (!children.empty())
			{
				auto c = *(children.begin());
				c->setParent(nullptr);
				children.remove(c);
			}
			children.clear();

			if (parent != nullptr) parent->removeChild(this);
		}


		Utilities::Vector3<float>* Transform::getPos()
		{
			return position;
		}

		Utilities::Vector3<float>* Transform::getRot()
		{
			return rotation;
		}

		Utilities::Vector3<float>* Transform::getScale()
		{
			return scale;
		}

		Utilities::Vector3<float> Transform::forward()
		{
			Utilities::Vector3<float> f(0, 0, 1);

			f = f.rotateX(rotation->x);
			f = f.rotateY(rotation->y);
			f = f.rotateZ(rotation->z);

			f.normalize();

			return f;
		}
		Utilities::Vector3<float> Transform::right()
		{
			Utilities::Vector3<float> f(1, 0, 0);

			f = f.rotateX(rotation->x);
			f = f.rotateY(rotation->y);
			f = f.rotateZ(rotation->z);

			f.normalize();

			return f;
		}

		void Transform::setRot(Utilities::Vector3<float> r) {
			Utilities::Vector3<float> rotchild(r.x, r.y, r.z);
			rotchild.x -= rotation->x;
			rotchild.y -= rotation->y;
			rotchild.z -= rotation->z;
			updateChildren(1, rotchild);
			rotation->x = r.x;
			rotation->y = r.y;
			rotation->z = r.z;
		}

		void Transform::setPos(Utilities::Vector3<float> p) {
			updateChildren(0, p - *position);
			position->x = p.x;
			position->y = p.y;
			position->z = p.z;
			//updateChildren(0, p);
			/*if (parent != nullptr) {
				
				localPosition->x = parent->position->x - p.x;
				localPosition->y = parent->position->y - p.y;
				localPosition->z = parent->position->z - p.z;
			}*/
		}

		void Transform::setLocalPos(Utilities::Vector3<float> lP)
		{
			localPosition->x = lP.x;
			localPosition->y = lP.y;
			localPosition->z = lP.z;
		}

		void Transform::setScale(Utilities::Vector3<float> s) {
			//updateChildren(2);
			scale->x = s.x;
			scale->y = s.y;
			scale->z = s.z;
		}

		void Transform::setScale(Utilities::Vector3<float> s, Utilities::Vector3<float> s2)
		{
			scale->x *= s.x * s2.x;
			scale->y *= s.y * s2.y;
			scale->z *= s.z * s2.z;
			//updateChildren(2);
		}

		void Transform::removeChild(Transform* child)
		{
			children.remove(child);
		}

		void Transform::translate(Utilities::Vector3<float> p) {

			position->x += p.x;
			position->y += p.y;
			position->z += p.z;
			/*if (parent != nullptr) {
				localPosition->x += p.x;
				localPosition->y += p.y;
				localPosition->z += p.z;
			}*/
			updateChildren(0, p);
		}

		void Transform::rotate(Utilities::Vector3<float> r) {
			//updateChildren(1);
			//rotateChild(2, r.x, *position);
			Utilities::Vector3<float> rotchild(r.x, r.y, r.z);
			rotateChild(*position, rotchild);
			rotation->x += r.x;
			//rotateChild(1, r.y, *position);
			rotation->y += r.y;
			//rotateChild(0, r.z, *position);
			rotation->z += r.z;

		}

		void Transform::detachChildren() {
			for (auto c : children) c->setParent(nullptr);
		}

		void Transform::setParent(Transform* p) {
			parent = p;
			if (parent != nullptr) parent->addChild(this);
		}

		Transform* Transform::getParent()
		{
			return parent;
		}

		Transform* Transform::getFirstParent()
		{
			if (parent == nullptr) return this;
			else parent->getFirstParent();
		}

		void Transform::addChild(Transform* c) {
			Utilities::Vector3<float> aux = *c->getPos() - *position;
			c->setLocalPos(aux);
			children.push_back(c);

		}

		void Transform::updateChildren(int mode, Utilities::Vector3<float> p)
		{
			if (children.empty()) return;

			for (auto& c : children) {
				switch (mode)
				{
				case 0: c->translate(p); break;
				case 1: rotateChild(*position, p); break;
				case 2: c->setScale(*scale, *c->scale); break;
				default:
					break;
				}
			}
		}

		Transform* Transform::getChild(int indx)
		{
			if (children.empty()) return nullptr;

			auto it = children.begin();
			for (int i = 0; i < indx; ++i) {
				it++;
			}
			return *it;
		}

		void Transform::rotateChild(Utilities::Vector3<float> posP, Utilities::Vector3<float> rotAng)
		{
			if (children.empty()) return;

			Utilities::Vector3<float> auxPos;

			float x = 0, y = 0, z = 0, dist = 0, angleRad = 0;
			for (auto& c : children) {
				c->rotateChild(posP, rotAng);

				//giro en ang z
				x = ((c->localPosition->x) * std::cos(rotAng.z) - (c->localPosition->y) * std::sin(rotAng.z));
				y = ((c->localPosition->x) * std::sin(rotAng.z) + (c->localPosition->y) * std::cos(rotAng.z));

				c->localPosition->x = x;
				c->localPosition->y = y;
				c->position->x = c->localPosition->x + posP.x;
				c->position->y = c->localPosition->y + posP.y;
				c->rotation->z += rotAng.z;

				//giro en ang y
				z = ((c->localPosition->z) * std::cos(rotAng.y) - (c->localPosition->x) * std::sin(rotAng.y));
				x = ((c->localPosition->z) * std::sin(rotAng.y) + (c->localPosition->x) * std::cos(rotAng.y));



				c->localPosition->z = z;
				c->localPosition->x = x;
				c->position->x = c->localPosition->x + posP.x;
				c->position->z = c->localPosition->z + posP.z;
				c->rotation->y += rotAng.y;

				//giro en ang x
				y = ((c->localPosition->y) * std::cos(rotAng.x) - (c->localPosition->z) * std::sin(rotAng.x));
				z = ((c->localPosition->y) * std::sin(rotAng.x) + (c->localPosition->z) * std::cos(rotAng.x));

				c->localPosition->z = z;
				c->localPosition->y = y;
				c->position->y = c->localPosition->y + posP.y;
				c->position->z = c->localPosition->z + posP.z;
				c->rotation->x += rotAng.x;
			}

		}

		void Transform::update()
		{
			
		}

		void Transform::receiveMessage(Utilities::StringFormatter& sf)
		{
			Utilities::Vector3<float> newPos = *position;
			Utilities::Vector3<float> newRot = *rotation;
			Utilities::Vector3<float> newScale = *scale;


			sf.tryGetVector3("scale", newScale);
			sf.tryGetVector3("rotation", newRot);
			sf.tryGetVector3("position", newPos);
			setPos(newPos);
			setRot(newRot);
			setScale(newScale);
			setLocalPos(newPos);
		}
		void Transform::receiveComponent(int i, Component* c)
		{
			//setChild
			if (i == 0) {
				addChild(static_cast<Transform*>(c));
			}
			else if (i == 1) {
				setParent(static_cast<Transform*>(c));
			}
		}
	}
}