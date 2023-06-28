#pragma once
#include "vector.h"

namespace MySTL
{
	template<typename T>
	class stack
	{
	private:
		vector<T> _data{};
	public:
		stack() = default;
	};
}
