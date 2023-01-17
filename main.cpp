#include <iostream>
#include "Vector.h"
using namespace std;

int main()
{
    MySTL::Vector<int> v{ 1, 2, 3 };
    cout << v << endl;
    v.push_back(20);
    cout << v << endl;
    return 0;
}