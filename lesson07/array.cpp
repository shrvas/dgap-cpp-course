
#include <stdexcept>
#include <iostream>

using namespace std;

// Variable-size array, storage on heap
template <typename T>
class Array
{
public:
    explicit Array(unsigned size = 64):
        m_size(size)
    {
        m_data = new T[size]();
    }
    ~Array()
    {
        delete [] m_data;
    }

    const T& operator [] (unsigned index) const
    {
        //cout << "const" << endl;
        if (index >= m_size)
            throw(range_error("range"));
        return m_data[index]; 
    }

    T& operator [] (unsigned index)
    {
        //cout << "reference" << endl;
        if (index >= m_size)
            throw(range_error("range"));
        return m_data[index];
    }

    void Resize(unsigned new_size)
    {
        T *n = new T[new_size];
        for (int i = 0; i < m_size; i++) {
            // This is really good way to move old values to new storage,
            // as class T must support operator=
            n[i] = std::move(m_data[i]);
        }
        delete [] m_data;
        m_size = new_size;
        m_data = n;
    }

private:
    T *m_data;

    unsigned m_size;
};


int main()
{
    Array<int> a(10);

    int * n = new int;

    a[0] = 0;
    for (int i = 1; i < 10; i++)
        a[i] = i;
    
    // This will terminate program with exception
    //n[32141221] = 1;
    int ii = a[5];
    cout << a[5] << endl;
    a.Resize(15);
    cout << a[5] << endl;

    const Array<int> c(10);
    // Here const version of operator[] is used
    cout << c[0] << endl;

    return 0;
}

