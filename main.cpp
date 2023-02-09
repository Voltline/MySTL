#include <iostream>
#include "tests/ArrayTest.h"
#include "tests/VectorTest.h"
#include "tests/StringTest.h"
#include <list>
#include "includes/List.h"
using namespace std;

int main()
{
    MySTL::List<int> l{ 1, 2, 3, 4, 5 };
    l.view();
   //  StringTest::StringTest();
    // ArrayTest::ArrayTest();
    // VectorTest::VectorTest();
    return 0;
}