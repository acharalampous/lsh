#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main(void){
    ifstream infile("input_small");
    string line;
    while(getline(infile, line)){
    
        string point;
        
        istringstream iss(line, istringstream::in); 

        /* Extract all points from string and insert in array */
        int i = 0;
        while( iss >> point )     
        {
            cout << stoi(point) << endl; 
            i++;
        }
    }
}