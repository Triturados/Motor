#pragma once
#include <math.h>

template<typename T>
class Vector3 {
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

	Vector3 operator+(Vector3 const& v2) const {
		return Vector3(x + v2.x, y + v2.y, z + v2.z);
	}

	bool operator==(Vector3 const& b) const {
		return x == v2.x && y == v2.y && z == v2.z;
	}

	bool operator!=(Vector3 const& b) const {
		return x != v2.x || y != v2.y || z != v2.z;
	}


	Vector3& bool operator =(const Vector3& v1, const Vector3& v2)
	{
		return Vector3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
	}

	Vector3 getVector()
	{
		return Vector3(x, y, z);
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
		return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	}

	T magnitude2() //Magnitud al cuadrado
	{
		return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	}

	void normalize() //normalizar vector
	{
		T magnitud = magnitude();

		x = x / magnitud;
		y = y / magnitud;
		z = z / magnitud;
	}

	T scalarProduct(Vector3<T> b)
	{
		int x_ = x * b.x;
		int y_ = y * b.y;
		int z_ = z * b.z;

		return x_ + y_ + z_;
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
		Vector3 aux = Vector3(x_, y_, z_);
		return aux.magnitude();
	}

	Vector3 rotateX(double degrees) { //Rotar en el eje x
		double rads = gradosARadianes(degrees);

		Vector3 A;
		A.x = x;
		A.y = cos(rads) * y + sin(rads) * z;
		A.z = -sin(rads) * y + cos(rads) * z;

		return A;
	}

	Vector3 rotateY(double degrees) { //Rotar en el eje y
		double rads = gradosARadianes(degrees);

		Vector3 A;
		A.x = (cos(rads) * x) - (sin(rads) * z);
		A.y = y;
		A.z = (sin(rads) * x) + (cos(rads) * z);

		return A;
	}

	Vector3 rotateZ(double degrees) { //Rotar en el eje z
		double rads = gradosARadianes(degrees);

		Vector3 A;
		A.x = (cos(rads) * x) + (sin(rads) * y);
		A.y = (-sin(rads) * x) + (cos(rads) * y);
		A.z = info.direction.z;

		return A;
	}


};