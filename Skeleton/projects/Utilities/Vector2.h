#pragma once
#include <math.h>
#include "Recta.h"

template<typename T>
class Vector2 {
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

	Vector2 operator+(Vector2 const& v2) const {
		return Vector3(x + v2.x, y + v2.y);
	}

	Vector2 operator-(Vector2 const& v2) const {
		return Vector3(x - v2.x, y - v2.y);
	}

	bool operator==(Vector2 const& b) const {
		return (x == v2.x && y == v2.y);
	}

	bool operator!=(Vector2 const& b) const {
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
		return sqrt(pow(x, 2) + pow(y, 2));
	}

	T magnitude2() //Magnitud al cuadrado
	{
		return pow(sqrt(pow(x, 2) + pow(y, 2)), 2);
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

	Vector2<T> vectorialProduct(Vector2<T> b)
	{
		Vector2<T> vectorial;

		vectorial.x = y * b.z - z * b.y;
		vectorial.y = z * b.x - x * b.z;

		return vectorial;
	}

	T getDistance(Vector2<T> b) //Distancia entre 2 vectores
	{
		int x_ = x - b.x;
		int y_ = y - b.y;
		Vector2 aux = Vector2(x_, y_);

		return aux.magnitude();
	}
};