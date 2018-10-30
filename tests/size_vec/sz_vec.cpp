#include <iostream>
#include <vector>
#include <array>
#include <unordered_map>
using namespace std;

int main(void){
	unordered_map<int, int>* fs;

	cout << sizeof(fs) << endl;

	fs = new unordered_map<int,int>;

	cout << fs->size() << endl;

	cout << sizeof(*fs) << endl;

	(*fs)[1] = 3;

	cout << fs->size() << endl;

	
	cout << fs->load_factor() << endl;


}
