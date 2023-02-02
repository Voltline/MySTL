#pragma once
#include <iostream>
#include "Vector.h"

namespace VectorTest
{
	void VectorTest()
	{
        std::cout << "*-----Here are MySTL::Vector<T> Test-----*" << std::endl;
        MySTL::Vector<int> u(4, 2), v{ 1, 2, 3, 4, 5, 6 };
        std::cout << "Init u : ";
        u.view();
        std::cout << "Init v : ";
        v.view();

        v.insert(v.end() - 3, 20);
        std::cout << "Insert single to v : ";
        v.view();

        v.insert(v.begin() + 1, 6, 20);
        std::cout << "Insert multi-value to v : ";
        v.view();

        std::cout << "Capacity of v : " << v.capacity() << std::endl;
        std::cout << "Size of v : " << v.size() << std::endl;

        v.reserve(5);

        for (int i = 0; i < 10; i++) {
            u.push_back(1);
        }
        std::cout << "Push_back to u : ";
        u.view();


        v.insert(v.begin() + 2, u.begin(), u.end());
        std::cout << "Insert from u to v : ";
        v.view();

        std::cout << "Pointer view u : " << u.data() << std::endl;
        std::cout << "Pointer View v : " << v.data() << std::endl;
        std::cout << "Swap u & v" << std::endl;
        u.swap(v);

        std::cout << "View v : ";
        v.view();
        std::cout << "View u : ";
        u.view();

        std::cout << "Pointer view u : " << u.data() << std::endl;
        std::cout << "Pointer view v : " << v.data() << std::endl;
        std::cout << "*-----End of MySTL::Vector<T> Test-----*" << std::endl;
	}
}