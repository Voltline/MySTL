#include <iostream>
#include "Vector.h"
using namespace std;

int main()
{
    MySTL::Vector<int> v{ 1, 2, 3, 4, 5, 6, 7, 1, 2, 3, 4, 5, 6, 7, 1, 2, 3, 4, 5, 6, 7 };
    cout << v << endl;
    v.push_back(20);
    cout << v << endl;
    cout << v.capacity_num() << endl;
    cout << v.elem_num() << endl;
    cout << v << endl;
    v.erase(v.begin(), v.end() - 5);
    cout << v.capacity_num() << endl;
    cout << v.elem_num() << endl;
    cout << v << endl;

    return 0;
}