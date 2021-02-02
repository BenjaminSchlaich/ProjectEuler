#include "pch.h"
#include "CppUnitTest.h"
#include "Vector.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace MathLibrary;

namespace TestMathLib
{
	TEST_CLASS(TestMathLib)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			MathLibrary::Vector v1(1,0);
			MathLibrary::Vector v2(3, 4);

			v1 += v2;

		}
	};
}
