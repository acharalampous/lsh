#include <iostream>
#include <array>
#include "template_class.h"

using namespace std;

int main(void){
    int a = 3.1;
    myClass<int> newItem(a);
    //newItem.fillClass(a);
    newItem.printClass();
}