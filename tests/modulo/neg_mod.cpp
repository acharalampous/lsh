#include <iostream>
#include <cmath>

using namespace std;

int main(int argc, char* argv[]){
	int x = atoi(argv[1]);
	int y = atoi(argv[2]);

	//cout << floor(-1.2) << endl;
	//cout << "Division: " << floor( (float)x / (float)y ) << endl;	

	int res = x - ((floor( (float)x / (float)y) ) * y);

	cout << res << endl;
}
