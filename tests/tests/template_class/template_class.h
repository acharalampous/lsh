#ifndef TEMPLATE_CLASS_H
#define TEMPLATE_CLASS_H
#include <array>

using namespace std;

template <class T>
class myClass{
    T myVar;
    std::array <T, 50> myArr;

    public:   
        myClass(T);
        void printClass();
};
#endif