#pragma once
#include <../Export.h>
#include <math.h>
#include <iostream>
#include "Utils.h"

namespace LoveEngine {
	namespace Utilities
	{
		template<typename T = float >
		class lovexport Vector3 {
		private:
			float gradosARadianes(double grados)
			{
				return grados * 3.1416 / 180;
			}

		public:

			T x;
			T y;
			T z;

			Vector3()
			{
				x = 0; y = 0; z = 0;
			}

			Vector3(T prim, T sec, T ter)
			{
				x = prim;
				y = sec;
				z = ter;
			}

			Vector3(const Vector3<T>& other) {
				x = other.x;
				y = other.y;
				z = other.z;
			}

			Vector3<T> operator+(Vector3<T> const& v2) const {
				return Vector3<T>(x + v2.x, y + v2.y, z + v2.z);
			}

			Vector3<T> operator*(float f) const {
				return Vector3<T>(x * f, y * f, z * f);
			}

			Vector3<T> operator-(Vector3<T> const& v2) const {
				return Vector3<T>(x - v2.x, y - v2.y, z - v2.z);
			}

			Vector3<T> operator+=(Vector3<T> const& v2) const {
				return Vector3<T>(x + v2.x, y + v2.y, z + v2.z);
			}

			bool operator==(Vector3<T> const& v2) const {
				return x == v2.x && y == v2.y && z == v2.z;
			}

			bool operator!=(Vector3<T> const& v2) const {
				return x != v2.x || y != v2.y || z != v2.z;
			}



			void inverse()
			{
				x = -x;
				y = -y;
				z = -z;
			}

			void add(T sumX, T sumY, T sumZ)
			{
				x += sumX;
				y += sumY;
				z += sumZ;
			}

			T magnitude() //Magnitud 
			{
				return sqrt(x * x + y * y + z * z);
			}

			T magnitudeSqr() //Magnitud al cuadrado
			{
				return x * x + y * y + z * z;
			}

			void normalize() //normalizar vector
			{
				T magnitud = magnitude();

				if (magnitud == 0) return;

				x = x / magnitud;
				y = y / magnitud;
				z = z / magnitud;
			}

			Vector3<T> getNormalized() //recibir vector normalizado
			{
				T magnitud = magnitude();

				float x_, y_, z_;
				x_ = x / magnitud;
				y_ = y / magnitud;
				z_ = z / magnitud;
				return Vector3<T>(x_, y_, z_);
			}

			T scalarProduct(Vector3<T> b)
			{
				int x_ = x * b.x;
				int y_ = y * b.y;
				int z_ = z * b.z;

				return (x_ + y_ + z_);
			}

			void lerp(Vector3<T> b, float t)
			{
				x = Utilities::lerp(x, b.x, t);
				y = Utilities::lerp(y, b.y, t);
				z = Utilities::lerp(z, b.z, t);
			}

			static Vector3<T> lerp(Vector3<T> a, Vector3<T> b, float t) {
				Vector3<T> c;
				c.x = Utilities::lerp(a.x, b.x, t);
				c.y = Utilities::lerp(a.y, b.y, t);
				c.z = Utilities::lerp(a.z, b.z, t);
				return c;
			}

			Vector3<T> vectorialProduct(Vector3<T> b)
			{
				Vector3<T> vectorial;

				vectorial.x = y * b.z - z * b.y;
				vectorial.y = z * b.x - x * b.z;
				vectorial.z = x * b.y - y * b.x;

				return vectorial;
			}

			T getDistance(Vector3<T> b) //Distancia entre 2 vectores
			{
				int x_ = x - b.x;


				int y_ = y - b.y;
				int z_ = z - b.z;
				Vector3<T> aux = Vector3(x_, y_, z_);
				return aux.magnitude();
			}

			Vector3<T> rotateX(double degrees) { //Rotar en el eje x
				//double rads = gradosARadianes(degrees);

				Vector3<T> A;
				A.x = x;
				A.y = cos(degrees) * y - sin(degrees) * z;
				A.z = sin(degrees) * y + cos(degrees) * z;

				return A;
			}

			Vector3<T> rotateY(double degrees) { //Rotar en el eje y
				//double rads = gradosARadianes(degrees);

				Vector3<T> A;
				A.x = (cos(degrees) * x) + (sin(degrees) * z);
				A.y = y;
				A.z = (-sin(degrees) * x) + (cos(degrees) * z);

				return A;
			}

			Vector3<T> rotateZ(double degrees) { //Rotar en el eje z
				//double rads = gradosARadianes(degrees);

				Vector3<T> A;
				A.x = (cos(degrees) * x) - (sin(degrees) * y);
				A.y = (sin(degrees) * x) + (cos(degrees) * y);
				A.z = z;

				return A;
			}

			explicit operator Vector3<int>() {
				Vector3<int> v = Vector3<int>();
				v.x = (int)x;
				v.y = (int)y;
				v.z = (int)z;
				return v;
			}

			explicit operator Vector3<float>() {
				Vector3<float> v = Vector3<float>();
				v.x = (float)x;
				v.y = (float)y;
				v.z = (float)z;
				return v;
			}

		};


		template <class T>
		std::ostream& operator<<(std::ostream& os, const Vector3<T>& v)
		{
			os << v.x << ", " << v.y << ", " << v.z;
			return os;
		}
	}

}