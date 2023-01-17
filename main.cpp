#include <iostream>
#include "Vector.h"
using namespace std;

int main()
{
    MySTL::Vector<int> v{ 1, 2, 3 };
    cout << v << endl;
    return 0;
}