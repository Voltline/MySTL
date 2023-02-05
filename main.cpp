#include <iostream>
#include "tests/ArrayTest.h"
#include "tests/VectorTest.h"
#include "includes/String.h"
using namespace std;

int main()
{
    MySTL::String s1{ "HEllo!" }, s3{ "World!" };
    s1 += s3;
    cout << s1 + s3 << endl;

    cout << boolalpha << (s1+s3 > s1) << endl;
    cout << s1.size() << endl;

    cout << 3["HeLlO!"] << endl;
    // ArrayTest::ArrayTest();
    // VectorTest::VectorTest();
    return 0;
}