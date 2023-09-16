#include "perm-lexicographical.h"
#include <algorithm>
#include <iostream>

bool nextPermLexicographical(std::vector<int>& p)
{
	const int size = static_cast<int>(p.size());

	// Step: 1
	// find the rightmost index which is smaller than the next index, and call it first index
	// eg. 3 2 1 4 5 6 -> 5 is not less than 6, 4 is less than 5 so 3 is "firstIndex" and arr[3] = 4
	int firstIndex = -1;
	for (int i = 0; i < size - 1; ++i)
	{
		if (p[i] < p[i + 1])
			firstIndex = i;
	}

	if (firstIndex == -1)
		return false;

	// Step: 2
	// start from index 3 and not including index 3 find the index with the value greater than index 3 but smallest among all selected ones
	// eg. 3 2 1 4 5 6 -> 5 and 6 both qualify because they are greater than 4 but 5 is the smallest among these so 5 is the selected value
	// but the "secondIndex" is 4 so arr[4] = 5
	int secondIndex = -1;
	for (int i = firstIndex + 1; i < size; ++i)
	{
		if (p[i] > p[firstIndex])
		{
			if (secondIndex > 0)
			{
				if (p[i] < p[secondIndex])
					secondIndex = i;
			}
			else
			{
				secondIndex = i;
			}
		}
	}

	// Step: 3
	// Swap both indexes
	// so, 3 2 1 5 4 6
	if (secondIndex > 0)
		std::swap(p[firstIndex], p[secondIndex]);

	// Step: 4
	// Now sort all the remaining indexes after the firstIndex(3)
	// but, 3 2 1 5> 4 6 the indexes after firstIndex are already sorted in this case
	std::vector<int>::iterator itr = p.begin();
	while (*itr != p[firstIndex + 1])
		++itr;

	std::sort(itr, p.end());

	// Repeat until can't do Step: 1
	return true;
}
