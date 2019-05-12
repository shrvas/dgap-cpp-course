
#include <iostream>
#include "container.h"

using std::cout;
using std::endl;


int main()
{
	int i = 13;
    // No instantiation here, found <int> instance (explicit from header)
	Container<int> cint = i;
    // Template implicit instantiation with type long
	Container<long> c = i;

	c.Show();

    // Linker error: Container<long>::getData() not found for instantiation
    // (here only header code provided, but getData is in .cpp file)
	int res = c.getData();
    // This OK, calculated in compilation time
	decltype(c.getData()) i2;
    // This OK, template <int> instance created explicitly in class.cpp
    // (so instance contain getData method)
	int resint = cint.getData();

	cout << "s: " << sizeof(i2) << endl;

	return 0;
}

