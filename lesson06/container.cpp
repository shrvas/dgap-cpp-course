
#include "class.h"

/*
 * Generally, this is not a good practice. Templates should be defined
 * completely in header file to be available for instantiation by user.
 * Here just example provided
 */
template<typename T>
T Container<T>::getData()
{
	return m_data;
};

// Template explicit instantiation with type int
template
class Container<int>;

