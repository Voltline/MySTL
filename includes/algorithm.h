#pragma once
#include <iostream>

namespace MySTL
{
	template<typename T>
	void swap(T& a, T& b)
	{
		T temp{ a };
		a = b;
		b = temp;
	}
}