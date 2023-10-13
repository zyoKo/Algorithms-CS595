#include "tsp.h"

#include <fstream>
#include <iostream>
#include <algorithm>
#include <queue>
#include <limits>
#include <map>

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

struct SalesMan
{
	int currentCity;
	int totalCost;
	std::vector<bool> visitedCities;
	std::vector<int> currentPath;
	std::vector<int> bestPossiblePath;

	SalesMan()
		:	currentCity(0),
			totalCost(0),
			visitedCities(),
			currentPath(),
			bestPossiblePath()
	{
	}

	void MoveToCity(int city, const MAP& map)
	{
		visitedCities[city] = true;
		totalCost += map[currentCity][city];
		currentCity = city;
		currentPath.push_back(city);
	}

	void BackTrackFromCity(int city, const MAP& map)
	{
		visitedCities[city] = false;
		currentCity = *(currentPath.end() - 2);
		totalCost -= map[currentCity][city];
		currentPath.pop_back();
	}
};

int CalculateLowerBound(const MAP& map, const int& citiesCount, const SalesMan& salesMan)
{
    int lowerBound = salesMan.totalCost;

    for (int i = 0; i < citiesCount; ++i) 
	{
		if (!salesMan.visitedCities[i])
		{
			int minimumCost = std::numeric_limits<int>::max();
			for (int j = 0; j < citiesCount; ++j)
			{
				if (!salesMan.visitedCities[j])
				{
					if (map[i][j] && minimumCost > map[i][j])
						minimumCost = map[i][j];
				}
			}

			lowerBound += minimumCost;
		}
    }

    return lowerBound;
}

void TraverseCity(const MAP& map, int maxCities, SalesMan& salesMan, int countOfVisitedCities, int& finalMinimumCost)
{
    if (salesMan.totalCost >= finalMinimumCost)
        return;

    if (countOfVisitedCities == maxCities && map[salesMan.currentCity][0])	// There is a way to go to city 0
    {
        const int prevBestCost = finalMinimumCost;
        finalMinimumCost = std::min(finalMinimumCost, salesMan.totalCost + map[salesMan.currentCity][0]);
        if (finalMinimumCost < prevBestCost)
            salesMan.bestPossiblePath = salesMan.currentPath;
        return;
    }

    std::multimap<int, int> bestPaths;
    for (int city = 0; city < maxCities; ++city) 
    {
        if (!salesMan.visitedCities[city])
        {
            salesMan.MoveToCity(city, map);
            int lowerBound = CalculateLowerBound(map, maxCities, salesMan);
            bestPaths.insert(std::pair<int, int>(lowerBound, city));
            salesMan.BackTrackFromCity(city, map);
        }
    }

    for (const auto& bestIntuitivePath : bestPaths)
    {
        const int city = bestIntuitivePath.second;
        salesMan.MoveToCity(city, map);

        const int lowerBound = bestIntuitivePath.first;
        if (lowerBound < finalMinimumCost)
            TraverseCity(map, maxCities, salesMan, countOfVisitedCities + 1, finalMinimumCost);

        salesMan.BackTrackFromCity(city, map);
    }
}

void TSP(const MAP& map, SalesMan& salesMan, int cityCount)
{
	int finalMinimumCost = std::numeric_limits<int>::max();

	TraverseCity(map, cityCount, salesMan, 1, finalMinimumCost);
}

std::vector<int> SolveTSP(const char* filename)
{
	std::vector<int> solution;
	int totalCities;
	
	std::ifstream fileStream(filename, std::ifstream::in);
	if (!fileStream.is_open()) {
		std::cerr << "Failed to open file!\n" << std::endl;
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
	//PrintMap(movingCostMatrix);

	SalesMan salesMan;
	salesMan.currentCity = 0;
	salesMan.totalCost = 0;
	salesMan.currentPath.push_back(0);
	for (int i = 0; i < totalCities; ++i)
		salesMan.visitedCities.push_back(false);

	salesMan.visitedCities[0] = true;

	TSP(movingCostMatrix, salesMan, totalCities);

	salesMan.bestPossiblePath.push_back(0);

	//std::cout << "Best Possible Path: ";
	//for (unsigned i = 0; i < salesMan.bestPossiblePath.size() - 1; ++i)
	//	std::cout << salesMan.bestPossiblePath[i] << "->";
	//std::cout << "0" << std::endl;

	return salesMan.bestPossiblePath;
}
