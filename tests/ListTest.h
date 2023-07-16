#pragma once
#include <iostream>
#include "../includes/list.h"

namespace ListTest
{
	void ListTest()
	{
        MySTL::list<int> l{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        l.view();
        for (auto& i : l) {
            std::cout << &i << std::endl;
        }
        MySTL::list<int> u(l);
        u.view(); // 调用拷贝该构造函数
        for (auto& i : u) {
            std::cout << &i << std::endl;
        }
        MySTL::list<int> v = MySTL::list<int>{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        v.view();
        for (auto& i : v) {
            std::cout << &i << std::endl;
        }
        u.push_back(3);
        u.view();
        MySTL::list<int> z{ 1 };
        z.view();
        z.pop_back();
        z.view();
	}
}