#pragma once
#include <iostream>
#include "../includes/stack.h"

namespace StackTest
{
    void StackTest()
    {
        std::cout << "*-----Here are MySTL::Stack Test-----*" << std::endl;
        MySTL::stack<int> l{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        std::cout << "Init l : ";
        l.view();
        std::cout << "Input a number: ";
        int num{ 0 };
        std::cin >> num;
        l.push(num);
        std::cout << "After push " << num << " : ";
        l.view();
        MySTL::stack<int> u(l);
        std::cout << "l == u : " << std::boolalpha << (l == u) << std::endl;
        MySTL::stack<int> v = MySTL::stack<int>{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        u.push(3);
        std::cout << "After push 3 into u : ";
        u.view();
        
        MySTL::stack<int> z{ 1 };
        std::cout << "Init z : ";
        z.view();
        z.pop();
        std::cout << "Pop an element : ";
        z.view();
        std::cout << "*-----End of MySTL::Stack Test-----*" << std::endl;
    }
}