#include <iostream>
#include <ctime>

#include "hashtable.h"

using namespace std;

euclideanHF::euclideanHF(){
	random_device rd;

	mt19937 gen(rd());

	for(int i = 0; i < D; i++){
		normal_distribution<float> nd_random(0.0, 1.0);
		
		v[i] = nd_random(gen);
	}

	for (int i = 0; i < D; i++)
		cout << i << ". " << v[i] << endl;

	uniform_real_distribution<> real_random(0.0, W);

	t = real_random(gen);

	cout << "T: " << t << endl;

}

int euclideanHF::getValue(){
	return 1;
}
