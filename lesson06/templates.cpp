
#include <iostream>
#include <string>
#include "class.h"

using std::cout;
using std::endl;

// Static size array, templated size param and default values:
template <typename T=int, int N=20>
class Array
{
public:
    // Realisation details

private:
	T m_array[N];   // Just old-fashioned static array member
};

// Classic example, smth like tuple in other languages
template <class T1, class T2>
class Pair
{
public:
    Pair(const T1 &c1, const T2 &c2):
        m_1(c1),
        m_2(c2)
    { };

	T1 first() { return m_1; };
	T2 second() { return m_2; };

	void Show()
    {
        cout << "(" << m_1 << ", " << m_2 << ")" << endl;
    }

private:
    // Const members could be set only in constructor init list
	const T1 m_1;
	const T2 m_2;
};


int main()
{
	int i = 13;
	Array<> a;  // int[20]
	cout << "Size a: " << sizeof(a) << endl;
	Array<long> l;  // long[20]
	cout << "Size l: " << sizeof(l) << endl;
	Array<int, 100> a100;  // int[100]
	cout << "Size a100: " << sizeof(a100) << endl;

    Pair<int, float> p(1, 2.0);
    p.Show();
    cout << p.first() << " " << p.second() << endl;

    Pair<std::string, bool> p2("This program works", true);
    cout << p2.first() << ": " << std::boolalpha << p2.second() << endl;

	return 0;
}

