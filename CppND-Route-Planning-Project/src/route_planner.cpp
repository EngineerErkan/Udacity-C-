#include "route_planner.h"
#include <algorithm>

RoutePlanner::RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y): m_Model(model) {
    // Convert inputs to percentage:
    start_x *= 0.01;
    start_y *= 0.01;
    end_x *= 0.01;
    end_y *= 0.01;

	start_node = &m_Model.FindClosestNode(start_x, start_y);    	end_node = &m_Model.FindClosestNode(end_x, end_y);
}




float RoutePlanner::CalculateHValue(RouteModel::Node const *node) {
	return node->distance(*end_node);

}


/*The flow is as follows. We start with calling the function FindNeighbors() to fill the neighbor vector of the current node.
Then, we need to loop over the nodes with a for loop/range-based for loop like for (auto neighbor: current_node->neighbors) and do five steps for every neighbor node.

Set the parent of the neighbor to be the current node.
Set the h_value of the neighbor.
Set the g_value to be the current_node g_value + distance from current_node to neighbor.
Set the neighbor as visited.
Add the neighbor to the open_list.*/
void RoutePlanner::AddNeighbors(RouteModel::Node *current_node) {
	current_node -> FindNeighbors();
  	for (auto neighbor: current_node->neighbors){
      
  	neighbor ->parent = current_node;
    neighbor->h_value = CalculateHValue(neighbor);
    neighbor->g_value = current_node->g_value + current_node->distance(*neighbor);
    neighbor->visited = true;
    open_list.push_back(neighbor);
}
}


bool Compare(const RouteModel::Node *node_1, RouteModel::Node *node_2)
{
    float f1 = node_1->g_value + node_1->h_value;
    float f2 = node_2->g_value + node_2->h_value;
    return f1 > f2;
}
RouteModel::Node *RoutePlanner::NextNode() {
	std::sort(open_list.begin(), open_list.end(), Compare);
  
  	RouteModel::Node *lowest = open_list.back();
	open_list.pop_back();
  	
  	return lowest;
  
}



std::vector<RouteModel::Node> RoutePlanner::ConstructFinalPath(RouteModel::Node *current_node) {
    distance = 0.0f;
    std::vector<RouteModel::Node> path_found;

    RouteModel::Node* pntr = current_node;
    path_found.insert(path_found.begin(), *current_node);
  
    RouteModel::Node* parentNode = current_node->parent;
  
    distance = distance + current_node->distance(*parentNode);
  
    while (parentNode != nullptr) {
      path_found.insert(path_found.begin(), *parentNode);
      RouteModel::Node* thisNode = parentNode;
      parentNode = parentNode->parent;
      if (parentNode != nullptr) {
        distance = distance + thisNode->distance(*parentNode);
      }
    }
    distance *= m_Model.MetricScale(); 
    return path_found;
}


/*Let me explain to you the flow of this task as well. We start the search with the start_node known. Please make the current node equal to the start node. Like every other node, we need to mark the start node as visited and push it into the open_list. This should happen before entering the while loop.

As you have done, the condition to keep the loop is that the open_list is not empty. The first thing we should do in the while loop is to call the NextNode() function and save the return in the current_node. Then, we need to check if the current_node == end_node, we should call the constructFinalPath(end_node) with the end_node as input.

However, if the current_node is not the end_node, then we should expand the search by calling the AddNeghobrs() function. This will insert new nodes in the open_list vector and keep exploring till the end_node is reached. Having two decisions to do based on current_node == end_node means that we need an if-else statement to handle this case inside the while loop. */

void RoutePlanner::AStarSearch() {
    RouteModel::Node *current_node = nullptr;

  	start_node->visited = true;
  	open_list.push_back(start_node);
  
    while (open_list.size() > 0) {
        current_node = NextNode();
     
        if (current_node->distance(*end_node) == 0) {
            m_Model.path = ConstructFinalPath(current_node);
          	return;
        } 
      
      	AddNeighbors(current_node); 
    }
}