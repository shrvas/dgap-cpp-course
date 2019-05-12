
#include <iostream>

template <typename T>
class Container
{
public:
	Container(T data): m_data(data) {};
	~Container() {};

	void Show()
	{
		std::cout << m_data << std::endl;
	};

	T getData();

private:
	T m_data;
};

