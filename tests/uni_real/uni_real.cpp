#include <random>
#include <iostream>

#define W 4

using namespace std;

int main(void){
	random_device rd;
	mt19937 gen(rd());

	/* Get random real number t(displacement) */
	uniform_real_distribution<> real_random(0.0, W);

	for(int i = 0; i != -1; i++){
		float t = real_random(gen);
		if(t == 4.0){
			cout << t << " i: " << i << endl;
			break;
		}
	}
}
