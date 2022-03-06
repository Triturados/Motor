#pragma once

struct element
{
	float value;
	float landa;
};

class Recta
{
public:
	element x;
	element y;
	element z;

	Recta(element x_, element y_, element z_)
	{
		x = x_;
		y = y_;
		z = z_;
	}

};