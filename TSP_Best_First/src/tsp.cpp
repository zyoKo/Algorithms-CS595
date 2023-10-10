#include "tsp.h"

#include <fstream>
#include <iostream>
#include <queue>

void PrintMap(const MAP& map)
{
	std::cout << "Map:\n";
	for (unsigned i = 0; i < map.size(); ++i) {
		for (unsigned j = 0; j < map.size(); ++j) {
			std::cout << map[i][j] << " ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

float CalculateLowerBound(const MAP& movingCostMatrix)
{
	float lowerBound = 0.0f;

	for (unsigned i = 0; i < movingCostMatrix.size(); ++i)
	{
		int min1 = std::numeric_limits<int>::max();
		int min2 = std::numeric_limits<int>::max();

		for (unsigned j = 0; j < movingCostMatrix.size(); ++j)
		{
			if (i != j)
			{
				if (movingCostMatrix[i][j] <= min1)
				{
					min2 = min1;
					min1 = movingCostMatrix[i][j];
				}
				else if (movingCostMatrix[i][j] <= min2)
				{
					min2 = movingCostMatrix[i][j];
				}
			}
		}
		lowerBound += static_cast<float>(min1 + min2);
	}

	return lowerBound / 2.0f;
}

struct SalesMan
{
	int currentCity;
	int totalCost;
	std::vector<bool> visitedCities;
	std::vector<int> orderOfVisitedCities;

	void MoveCity(int city, const MAP& map)
	{
		visitedCities[city] = true;
		orderOfVisitedCities.push_back(city);
		totalCost += map[currentCity][city];
		currentCity = city;
	}

	void BackTrackFromCity(int city)
	{
		visitedCities[city] = false;
		orderOfVisitedCities.erase(orderOfVisitedCities.end() - 1);
	}
};

// Recursive Function
void TraverseCity(const MAP& map, int cityCount, SalesMan& salesMan, int countOfVisitedCities, int& finalMinimumCost)
{
	if (countOfVisitedCities == cityCount && map[salesMan.currentCity][0])
	{
		//salesMan.orderOfVisitedCities.push_back(0);
		finalMinimumCost = std::min(finalMinimumCost, salesMan.totalCost + map[salesMan.currentCity][0]);
		return;
	}

	for (int city = 0; city < cityCount; ++city)
	{
		if (!salesMan.visitedCities[city] && map[salesMan.currentCity][city])
		{
			salesMan.MoveCity(city, map);
			TraverseCity(map, cityCount, salesMan, countOfVisitedCities + 1, finalMinimumCost);
			salesMan.BackTrackFromCity(city);
		}
	}
}

int TSP(const MAP& map)
{
	const int cityCount = static_cast<int>(map.size());

	SalesMan salesMan;
	salesMan.currentCity = 0;
	salesMan.totalCost = 0;
	salesMan.orderOfVisitedCities.push_back(0);
	for (int i = 0; i < cityCount; ++i)
		salesMan.visitedCities.push_back(false);

	salesMan.visitedCities[0] = true;

	int finalMinimumCost = std::numeric_limits<int>::max();

	TraverseCity(map, cityCount, salesMan, 1, finalMinimumCost);

	return finalMinimumCost;
}

std::vector<int> SolveTSP(const char* filename)
{
	std::vector<int> solution;
	int totalCities;
	
	std::ifstream fileStream(filename, std::ifstream::in);
	if (!fileStream.is_open()) {
		std::cerr << "Failed to open file!\n" << std::endl;
		__debugbreak();
	}
	fileStream >> totalCities;
	
	MAP movingCostMatrix(totalCities, std::vector<int>(totalCities, std::numeric_limits<int>::max()));
	for (int i = 0; i < totalCities; ++i)
		movingCostMatrix[i][i] = 0;	// The diagonal(moving inside same city) is 0
	
	// Read the costs and fill the matrix
	for (int i = 0; i < totalCities; ++i) {
		for (int j = i + 1; j < totalCities; ++j) {
			int cost;
			if (fileStream >> cost) {
				movingCostMatrix[i][j] = cost;
				movingCostMatrix[j][i] = cost;  // Since the matrix is symmetric
			}
		}
	}
	PrintMap(movingCostMatrix);

	const auto minimumCost = TSP(movingCostMatrix);

	std::cout << "Minimum Cost: " << minimumCost << "\n";

	// Calculate Lowest Bound
	//const float lowerBound = CalculateLowerBound(movingCostMatrix);
	//std::cout << "Lower Bound: " << lowerBound << "\n";

	return solution;
}


















//struct Node
//{
//	float bound;
//	float cost;
//	std::vector<int> path;
//};
//
//struct CompareNode {
//	bool operator()(const Node& n1, const Node& n2) {
//		return n1.bound > n2.bound;
//	}
//};

//float CalculateNodeBound(const Node& node, const MAP& movingCostMatrix) {
//	float bound = node.cost;  // Current cost to reach the node
//	int n = movingCostMatrix.size();
//
//	for (int i = 0; i < n; ++i) {
//		if (std::find(node.path.begin(), node.path.end(), i) == node.path.end()) {  // If city i is not yet visited
//			int min1 = std::numeric_limits<int>::max();
//			int min2 = std::numeric_limits<int>::max();
//
//			for (int j = 0; j < n; ++j) {
//				if (i != j && (std::find(node.path.begin(), node.path.end(), j) == node.path.end() || j == node.path[0])) {  // Considering unvisited cities and starting city
//					if (movingCostMatrix[i][j] <= min1) {
//						min2 = min1;
//						min1 = movingCostMatrix[i][j];
//					}
//					else if (movingCostMatrix[i][j] <= min2) {
//						min2 = movingCostMatrix[i][j];
//					}
//				}
//			}
//
//			bound += static_cast<float>(min1 + min2);
//		}
//	}
//
//	return bound / 2.0f;
//}

//std::priority_queue<Node, std::vector<Node>, CompareNode> pq;
	//
	//// Add the starting city to the priority queue
	//Node start;
	//start.path.push_back(0);
	//start.cost = 0;
	//start.bound = CalculateNodeBound(start, movingCostMatrix);
	//pq.push(start);
	//
	//float minLength = std::numeric_limits<float>::max();
	//std::vector<int> bestPath;
	//
	//while (!pq.empty()) {
	//	Node current = pq.top();
	//	pq.pop();
	//
	//	// If this is an end node and its cost is less than the current best
	//	if (current.path.size() == totalCities && current.cost < minLength) {
	//		bestPath = current.path;
	//		minLength = current.cost;
	//	}
	//
	//	// If this node's bound is promising
	//	if (current.bound < minLength) {
	//		// Expand the current node
	//		for (int city = 0; city < totalCities; ++city) {
	//			if (std::find(current.path.begin(), current.path.end(), city) == current.path.end()) {
	//				Node child = current;
	//				child.path.push_back(city);
	//				child.cost += movingCostMatrix[current.path.back()][city];
	//				child.bound = CalculateNodeBound(child, movingCostMatrix);
	//
	//				if (child.bound < minLength) {
	//					pq.push(child);
	//				}
	//			}
	//		}
	//	}
	//}
	//
	//bestPath.push_back(0);
	//return bestPath;