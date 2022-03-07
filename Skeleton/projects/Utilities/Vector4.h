#pragma once

template<typename T>
class Vector4 {
public:

	T x;
	T y;
	T z;
	T a;

	Vector4()
	{
		x = 0; y = 0; z = 0; a = 0;
	}

	Vector4(T prim, T sec, T ter, T cuar)
	{
		x = prim;
		y = sec;
		z = ter;
	}

	Vector4 operator+(Vector4 const& v2) const {
		return Vector3(x + v2.x, y + v2.y, z + v2.z);
	}

	Vector4 operator-(Vector4 const& v2) const {
		return Vector3(x - v2.x, y - v2.y, z - v2.z);
	}

	bool operator==(Vector4 const& b) const {
		return x == v2.x && y == v2.y && z == v2.z;
	}

	bool operator!=(Vector4 const& b) const {
		return x != v2.x || y != v2.y || z != v2.z;
	}

	void inverse()
	{
		x = -x;
		y = -y;
		z = -z;
		a = -a;
	}
};