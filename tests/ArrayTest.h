#pragma once
#include <iostream>
#include "../includes/Array.h"

namespace ArrayTest
{
	void ArrayTest()
	{
		std::cout << "*-----Here are MySTL::Array<T, _Size> Test-----*" << std::endl;
		MySTL::Array<int, 6> arr{ 3, 12, 2 };
		std::cout << "Initialize arr: ";
		arr.view();
		
		arr.fill(6.0);
		arr[3] = 6;
		std::cout << "Fill and change arr: ";
		arr.view();

		arr.front() = 108;
		arr.back() = 199;

		std::cout << "Change front and back arr: ";
		arr.view();
		std::cout << "*-----End of MySTL::Array<T, _Size> Test-----*" << std::endl;
	}
}