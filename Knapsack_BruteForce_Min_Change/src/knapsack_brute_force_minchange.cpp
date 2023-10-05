#include "knapsack_brute_force_minchange.h"

#ifdef DEBUG
#include <intrin.h>
#endif
#include <iostream>
#include <cstring>

GreyCode::GreyCode(int s)
	: size(s),
	currentValue(0)
{
}

////////////////////////////////////////////////////////////////////////////////
std::pair< bool, std::pair< bool, int > > GreyCode::Next()
{
	int currentGray = currentValue ^ (currentValue >> 1);
	++currentValue;
	int nextGray = currentValue ^ (currentValue >> 1);

	int changedBit = currentGray ^ nextGray;

#ifdef DEBUG
	unsigned long pos = 0;
	_BitScanForward(&pos, changedBit);
	/*while (changedBit)
	{
		if (changedBit & 1)
			break;
		++pos;
		changedBit >>= 1;
	}*/

#else
	int pos = ffs(changedBit) - 1;
#endif


	bool add = (nextGray & (1 << pos)) != 0;

	// Check if this is the last permutation
	bool last = currentValue >= (1 << size) - 1;

	return std::make_pair(!last, std::make_pair(add, pos));
}

////////////////////////////////////////////////////////////////////////////////
std::vector<bool> knapsack_brute_force(std::vector<Item> const& items, Weight const& W)
{
	std::vector<bool> bestCombination(items.size(), false);
	std::vector<bool> currentCombination(items.size(), false);

	GreyCode gray(static_cast<int>(items.size()));

	Weight currentWeight;
	int currentValue = 0;
	int maxValue = 0;

	for (int i = 0; i < (1 << items.size()) - 1; ++i)
	{
		const auto result = gray.Next();
		const bool add = result.second.first;
		const int pos = result.second.second;

		if (add)
		{
			currentCombination[pos] = true;
			currentWeight += items[pos].GetWeight();
			currentValue += items[pos].GetValue();
		}
		else
		{
			currentCombination[pos] = false;
			currentWeight -= items[pos].GetWeight();
			currentValue -= items[pos].GetValue();
		}

		if (currentWeight <= W && currentValue > maxValue)
		{
			maxValue = currentValue;
			bestCombination = currentCombination;
		}
	}

	return bestCombination;

	/*int maxValue = 0;
	std::vector<bool> bestCombination(n, false);

	GreyCode gray(n);

	for (int i = 0; i < maxPossibleCombinations; i++) {
		std::pair<bool, std::pair<bool, int>> result = gray.Next();
		bool last = result.first;
		bool add = result.second.first;
		int pos = result.second.second;

		std::vector<bool> currentCombination = bestCombination;
		currentCombination[pos] = add;

		Weight currentWeight;
		int currentValue = 0;

		for (int j = 0; j < n; j++) {
			if (currentCombination[j]) {
				currentWeight += items[j].GetWeight();
				if (currentWeight > W)
					break;
				currentValue += items[j].GetValue();
			}
		}

		if (currentValue > maxValue && currentWeight <= W) {
			maxValue = currentValue;
			bestCombination = currentCombination;
		}
	}

	return bestCombination;*/
}
