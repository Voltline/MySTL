#include <iostream>
#include "Vector.h"
using namespace std;

int main()
{
    MySTL::Vector<int> u(4, 2), v{1, 2, 3, 4, 5, 6};
    cout << "Init u : ";
    u.view();
    cout << "Init v : ";
    v.view();

    v.insert(v.end()-3, 20);
    cout << "Insert single to v : ";
    v.view();

    v.insert(v.begin() + 1, 6, 20);
    cout << "Insert multi-value to v : ";
    v.view();

    cout << "Capacity of v : " << v.capacity() << endl;
    cout << "Size of v : " << v.size() << endl;

    v.reserve(5);

    for (int i = 0; i < 10; i++) {
        u.push_back(1);
    }
    cout << "Push_back to u : ";
    u.view();


    v.insert(v.begin() + 2, u.begin(), u.end());
    cout << "Insert from u to v : ";
    v.view();

    cout << "Pointer view u : " << u.data() << endl;
    cout << "Pointer View v : " << v.data() << endl;
    cout << "Swap u & v" << endl;
    u.swap(v);

    cout << "View v : ";
    v.view();    
    cout << "View u : ";
    u.view();

    cout << "Pointer view u : " << u.data() << endl;
    cout << "Pointer view v : " << v.data() << endl;
    return 0;
}