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
			localRotation = new Utilities::Vector4<float>(0.0, 0.0, 0.0, 0.0);
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

		Utilities::Vector3<float> Transform::forward()
		{
			Utilities::Vector3<float> f(0, 0, 1);

			f = f.rotateX(rotation->x);
			f = f.rotateY(rotation->y);
			f = f.rotateZ(rotation->z);
			
			f.normalize();

			return f;
		}

		void Transform::setRot(Utilities::Vector4<float> r) {
			rotation->x = r.x;
			rotation->y = r.y;
			rotation->z = r.z;
			rotation->w = r.w;
			updateChildren(1, Utilities::Vector3<float>(0, 0, 0));
		}

		void Transform::setPos(Utilities::Vector3<float> p) {
			position->x = p.x;
			position->y = p.y;
			position->z = p.z;
			//updateChildren(0, p);
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

		void Transform::translate(Utilities::Vector3<float> p) {
			
			position->x += p.x;
			position->y += p.y;
			position->z += p.z;
			updateChildren(0, p);
		}

		void Transform::rotate(Utilities::Vector4<float> r) {
			//updateChildren(1);
			rotation->x += r.x;
			//rotateChild(1, r.x, *position);
			rotation->y += r.y;
			//rotateChild(2, r.y, *position);
			//rotateChild(0, r.z, *position);
			rotation->z += r.z;
			rotation->w += r.w;//??
		}

		void Transform::detachChildren() {
			for (auto c : children) c->setParent(nullptr);
		}

		void Transform::setParent(Transform* p) {
			parent = p;
			parent->addChild(this);
		}

		Transform* Transform::getParent()
		{
			return parent;
		}

		void Transform::addChild(Transform* c) {
			c->setLocalPos(*c->getPos());
			children.push_back(c);
			
		}

		void Transform::updateChildren(int mode, Utilities::Vector3<float> p)
		{
			if (children.empty()) return;

			for (auto& c : children) {
				switch (mode)
				{
				case 0: c->translate(p); break;
				//case 1: c->rotate(*rotation); break;
				case 2: c->setScale(*scale, *c->scale); break;
				default:
					break;
				}
			}
		}

		void Transform::rotateChild(int modeAngule, float ang, Utilities::Vector3<float> posP)
		{
			if (children.empty()) return;

			Utilities::Vector3<float> auxPos;

			float x = 0, y = 0, z = 0, dist = 0, angleRad = 0;
			for (auto& c : children) {
				c->rotateChild(modeAngule, ang, *c->position);
				switch (modeAngule)
				{
					//giro en ang z
				case 0:
					//posicion respecto al padre

					/*x = c->localPosition->x;
					y = c->localPosition->y;

					dist = std::sqrt(std::pow(x, 2) + std::pow(y, 2));
					c->position = c->getParent()->getPos();
					c->rotation->z += ang;
					c->position->x += c->forward().x * dist;
					c->position->y += c->forward().y * dist;*/
					//c->position->z += c->forward().z * dist;

					//NO SE QUE ESTOY HACIENDOOO AAAAAAAAAAAA

					/*c->position->x = posP.x + (std::cos(ang) * c->localPosition->x) +(-std::sin(ang) * c->localPosition->x);
					c->position->y = posP.y + (std::sin(ang) * c->localPosition->y) + (std::cos(ang) * c->localPosition->y);*/

					//x = c->localPosition->x;
					//y = c->localPosition->y;

					//dist = std::sqrt(std::pow(x, 2) + std::pow(y, 2));

					//c->position->x = dist * std::cos(ang /** std::numbers::pi / 180*/);
					//
					//c->position->y = dist * std::sin(ang/** std::numbers::pi / 180*/);
					//
					//c->rotation->z += ang;

					angleRad = ang * 3.141592f / 180.0f;
					x = (c->position->x) * std::cos(ang) - (c->position->y) * std::sin(ang);
					y = (c->position->x) * std::sin(ang) + (c->position->y) * std::cos(ang);
					c->localPosition->x = x ;
					c->localPosition->y = y ;
					c->position->x = c->localPosition->x + c->getParent()->getPos()->x;
					dist = c->getParent()->getPos()->y;
					c->position->y = c->localPosition->y + c->getParent()->getPos()->y;
					break;
					//giro en ang x
				case 1:
					//posicion respecto al padre
					z = c->position->z - posP.z;
					y = c->position->y - posP.y;

					dist = std::sqrt(std::pow(z, 2) + std::pow(y, 2));

					c->position->z = dist * cos(ang);
					c->position->y = dist * sin(ang);

					c->rotation->x += ang;
					break;
					//giro en ang y
				case 2:
					//posicion respecto al padre
					z = c->position->z - posP.z;
					x = c->position->x - posP.x;

					dist = std::sqrt(std::pow(z, 2) + std::pow(x, 2));

					c->position->z = dist * cos(ang);
					c->position->x = dist * sin(ang);

					c->rotation->y += ang;
					break;
				default:
					break;
				}

				c->rotateChild(modeAngule, ang, *position);
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
			if(!children.empty())
			std::cout <<"Soy un ogro bobo: " << position->y << std::endl;
		}

		void Transform::receiveMessage(Utilities::StringFormatter& sf)
		{
			sf.tryGetVector3("scale", *scale);
			sf.tryGetVector4("rotation", *rotation);
			sf.tryGetVector3("position", *position);
			//sf.tryGetVector3("position", *localPosition);
			
		}
		void Transform::receiveComponent(int i, Component* c)
		{
			//setChild
			if (i == 1) {
				setParent(static_cast<Transform*>(c));
			}
		}
	}
}