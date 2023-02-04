#include <iostream>
#include "tests/ArrayTest.h"
#include "tests/VectorTest.h"
#include "includes/String.h"
#include <string>
using namespace std;

int main()
{
    string s{ "Hello, world!" };
    s = s + "H";
    MySTL::String s1{ "HEllo!" };
    cin >> s1;
    cout << s1 << endl;
    cout << s.size() << endl;
    ArrayTest::ArrayTest();
    VectorTest::VectorTest();
    return 0;
}