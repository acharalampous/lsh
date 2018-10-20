#include <iostream>
#include <vector>
#include <array>

using namespace std;

int main(void){
	vector<int>* ptr;

	// // int d = 5;
	// // v = new array<int, d>;

	// // v.push_back(5.0);
	
	// // v.push_back(2.1);
	// // v.push_back(1.3);
	// // v.push_back(45.1);

	// // cout << v[0] << endl; 
	// // cout << v[1] << endl;
	// // cout << v[2] << endl;
	// cout << v[3] << endl;

	ptr = new vector<int>[5];

	ptr[0].push_back(3);
	ptr[1].push_back(-5);

	cout << ptr[0].size() << endl;
	cout << ptr[1].size() << endl;
	cout << ptr[2].size() << endl;
	cout << ptr[3].size() << endl;
	cout << ptr[4].size() << endl;
	cout << ptr[5].size() << endl;


}
