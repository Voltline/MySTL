#pragma once
#include <iostream>
#include "Vector.h"

namespace MySTL 
{
	class String
	{
	private:
		Vector<char> container{};
		size_t char_size{ 0 };
	};
}


