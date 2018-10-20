#include <random>
#include <iostream>

#define W 4

using namespace std;

int main(void){
	random_device rd;
	mt19937 gen(rd());	

	/* Get random int number t(displacement) */
	uniform_int_distribution<int> rand_Z(-40,40); 

	for(int i = 0; i != 45; i++){
		cout << rand_Z(gen) << endl;
	}
}
