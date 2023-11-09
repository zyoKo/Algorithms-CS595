#include "e-dijkstra.h"

#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
#include <numeric>
#include <limits>

struct VehicleStatus;

using PriorityQueue = std::priority_queue<VehicleStatus, std::vector<VehicleStatus>, std::less<VehicleStatus>>;

struct VehicleStatus 
{
    int currentTown;

    int rechargesLeft;

    int remainingPower;

    int totalCostSoFar;

    VehicleStatus(int _currentTown, int _rechargesLeft, int _powerLeft, int _totalCostSoFar)
		:   currentTown(_currentTown),
			rechargesLeft(_rechargesLeft),
			remainingPower(_powerLeft),
			totalCostSoFar(_totalCostSoFar)
	{ }

    bool operator<(const VehicleStatus& other) const 
    {
        return totalCostSoFar < other.totalCostSoFar;
    }
};

struct FileData
{
	int totalNumberOfTowns;

    int maxNumberOfRecharges;

    int numberOfPaths;

    std::vector<std::vector<std::pair<int, int>>> townMap;

    FileData()
	    :   totalNumberOfTowns(0),
			maxNumberOfRecharges(0),
			numberOfPaths(0),
			townMap()
    { }

    FileData(int countOfTowns, int maxRechargesAvailable, int totalNumberOfPaths)
	    :   totalNumberOfTowns(countOfTowns),
			maxNumberOfRecharges(maxRechargesAvailable),
			numberOfPaths(totalNumberOfPaths),
			townMap()
    {
        // Vector of all towns, vector of edges and weights to other towns
	    townMap.resize(totalNumberOfTowns);
    }
};

bool e_dijkstra(char const* filepath, int maxCharge)
{
	std::ifstream fileStream(filepath, std::ifstream::in);
	if (!fileStream.is_open()) 
    {
		std::cerr << "Failed to open file!\n" << std::endl;
        return false;
	}

    int totalTown, maxRecharges, totalPaths;
    fileStream >> totalTown >> maxRecharges >> totalPaths;

    FileData baseData(totalTown, maxRecharges, totalPaths);

	for (int i = 0; i < baseData.numberOfPaths; ++i)
    {
		int town1, town2, weight;
        fileStream >> town1 >> town2 >> weight;

        baseData.townMap[town1].emplace_back(town2, weight);
        baseData.townMap[town2].emplace_back(town1, weight);
    }
    fileStream.close();

    PriorityQueue pQueue;

	// Set distance to each town to max
    std::vector<int> distanceToEachTown(baseData.totalNumberOfTowns, std::numeric_limits<int>::max());

    // We recharge before we start
    baseData.maxNumberOfRecharges -= 1;

    // Main Loop
    for (int currentTown = 0; currentTown < baseData.totalNumberOfTowns; ++currentTown) 
    {
        for (int i = 0; i < baseData.totalNumberOfTowns; ++i) 
        {
            if (i == currentTown)
            {
	            distanceToEachTown[i] = 0;  // Starting city, traveling to same town (0)
            }

            distanceToEachTown[i] = std::numeric_limits<int>::max();    // else max, not traveled yet
        }

        pQueue.emplace(currentTown, baseData.maxNumberOfRecharges, maxCharge, 0);

        while (!pQueue.empty()) 
        {
        	const auto state = pQueue.top();
            pQueue.pop();

            for (const auto& travelingCost : baseData.townMap[state.currentTown]) 
            {
                const auto nextTown = travelingCost.first;
                const auto powerRequiredToTravelToNextTown = travelingCost.second;

                if(maxCharge < powerRequiredToTravelToNextTown || (state.rechargesLeft == 0 && state.remainingPower < powerRequiredToTravelToNextTown))
                {
                	continue;
                }

                if(state.remainingPower >= powerRequiredToTravelToNextTown)
                {
                    const auto totalCostToNeighborCity = distanceToEachTown[state.currentTown] + powerRequiredToTravelToNextTown;
                    if (totalCostToNeighborCity >= distanceToEachTown[nextTown])
                    {
	                    continue;
                    }

                    distanceToEachTown[nextTown] = totalCostToNeighborCity;
                    const auto powerLeft = state.remainingPower - powerRequiredToTravelToNextTown;
                    pQueue.emplace(nextTown, state.rechargesLeft, powerLeft, distanceToEachTown[nextTown]);
                }
                else
                {
                    const auto wastedPower = state.remainingPower;

                    const auto totalCostToNeighborCity = distanceToEachTown[state.currentTown] + wastedPower + powerRequiredToTravelToNextTown;
                    if (totalCostToNeighborCity >= distanceToEachTown[nextTown])
                    {
	                    continue;
                    }

                    distanceToEachTown[nextTown] = totalCostToNeighborCity;
                    const auto powerAfterReached = maxCharge - powerRequiredToTravelToNextTown;
                    pQueue.emplace(nextTown, state.rechargesLeft - 1, powerAfterReached, distanceToEachTown[nextTown]);
                }
            }
        }

        // If didn't travel to all towns, return false
        for (const auto distance : distanceToEachTown)
        {
            if (distance == std::numeric_limits<int>::max())
            {
                return false;
            }
        }
    }

    return true;
}
