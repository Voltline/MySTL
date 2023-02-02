#include <iostream>
#include <array>
#include "ArrayTest.h"
#include "VectorTest.h"
using namespace std;

int main()
{
    array<int, 10> a{ 100 };
    a.front() = 3;
    ArrayTest::ArrayTest();
    // VectorTest::VectorTest();
    return 0;
}