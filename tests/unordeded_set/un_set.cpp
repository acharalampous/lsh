#include <iostream>
#include <unordered_set>
#include <string>

using namespace std;

int main(void){
    unordered_set<string> my_set;
    unordered_set<string>::iterator it;

    my_set.insert("Andreas");
    my_set.insert("Kwstas");
    my_set.insert("Michalis");
    my_set.insert("Limassol");
    my_set.insert("Manchester");
    my_set.insert("Athens");

    string city = "Athens";
    it = my_set.find(city);
    if(it == my_set.end())
        cout << city << " Was Not found" << endl;
    else
        cout << *it << " Was Found" << endl;

    city.assign("Pafos");
    it = my_set.find(city);
    if(it == my_set.end())
        cout << city << " Was Not found" << endl;
    else
        cout << *it << " Was Found" << endl;


    city = "Athens";
    my_set.erase(city);  
    it = my_set.find(city);
    if(it == my_set.end())
        cout << city << " Was Not found" << endl;
    else
        cout << *it << " Was Found" << endl;


    for(it = my_set.begin(); it != my_set.end(); it++){
        cout << *it << endl;
    }
    cout << "Size = " << my_set.size() << endl;

}