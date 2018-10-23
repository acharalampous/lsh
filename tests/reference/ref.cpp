#include <iostream>

using namespace std;

int reference(int& val){
    val += 10;
}

int main(void){
    int val = 5;
    cout << val << endl;
    reference(val);
    cout << val << endl;
}
