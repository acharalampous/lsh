#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

int main(void){
    unordered_map<string, int> my_set;
    unordered_map<string, int>::iterator it;

    my_set["Athens"] = 0;
    my_set["Oslo"] = 1;
    my_set["Limassol"] = 1;
    my_set["Pafos"] = 0;
    my_set["Manchester"] = 1;
    my_set["Tokio"] = 0;
    my_set["Patra"] = 1;

    string city = "Oslo";
    it = my_set.find(city);
    if(it == my_set.end())
        cout << city << " Was Not found" << endl;
    else{
        int val = it->second;
        cout << it->first << " Was Found. Value = " << val << endl;
    }
}