#pragma once
#include <../Export.h>
#include <iostream>

namespace LoveEngine {
	namespace Utilities
	{
		template<typename T = float>
		class lovexport Vector4 {
		public:

			T x;
			T y;
			T z;
			T w;

			Vector4()
			{
				x = 0; y = 0; z = 0; w = 0;
			}

			Vector4(T prim, T sec, T ter, T cuar)
			{
				x = prim;
				y = sec;
				z = ter;
				w = cuar;
			}

			Vector4(const Vector4& v) {
				x = v.x;
				y = v.y;
				z = v.y;
				w = v.w;
			}

			Vector4<T> operator+(Vector4<T> const& v2) const {
				return Vector4(x + v2.x, y + v2.y, z + v2.z, w);
			}

			Vector4<T> operator-(Vector4<T> const& v2) const {
				return Vector4(x - v2.x, y - v2.y, z - v2.z, w);
			}

			Vector4<T> operator+=(Vector4<T> const& v2) const {
				return Vector4(x + v2.x, y + v2.y, z + v2.z, w);
			}

			bool operator==(Vector4<T> const& v2) const {
				return (x == v2.x && y == v2.y && z == v2.z && w == v2.w);
			}

			bool operator!=(Vector4<T> const& v2) const {
				return (x != v2.x || y != v2.y || z != v2.z || w != v2.w);
			}

			void inverse()
			{
				x = -x;
				y = -y;
				z = -z;
				w = -w;
			}
		};

		template <class T>
		std::ostream& operator<<(std::ostream& os, const Vector4<T>& v)
		{
			os << v.x << ", " << v.y << ", " << v.z << ", " << v.w;
			return os;
		}

		//using Quaternion = Vector4<float>;
		template <class T>
		class Vector3;
		template <class T>
		static Vector4<T> EulerToQuaternion(Vector3<T> v) {

		}
	}
}