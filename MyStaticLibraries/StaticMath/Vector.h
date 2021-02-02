#pragma once

#include <string>

namespace MathLibrary
{

	class Vector
	{
	public:

		Vector(int deltaX, int deltaY);

		Vector(Vector& v);

		Vector& operator+=(Vector& v);

		std::string to_string();

	private:

		int deltaX;
		int deltaY;
	};

}