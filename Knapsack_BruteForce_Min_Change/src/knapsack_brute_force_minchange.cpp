#include "knapsack_brute_force_minchange.h"

#include <iostream>

#ifdef WINDOWS
#include <intrin.h>
#elif LINUX
#include <cstring>
#endif

GreyCode::GreyCode(int s)
	: size(s),
	currentValue(0)
{
}

////////////////////////////////////////////////////////////////////////////////
std::pair< bool, std::pair< bool, int > > GreyCode::Next()
{
	// To convert Binary to Gray you do the following
	const int currentGray = currentValue ^ (currentValue >> 1);
	++currentValue;
	const int nextGray = currentValue ^ (currentValue >> 1);

	int changedBit = currentGray ^ nextGray;

	int position;
#ifdef WINDOWS
	unsigned long pos = 0;
	_BitScanForward(&pos, changedBit);
	position = static_cast<int>(pos);
	/*while (changedBit)
	{
		if (changedBit & 1)
			break;
		++pos;
		changedBit >>= 1;
	}*/
#elif LINUX
	position = ffs(changedBit) - 1;
#endif

	bool add = (nextGray & (1 << position)) != 0;
	bool last = currentValue >= (1 << size) - 1;

	return std::make_pair(!last, std::make_pair(add, position));
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
}
