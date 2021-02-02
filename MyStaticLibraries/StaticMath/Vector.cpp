#include "pch.h"
#include "Vector.h"

namespace MathLibrary
{

	Vector operator+(Vector v1, Vector& v2)
	{
		v1 += v2;
		return v1;
	}

	MathLibrary::Vector::Vector(int deltaX, int deltaY)
	{
		this->deltaX = deltaX;
		this->deltaY = deltaY;
	}

	MathLibrary::Vector::Vector(Vector& v)
	{
		deltaX = v.deltaX;
		deltaY = v.deltaY;
	}

	Vector& MathLibrary::Vector::operator+=(Vector& v)
	{
		deltaX += v.deltaX;
		deltaY += v.deltaY;
		return *this;
	}

	std::string Vector::to_string()
	{
		return "(" + std::to_string(deltaX) + "|" + std::to_string(deltaY) + ")";
	}

}