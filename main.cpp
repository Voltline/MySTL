#include <iostream>
#include "tests/ArrayTest.h"
#include "tests/VectorTest.h"
#include <string>
using namespace std;

int main()
{
    string s{ "Hello, world!" };
    s = s + "H";
    cout << s.size() << endl;
    ArrayTest::ArrayTest();
    VectorTest::VectorTest();
    return 0;
}