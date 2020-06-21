#ifndef MY_UTILITY_H
#define MY_UTILITY_H
#include <string>
#include <vector>
#include "route_model.h"
using std::string;
using std::vector;

vector<string> split(const string&, char);

void print_node_info(RouteModel::Node*, string , bool);

#endif// MY_UTILITY_H