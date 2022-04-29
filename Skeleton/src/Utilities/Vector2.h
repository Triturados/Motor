#pragma once
#include <../Export.h>
#include <math.h>
#include <iostream>
#include "Utils.h"

namespace LoveEngine {
	namespace Utilities
	{
		template<typename T = float>
		class lovexport Vector2 {
		public:

			T x;
			T y;

			Vector2()
			{
				x = 0; y = 0;
			}

			Vector2(T prim, T sec)
			{
				x = prim;
				y = sec;
			}

			Vector2(const Vector2& v) {
				x = v.x;
				y = v.y;
			}

			Vector2<T> operator*(float v) {
				return Vector2<T>(x * v, y * v);
			}

			Vector2<T> operator+(Vector2<T> const& v2) const {
				return Vector2<T>(x + v2.x, y + v2.y);
			}

			Vector2<T> operator-(Vector2<T> const& v2) const {
				return Vector2<T>(x - v2.x, y - v2.y);
			}

			bool operator==(Vector2<T> const& v2) const {
				return (x == v2.x && y == v2.y);
			}

			bool operator!=(Vector2<T> const& v2) const {
				return (x != v2.x || y != v2.y);
			}


			void inverse()
			{
				x = -x;
				y = -y;
			}

			void add(T sumX, T sumY)
			{
				x += sumX;
				y += sumY;
			}

			T magnitude() //Magnitud 
			{
				return sqrt(x * x + y * y);
			}

			T magnitudeSqr() //Magnitud al cuadrado
			{
				return x * x + y * y;
			}

			void normalize() //normalizar vector
			{
				T magnitud = magnitude();

				x = x / magnitud;
				y = y / magnitud;
			}

			T scalarProduct(Vector2<T> b)
			{
				int x_ = x * b.x;
				int y_ = y * b.y;

				return (x_ + y_);
			}

			void lerp(Vector2<T> b, float t)
			{
				x = Utilities::lerp(x, b.x, t);
				y = Utilities::lerp(y, b.y, t);
			}

			static Vector2<T> lerp(Vector2<T> a, Vector2<T> b, float t) {
				Vector2<T> c;
				c.x = Utilities::lerp(a.x, b.x, t);
				c.y = Utilities::lerp(a.y, b.y, t);
				return c;
			}

			T getDistance(Vector2<T> b) //Distancia entre 2 vectores
			{
				int x_ = x - b.x;
				int y_ = y - b.y;
				Vector2<T> aux = Vector2(x_, y_);

				return aux.magnitude();
			}

		};

		template <class T>
		std::ostream& operator<<(std::ostream& os, const Vector2<T>& v)
		{
			os << v.x << ", " << v.y;
			return os;
		}
	}
}