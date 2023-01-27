#pragma once
#include <iostream>
#include "Vector.h"

class String
{
private:
	MySTL::Vector<char> container{};
	size_t char_size;
};

