#include <iostream>

#include "template_class.h"

using namespace std;

template class myClass<int>;
template class myClass<double>;

template <class T>
myClass<T>::myClass(T newitem){
    myVar = newitem;
    for(int i = 0; i < 50; i++)
        myArr[i] = newitem + i;
}

template <class T>
void myClass<T>::printClass(){
    for(int i = 0; i < 50; i++)
        cout << myArr[i] << endl;
}
