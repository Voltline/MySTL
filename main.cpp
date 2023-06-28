#include <iostream>
#include "tests/ArrayTest.h"
#include "tests/VectorTest.h"
#include "tests/StringTest.h"
#include <list>
#include "includes/list.h"
using namespace std;

int main()
{
    MySTL::list<int> l{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    l.view();
    for (auto& i : l) {
        cout << &i << endl;
    }
    MySTL::list<int> u(l);
    u.view(); // 调用拷贝该构造函数
    for (auto& i : u) {
        cout << &i << endl;
    }
    u.push_back(3);
    u.view();
    MySTL::list<int> z{ 1 };
    z.view();
    z.pop_back();
    z.view();
    // StringTest::StringTest();
    // ArrayTest::ArrayTest();
    // VectorTest::VectorTest();
    return 0;
}