#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

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

/*
//Compare the F values of two cells. 
bool Compare(const vector<int> a, const vector<int> b)
{
    int f1 = a[2] + a[3]; // f1 = g1 + h1
    int f2 = b[2] + b[3]; // f2 = g2 + h2
    return f1 > f2;
}

//Sort the two-dimensional vector of ints in descending order. 
void CellSort(vector<vector<int>> *v)
{
    sort(v->begin(), v->end(), Compare);
}
*/