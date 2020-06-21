#include "my_utility.h"
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iostream>

using std::cout;
using std::string;
using std::vector;
using std::stringstream;

//using namespace std

// Split Strings by delimiter
vector<string> split(const string &s, char delimiter)
{
    vector<string> elements;
    stringstream ss(s);
    string item;

    while (getline(ss, item, delimiter))
    {
        if (!item.empty())
        {
            elements.push_back(item);
        }
    }
    return elements;
}

#include "route_model.h"

void print_node_info(RouteModel::Node* node, string title, bool flag_debug){
    if(!(title.empty())){
        cout << title;
    }
    //
    cout << "xy = [" << node->x << "," << node->y << "]  ";
    cout << "g  = " << node->g_value << ", h = " << node->h_value << "\n";
}