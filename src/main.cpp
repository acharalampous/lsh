#include <iostream>
#include <string>

#include "datasets.h"

using namespace std;

int main(void){
    dataset<int> myData;
    myData.add_vector("192 165 123 123 9 1");
    myData.add_vector("1234 1456 14563 23 9 1123");
    myData.add_vector("543 1456 53 13 7 123");
    myData.print();
}
