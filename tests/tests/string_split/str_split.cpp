#include <iostream>
#include <string>
#include <sstream>


using namespace std;

int main(void){
	string line("a line of text to iterate through");
	string word;
	
	istringstream iss(line, istringstream::in);

	while( iss >> word )     
	{
	    cout << word << endl;
	}
}
