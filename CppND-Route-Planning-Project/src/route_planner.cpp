#include "route_planner.h"
#include <algorithm>
#include "my_utility.cpp"

using std::cout;

bool flag_debug = true;

RoutePlanner::RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y): m_Model(model) {
    // Convert inputs to percentage:
    start_x *= 0.01;
    start_y *= 0.01;
    end_x *= 0.01;
    end_y *= 0.01;

    // TODO 2: Use the m_Model.FindClosestNode method to find the closest nodes to the starting and ending coordinates.
    // Store the nodes you find in the RoutePlanner's start_node and end_node attributes.
    this->start_node = &m_Model.FindClosestNode(start_x, start_y);
    this->end_node   = &m_Model.FindClosestNode(end_x, end_y);
}


// TODO 3: Implement the CalculateHValue method.
// Tips:
// - You can use the distance to the end_node for the h value.
// - Node objects have a distance method to determine the distance to another node.

float RoutePlanner::CalculateHValue(RouteModel::Node const *node) {
    // h_valie = distance from end_node
    return (this->end_node->distance(*node));
}


// TODO 4: Complete the AddNeighbors method to expand the current node by adding all unvisited neighbors to the open list.
// Tips:
// - Use the FindNeighbors() method of the current_node to populate current_node.neighbors vector with all the neighbors.
// - For each node in current_node.neighbors, set the parent, the h_value, the g_value. 
// - Use CalculateHValue below to implement the h-Value calculation.
// - For each node in current_node.neighbors, add the neighbor to open_list and set the node's visited attribute to true.

void RoutePlanner::AddNeighbors(RouteModel::Node *current_node) {
    current_node->FindNeighbors();
    //
    if (flag_debug){
        cout << "AddNeighbors" << "\n";
        cout << "< Current >"  << "\n";
        cout << "   x = " << current_node->x; 
        cout << "   y = " << current_node->y;
        cout << "   h = " << current_node->h_value;
        cout << "   g = " << current_node->g_value ;
        cout << "\n";
    }
    //
    int n_neighbors = 0;
    //
    for(RouteModel::Node* neighbor : current_node->neighbors){
        neighbor->parent  = current_node;
        // h_valie = distance from end_node
        neighbor->h_value = CalculateHValue(neighbor);
        // g_valie = distance from current_node
        neighbor->g_value = current_node->distance(*neighbor);
        neighbor->visited = true;
        this->open_list.push_back(neighbor);

        if (flag_debug)
        {
            n_neighbors += 1;
            cout << "< neighbor[" << n_neighbors << "] >\n";
            cout << "   x = " << neighbor->x;
            cout << "   y = " << neighbor->y;
            cout << "   h = " << neighbor->h_value;
            cout << "   g = " << neighbor->g_value;
            cout << "\n";
        }
    }
}


// TODO 5: Complete the NextNode method to sort the open list and return the next node.
// Tips:
// - Sort the open_list according to the sum of the h value and g value.
// - Create a pointer to the node in the list with the lowest sum.
// - Remove that node from the open_list.
// - Return the pointer.

// My Function to compare F Value
bool CompareFValue(const RouteModel::Node *a, const RouteModel::Node *b)
{
    int f1 = a->g_value + a->h_value; // f1 = g1 + h1
    int f2 = b->g_value + b->g_value; // f2 = g2 + h2
    return f1 > f2;
}

// My Function to sort open_list
void *NodeSort(std::vector<RouteModel::Node *> *open_list)
{
    sort(open_list->begin(), open_list->end(), CompareFValue);
}

// Main Function of TODO 5
RouteModel::Node *RoutePlanner::NextNode() {
    // sort list with f value
    NodeSort(&this->open_list);
    // get pointer
    RouteModel::Node* current = this->open_list.back();


    if (flag_debug){
        int num_node = 0;
        for (RouteModel::Node * node : open_list){
            if (flag_debug)
            {
                num_node += 1;
                cout << "< node[" << num_node << "] >\n";
                cout << "   h = " << (node->h_value + node->g_value);
                cout << "\n";
            }
        }
    }

    // return
    return current;
}


// TODO 6: Complete the ConstructFinalPath method to return the final path found from your A* search.
// Tips:
// - This method should take the current (final) node as an argument and iteratively follow the 
//   chain of parents of nodes until the starting node is found.
// - For each node in the chain, add the distance from the node to its parent to the distance variable.
// - The returned vector should be in the correct order: the start node should be the first element
//   of the vector, the end node should be the last element.

std::vector<RouteModel::Node> RoutePlanner::ConstructFinalPath(RouteModel::Node *current_node) {
    // Create path_found vector
    distance = 0.0f;
    std::vector<RouteModel::Node> path_found;

    // TODO: Implement your solution here.

    distance *= m_Model.MetricScale(); // Multiply the distance by the scale of the map to get meters.
    return path_found;

}


// TODO 7: Write the A* Search algorithm here.
// Tips:
// - Use the AddNeighbors method to add all of the neighbors of the current node to the open_list.
// - Use the NextNode() method to sort the open_list and return the next node.
// - When the search has reached the end_node, use the ConstructFinalPath method to return the final path that was found.
// - Store the final path in the m_Model.path attribute before the method exits. This path will then be displayed on the map tile.

void RoutePlanner::AStarSearch() {
    RouteModel::Node *current_node = nullptr;

    // TODO: Implement your solution here.

}