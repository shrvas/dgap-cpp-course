#include "storage.h"

template <typename T>
Storage<T>::Storage(const T &val) {
    SetVal(val);
}
template <typename T>
void Storage<T>::SetVal(const T &val) {
    m_val = val;
}
template <typename T>
T Storage<T>::GetVal() {
    return m_val;
}
template <typename T>
Storage<T>::~Storage(){}

Storage<char*>::Storage() {
    m_val = nullptr;
}
Storage<char*>::Storage(const Storage& val) {
    SetVal(val.m_val);
}
Storage<char*>::Storage(const char* val) {
    SetVal(val);
}
void Storage<char*>::SetVal(const char* val) {
    int c = 0;
    while(val[c++]);
    delete[] m_val;
    m_val = new char[c];
    memcpy(m_val,val,c);
}
char* Storage<char*>::GetVal() {
    return m_val;
}
Storage<char*>::~Storage(){}
