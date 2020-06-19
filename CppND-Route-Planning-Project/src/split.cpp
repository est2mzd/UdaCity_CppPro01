#include <vector>
#include <string>
#include <sstream>

using namespace std;

vector<string> split(const string &s, char delimiter){
    vector<string> elements;
    stringstream ss(s);
    string item;

    while(getline(ss, item, delimiter)){
        if(!item.empty()){
            elements.push_back(item);
        }
    }
    return elements;
}